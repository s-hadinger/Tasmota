/*
  xdrv_23_zigbee_converters.ino - zigbee support for Sonoff-Tasmota

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

// Zigbee ZCL converters

// from https://github.com/Koenkk/zigbee-shepherd-converters/blob/638d29f0cace6343052b9a4e7fd60980fa785479/converters/fromZigbee.js#L55
// float toPercentageCR2032(uint32_t voltage) {
//   // input voltage is in mV, i.e. 3000 = 3.000V
//   float percentage;
//   if (voltage < 2100) {
//       percentage = 0.0f;
//   } else if (voltage < 2440) {
//       percentage = 6.0f - ((2440 - voltage) * 6) / 340.0f;
//   } else if (voltage < 2740) {
//       percentage = 18.0f - ((2740 - voltage) * 12) / 300.0f;
//   } else if (voltage < 2900) {
//       percentage = 42.0f - ((2900 - voltage) * 24) / 160.0f;
//   } else if (voltage < 3000) {
//       percentage = 100.0f - ((3000 - voltage) * 58) / 100.0f;
//   } else if (voltage >= 3000) {
//       percentage = 100.0f;
//   }
//   return percentage;
// }

// Input voltage in mV, i.e. 3000 = 3.000V
// Output percentage from 0 to 100 as int
uint8_t toPercentageCR2032(uint32_t voltage) {
  float percentage;
  if (voltage < 2100) {
      percentage = 0;
  } else if (voltage < 2440) {
      percentage = 6 - ((2440 - voltage) * 6) / 340;
  } else if (voltage < 2740) {
      percentage = 18 - ((2740 - voltage) * 12) / 300;
  } else if (voltage < 2900) {
      percentage = 42 - ((2900 - voltage) * 24) / 160;
  } else if (voltage < 3000) {
      percentage = 100 - ((3000 - voltage) * 58) / 100;
  } else if (voltage >= 3000) {
      percentage = 100;
  }
  return percentage;
}

uint8_t parseAttributes(JsonObject& json,
                        uint16_t clusterid, class SBuffer &buf, uint8_t offset, uint8_t len) {
  uint32_t i = offset;
  uint32_t attrid;      // attribute id
  uint32_t attrtype;    // attribute type
  uint32_t attrlen;

  while (len + offset - i >= 3) {
    attrid = buf.get16(i);
    i += 2;
    attrtype = buf.get8(i);
    i++;
    attrlen = 0;

    String attrfullid =   

    json["type"] = "0x" + String(attrtype, HEX);
    json["value"] = nullptr;    // by default value is null if not provided

    // now parse accordingly to attr type
    switch (attrtype) {
      case 0x00:      // nodata
        break;
      case 0x10:      // bool
        {
          uint8_t val_bool = buf.get8(i++);
          if (0xFF != val_bool) {
            if (val_bool) {
              json["value"] = true;
            } else {
              json["value"] = false;
            }
          }
        }
        break;
      case 0x20:      // uint8
        {
          uint8_t uint8_val = buf.get8(i);
          i += 1;
          if (0xFF != uint8_val) {
            json["value"] = uint8_val;
          }
        }
        break;
      case 0x21:      // uint16
        {
          uint16_t uint16_val = buf.get16(i);
          i += 2;
          if (0xFFFF != uint16_val) {
            json["value"] = uint16_val;
          }
        }
        break;
      case 0x23:      // uint16
        {
          uint32_t uint32_val = buf.get32(i);
          i += 4;
          if (0xFFFFFFFF != uint32_val) {
            json["value"] = uint32_val;
          }
        }
        break;
      case 0x28:      // uint8
        {
          int8_t int8_val = buf.get8(i);
          i += 1;
          if (0x80 != int8_val) {
            json["value"] = int8_val;
          }
        }
        break;
      case 0x29:      // uint16
        {
          int16_t int16_val = buf.get16(i);
          i += 2;
          if (0x8000 != int16_val) {
            json["value"] = int16_val;
          }
        }
        break;
      case 0x2B:      // uint16
        {
          int32_t int32_val = buf.get32(i);
          i += 4;
          if (0x80000000 != int32_val) {
            json["value"] = int32_val;
          }
        }
        break;
      case 0x41:      // octet string, 1 byte len
      case 0x43:      // octet string, 2 bytes len
        break;
      case 0x42:      // string, 1 byte len
      case 0x44:      // string, 2 bytes len
        break;
    }
  }

//  ResponseAppend_P(PSTR());

  //
  // ToHex_P((unsigned char*)_payload.getBuffer(), _payload.len(), hex_char, sizeof(hex_char));
  // Response_P(PSTR("{\"" D_JSON_ZIGBEEZCLRECEIVED "\":{"
  //                 "\"groupid\":%d," "\"clusterid\":%d," "\"srcaddr\":\"0x%04X\","
  //                 "\"srcendpoint\":%d," "\"dstendpoint\":%d," "\"wasbroadcast\":%d,"
  //                 "\"linkquality\":%d," "\"securityuse\":%d," "\"seqnumber\":%d,"
  //                 "\"timestamp\":%d,"
  //                 "\"fc\":\"0x%02X\",\"manuf\":\"0x%04X\",\"transact\":%d,"
  //                 "\"cmdid\":\"0x%02X\",\"payload\":\"%s\"}}"),
  //                 groupid, clusterid, srcaddr,
  //                 srcendpoint, dstendpoint, wasbroadcast,
  //                 linkquality, securityuse, seqnumber,
  //                 timestamp,
  //                 _frame_control, _manuf_code, _transact_seq, _cmd_id,
  //                 hex_char);
  // MqttPublishPrefixTopic_P(RESULT_OR_TELE, PSTR(D_JSON_ZIGBEEZCLSENT));

      // uint32_t i = offset;
      // ZCLHeaderFrameControl_t frame_control;
      // uint16_t manuf_code = 0;
      // uint8_t transact_seq;
      // uint8_t cmd_id;
      //
      // frame_control.d8 = buf.get8(i++);
      // if (frame_control.b.manuf_specific) {
      //   manuf_code = buf.get16(i);
      //   i += 2;
      // }
      // transact_seq = buf.get8(i++);
      // cmd_id = buf.get8(i++);
      // ZCLFrame zcl_frame(frame_control.d8, manuf_code, transact_seq, cmd_id,
      //                    (const char *)(buf.buf() + i), len + offset - i);
      // return zcl_frame;
}

#endif // USE_ZIGBEE
