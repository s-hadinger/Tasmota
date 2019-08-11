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

#define XDRV_23                    23

const uint32_t ZIGBEE_BUFFER_SIZE = 256;  // Max ZNP frame is SOF+LEN+CMD1+CMD2+250+FCS = 255
const uint8_t  ZIGBEE_SOF = 0xFE;

// State machine states
enum class ZnpStates {
	S_START = 0,
	S_READY
};

const char kZigbeeCommands[] PROGMEM = D_CMND_ZIGBEEZNPSEND;

void (* const ZigbeeCommand[])(void) PROGMEM = { &CmndZigbeeZNPSend };

#include <TasmotaSerial.h>

TasmotaSerial *ZigbeeSerial = nullptr;

unsigned long zigbee_polling_window = 0;
SBuffer *zigbee_buffer = nullptr;
uint32_t zigbee_frame_len = 256;
bool zigbee_active = true;
bool zigbee_raw = false;

bool zigbeeCheckFCS(const class SBuffer *buf) {
	uint8_t len = buf->get8(1);
	uint8_t * buf2 = &(buf->getBuffer())[1]; 		// address of buffer[2], skipping SOF and Len
	uint8_t fcs = xorBytes(buf2, len + 3);	// LEN + CMD1 + CMD2 + Data len
	return (fcs == buf->get8(buf->len() - 1)) ? true : false;
}

uint8_t xorBytes(const uint8_t *buf, uint8_t len) {
	// compute XOR from all bytes
	uint8_t fcs = 0x00;		// FCS initialized with len
	for (uint32_t i = 0; i < len; i++) {
		fcs ^= *(buf++);
	}
	return fcs;
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
    uint8_t zigbee_in_byte = ZigbeeSerial->read();
//Serial.printf("ZigbeeInput byte=%d len=%d\n", zigbee_in_byte, zigbee_buffer->len());

    if ((0 == zigbee_buffer->len()) && (ZIGBEE_SOF != zigbee_in_byte)) {
      // waiting for SOF (Start Of Frame) byte, discard anything else
      AddLog_P2(LOG_LEVEL_DEBUG_MORE, PSTR("ZigbeeInput discarding byte %02X"), zigbee_in_byte);
      continue;     // discard
    }

    if (zigbee_buffer->len() < zigbee_frame_len) {
			zigbee_buffer->add8(zigbee_in_byte);
      zigbee_polling_window = millis();                               // Wait for more data
    } else {
      zigbee_polling_window = 0;                                      // Publish now
      break;
    }

    // recalculate frame length
    if (02 == zigbee_buffer->len()) {
      // We just received the Lenght byte
      uint8_t len_byte = zigbee_buffer->get8(1);
      if (len_byte > 250)  len_byte = 250;    // ZNP spec says len is 250 max

      zigbee_frame_len = len_byte + 5;        // SOF + LEN + CMD1 + CMD2 + FCS = 5 bytes overhead
    }
  }

  if (zigbee_buffer->len() && (millis() > (zigbee_polling_window + ZIGBEE_POLLING))) {
    char hex_char[(zigbee_buffer->len() * 2) + 2];
		ToHex((unsigned char*)zigbee_buffer->getBuffer(), zigbee_buffer->len(), hex_char, sizeof(hex_char));

		// buffer received, now check integrity
		if (zigbee_buffer->len() != zigbee_frame_len) {
			// Len is not correct, log and reject frame
      AddLog_P2(LOG_LEVEL_DEBUG, PSTR(D_JSON_ZIGBEEZNPRECEIVED ": received frame of wrong size %s"), hex_char);
		} else if (!zigbeeCheckFCS(zigbee_buffer)) {
			// FCS is wrong, packet is corrupt, log and reject frame
      AddLog_P2(LOG_LEVEL_DEBUG, PSTR(D_JSON_ZIGBEEZNPRECEIVED ": received bad FCS frame %s"), hex_char);
		} else {
			// frame is correct
      AddLog_P2(LOG_LEVEL_DEBUG, PSTR(D_JSON_ZIGBEEZNPRECEIVED ": received correct frame %s"), hex_char);
	    Response_P(PSTR("{\"" D_JSON_ZIGBEEZNPRECEIVED "\":\"%s\"}"), hex_char);
	    MqttPublishPrefixTopic_P(RESULT_OR_TELE, PSTR(D_JSON_ZIGBEEZNPRECEIVED));
	    XdrvRulesProcess();

			// now process the message
		}
		zigbee_buffer->setLen(0);		// empty buffer
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
				zigbee_buffer = new PreAllocatedSBuffer(sizeof(serial_in_buffer), serial_in_buffer);
			} else {
				zigbee_buffer = new SBuffer(ZIGBEE_BUFFER_SIZE);
			}
      zigbee_active = true;
      ZigbeeSerial->flush();
    }
  }
}

/*********************************************************************************************\
 * Commands
\*********************************************************************************************/

void CmndZigbeeZNPSend(void)
{
  if (ZigbeeSerial && (XdrvMailbox.data_len > 0)) {
    uint8_t code;

    char *codes = RemoveSpace(XdrvMailbox.data);
    int32_t size = strlen(XdrvMailbox.data);

    while (size > 0) {
      char stemp[3];
      strlcpy(stemp, codes, sizeof(stemp));
      code = strtol(stemp, nullptr, 16);
      ZigbeeSerial->write(code);
      size -= 2;
      codes += 2;
    }
  }
  ResponseCmndDone();
}

void ZigbeeZNPSend(class SBuffer message) {
	size_t len = message.len();

  if (ZigbeeSerial) {
		for (uint32_t i = 0; i < len; i++) {
			ZigbeeSerial->write(message.get8(i));
			// Serial.printf("ZNPSend byte %02X\n", message->get8(i));
		}
  }
	// Now send a MQTT message to report the sent message
	char hex_char[(len * 2) + 2];
	Response_P(PSTR("{\"" D_JSON_ZIGBEEZNPSENT "\":\"%s\"}"),
			ToHex(message.getBuffer(), len, hex_char, sizeof(hex_char)));
	MqttPublishPrefixTopic_P(RESULT_OR_TELE, PSTR(D_JSON_ZIGBEEZNPRECEIVED));
	XdrvRulesProcess();
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
