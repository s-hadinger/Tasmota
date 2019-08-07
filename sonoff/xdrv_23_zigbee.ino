/*
  xdrv_23_zigbee.ino - zigbee serial support for Sonoff-Tasmota

  Copyright (C) 2019  Theo Arends and Stephan Hadinger

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef USE_ZIGBEE
/*********************************************************************************************\
 * Serial Bridge using Software Serial library (TasmotaSerial)
\*********************************************************************************************/

#define XDRV_23                    23

const uint32_t ZIGBEE_BUFFER_SIZE = 256;  // Max ZNP frame is SOF+LEN+CMD1+CMD2+250+FCS = 255
const uint8_t  ZIGBEE_SOF = 0xFE;


const char kZigbeeCommands[] PROGMEM = D_CMND_ZIGBEESEND;

void (* const ZigbeeCommand[])(void) PROGMEM = { &CmndZigbeeSend };

#include <TasmotaSerial.h>

TasmotaSerial *ZigbeeSerial = nullptr;

unsigned long zigbee_polling_window = 0;
uint8_t *zigbee_buffer = nullptr;
uint32_t zigbee_in_byte_counter = 0;
uint32_t zigbee_frame_len = 256;
bool zigbee_active = true;
bool zigbee_raw = false;

// see https://stackoverflow.com/questions/6357031/how-do-you-convert-a-byte-array-to-a-hexadecimal-string-in-c
static void tohex(unsigned char * in, size_t insz, char * out, size_t outsz) {
	unsigned char * pin = in;
	static const char * hex = "0123456789ABCDEF";
	char * pout = out;
	for(; pin < in+insz; pout +=3, pin++){
		pout[0] = hex[(*pin>>4) & 0xF];
		pout[1] = hex[ *pin     & 0xF];
		pout[2] = ':';
		if (pout + 3 - out > outsz){
			/* Better to truncate output string than overflow buffer */
			/* it would be still better to either return a status */
			/* or ensure the target buffer is large enough and it never happen */
			break;
		}
	}
	pout[-1] = 0;
}


void ZigbeeInput(void)
{
  // Receive only valid ZNP frames:
  // 00 - SOF = 0xFE
  // 01 - Length of Data Field - 0..250
  // 02 - CMD1 - first byte of command
  // 03 - CMD2 - second byte of command
  // 04..FD - Data Field
  // FE (or last) - FCS Checksum

  while (ZigbeeSerial->available()) {
    yield();
    uint8_t serial_in_byte = ZigbeeSerial->read();

    if ((0 == zigbee_in_byte_counter) && (ZIGBEE_SOF != serial_in_byte)) {
      // waiting for SOF (Start Of Frame) byte, discard anything else
      continue;     // discard
    }
    // if ((serial_in_byte > 127) && !zigbee_raw) {                        // Discard binary data above 127 if no raw reception allowed
    //   zigbee_in_byte_counter = 0;
    //   ZigbeeSerial->flush();
    //   return;
    // }

    if (zigbee_in_byte_counter < zigbee_frame_len) {
      zigbee_buffer[zigbee_in_byte_counter++] = serial_in_byte;
      zigbee_polling_window = millis();                               // Wait for more data
    } else {
      zigbee_polling_window = 0;                                      // Publish now
      break;
    }

    // recalculate frame length
    if (02 == zigbee_in_byte_counter) {
      // We just received the Lenght byte
      uint8_t len_byte = zigbee_buffer[1];
      if (len_byte > 250)  len_byte = 250;    // ZNP spec says len is 250 max

      zigbee_frame_len = len_byte + 5;        // SOF + LEN + CMD1 + CMD2 + FCS = 5 bytes overhead
    }
  }

  if (zigbee_in_byte_counter && (millis() > (zigbee_polling_window + ZIGBEE_POLLING))) {
    Response_P(PSTR("{\"" D_JSON_ZIGBEERECEIVED "\":\""));
    for (uint32_t i = 0; i < serial_bridge_in_byte_counter; i++) {
      ResponseAppend_P(PSTR("%02x"), serial_bridge_buffer[i]);
    }
    ResponseAppend_P(PSTR("\"}"));
    MqttPublishPrefixTopic_P(RESULT_OR_TELE, PSTR(D_JSON_ZIGBEERECEIVED));
    XdrvRulesProcess();
    zigbee_in_byte_counter = 0;
    zigbee_frame_len = 254;
  }
}

/********************************************************************************************/

void ZigbeeInit(void)
{
  zigbee_active = false;
  if ((pin[GPIO_ZIGBEE_RX] < 99) && (pin[GPIO_ZIGBEE_TX] < 99)) {
    ZigbeeSerial = new TasmotaSerial(pin[GPIO_ZIGBEE_RX], pin[GPIO_ZIGBEE_TX]);
    if (ZigbeeSerial->begin(115200)) {    // ZNP is 115200, RTS/CTS (ignored), 8N1
      if (ZigbeeSerial->hardwareSerial()) {
        ClaimSerial();
        zigbee_buffer = (uint8_t*) serial_in_buffer;  // Use idle serial buffer to save RAM
      } else {
        zigbee_buffer = (uint8_t*) malloc(SERIAL_BRIDGE_BUFFER_SIZE);
      }
      zigbee_active = true;
      ZigbeeSerial->flush();
    }
  }
}

/*********************************************************************************************\
 * Commands
\*********************************************************************************************/

void CmndZigbeeSend(void)
{
  if (XdrvMailbox.data_len > 0) {
    uint8_t code;

    char *codes = RemoveSpace(XdrvMailbox.data);
    int32_t size = strlen(XdrvMailbox.data);

    while (size > 0) {
      char stemp[3];
      strlcpy(stemp, codes, sizeof(stemp));
      code = strtol(stemp, nullptr, 16);
      SerialBridgeSerial->write(code);                                  // "AA004566" as hex values
      size -= 2;
      codes += 2;
    }
  }
  ResponseCmndDone();
}

/*********************************************************************************************\
 * Interface
\*********************************************************************************************/

bool Xdrv23(uint8_t function)
{
  bool result = false;

  if (zigbee_active) {
    switch (function) {
      case FUNC_LOOP:
        if (ZigbeeSerial) { ZigbeeInput(); }
        break;
      case FUNC_PRE_INIT:
        ZigbeeInit();
        break;
      case FUNC_COMMAND:
        result = DecodeCommand(kZigbeeCommands, ZigbeeCommand);
        break;
    }
  }
  return result;
}

#endif // USE_ZIGBEE
