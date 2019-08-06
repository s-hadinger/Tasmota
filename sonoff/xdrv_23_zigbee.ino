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

const uint32_t ZIGBEE_BUFFER_SIZE = 256;

#include <TasmotaSerial.h>

TasmotaSerial *ZigbeeSerial = nullptr;

unsigned long zigbee_polling_window = 0;
char *zigbee_buffer = nullptr;
int zigbee_in_byte_counter = 0;
bool zigbee_active = true;
bool zigbee_raw = false;

void ZigbeeInput(void)
{
  while (ZigbeeSerial->available()) {
    yield();
    uint8_t serial_in_byte = ZigbeeSerial->read();

    if ((serial_in_byte > 127) && !zigbee_raw) {                        // Discard binary data above 127 if no raw reception allowed
      zigbee_in_byte_counter = 0;
      ZigbeeSerial->flush();
      return;
    }
    if (serial_in_byte || zigbee_raw) {                                 // Any char between 1 and 127 or any char (0 - 255)

      if ((zigbee_in_byte_counter < SERIAL_BRIDGE_BUFFER_SIZE -1) &&    // Add char to string if it still fits and ...
          ((isprint(serial_in_byte) && (128 == Settings.serial_delimiter)) ||  // Any char between 32 and 127
          ((serial_in_byte != Settings.serial_delimiter) && (128 != Settings.serial_delimiter)) ||  // Any char between 1 and 127 and not being delimiter
            zigbee_raw)) {                                              // Any char between 0 and 255
        zigbee_buffer[zigbee_in_byte_counter++] = serial_in_byte;
        zigbee_polling_window = millis();                               // Wait for more data
      } else {
        zigbee_polling_window = 0;                                      // Publish now
        break;
      }
    }
  }

  if (zigbee_in_byte_counter && (millis() > (zigbee_polling_window + SERIAL_POLLING))) {
    zigbee_buffer[zigbee_in_byte_counter] = 0;                   // Serial data completed
    if (!zigbee_raw) {
      Response_P(PSTR("{\"" D_JSON_SSERIALRECEIVED "\":\"%s\"}"), zigbee_buffer);
    } else {
      Response_P(PSTR("{\"" D_JSON_SSERIALRECEIVED "\":\""));
      for (uint32_t i = 0; i < zigbee_in_byte_counter; i++) {
        ResponseAppend_P(PSTR("%02x"), zigbee_buffer[i]);
      }
      ResponseAppend_P(PSTR("\"}"));
    }
    MqttPublishPrefixTopic_P(RESULT_OR_TELE, PSTR(D_JSON_SSERIALRECEIVED));
    XdrvRulesProcess();
    zigbee_in_byte_counter = 0;
  }
}

/********************************************************************************************/

void ZigbeeInit(void)
{
  zigbee_active = false;
  if ((pin[GPIO_SBR_RX] < 99) && (pin[GPIO_SBR_TX] < 99)) {
    ZigbeeSerial = new TasmotaSerial(pin[GPIO_SBR_RX], pin[GPIO_SBR_TX]);
    if (ZigbeeSerial->begin(Settings.sbaudrate * 1200)) {  // Baud rate is stored div 1200 so it fits into one byte
      if (ZigbeeSerial->hardwareSerial()) {
        ClaimSerial();
        zigbee_buffer = serial_in_buffer;  // Use idle serial buffer to save RAM
      } else {
        zigbee_buffer = (char*)(malloc(SERIAL_BRIDGE_BUFFER_SIZE));
      }
      zigbee_active = true;
      ZigbeeSerial->flush();
    }
  }
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
    }
  }
  return result;
}

#endif // USE_ZIGBEE
