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

/*********************************************************************************************\
 * ZCL
\*********************************************************************************************/

typedef union ZCLHeaderFrameControl_t {
  struct {
    uint8_t frame_type : 2;           // 00 = across entire profile, 01 = cluster specific
    uint8_t manuf_specific : 1;       // Manufacturer Specific Sub-field
    uint8_t direction : 1;            // 0 = tasmota to zigbee, 1 = zigbee to tasmota
    uint8_t disable_def_resp : 1;     // don't send back default response
    uint8_t reserved : 3;
  } b;
  uint32_t d8;                         // raw 8 bits field
} ZCLHeaderFrameControl_t;


class ZCLFrame {
public:

  ZCLFrame(uint8_t frame_control, uint16_t manuf_code, uint8_t transact_seq, uint8_t cmd_id,
    const char *buf, size_t buf_len, uint16_t clusterid = 0, uint16_t groupid = 0):
    _cmd_id(cmd_id), _manuf_code(manuf_code), _transact_seq(transact_seq),
    _payload(buf_len ? buf_len : 250),      // allocate the data frame from source or preallocate big enough
    _cluster_id(clusterid), _group_id(groupid)
    {
      _frame_control.d8 = frame_control;
      _payload.addBuffer(buf, buf_len);
    };


  void publishMQTTReceived(uint16_t groupid, uint16_t clusterid, Z_ShortAddress srcaddr,
                           uint8_t srcendpoint, uint8_t dstendpoint, uint8_t wasbroadcast,
                           uint8_t linkquality, uint8_t securityuse, uint8_t seqnumber,
                           uint32_t timestamp) {
    char hex_char[_payload.len()*2+2];
		ToHex_P((unsigned char*)_payload.getBuffer(), _payload.len(), hex_char, sizeof(hex_char));
    Response_P(PSTR("{\"" D_JSON_ZIGBEEZCLRECEIVED "\":{"
                    "\"groupid\":%d," "\"clusterid\":%d," "\"srcaddr\":\"0x%04X\","
                    "\"srcendpoint\":%d," "\"dstendpoint\":%d," "\"wasbroadcast\":%d,"
                    "\"linkquality\":%d," "\"securityuse\":%d," "\"seqnumber\":%d,"
                    "\"timestamp\":%d,"
                    "\"fc\":\"0x%02X\",\"manuf\":\"0x%04X\",\"transact\":%d,"
                    "\"cmdid\":\"0x%02X\",\"payload\":\"%s\""),
                    groupid, clusterid, srcaddr,
                    srcendpoint, dstendpoint, wasbroadcast,
                    linkquality, securityuse, seqnumber,
                    timestamp,
                    _frame_control, _manuf_code, _transact_seq, _cmd_id,
                    hex_char);

    ResponseJsonEnd();      // append '}'
    ResponseJsonEnd();      // append '}'
  	MqttPublishPrefixTopic_P(RESULT_OR_TELE, PSTR(D_JSON_ZIGBEEZCLSENT));
  	XdrvRulesProcess();
  }

  static ZCLFrame parseRawFrame(SBuffer &buf, uint8_t offset, uint8_t len, uint16_t clusterid, uint16_t groupid) { // parse a raw frame and build the ZCL frame object
    uint32_t i = offset;
    ZCLHeaderFrameControl_t frame_control;
    uint16_t manuf_code = 0;
    uint8_t transact_seq;
    uint8_t cmd_id;

    frame_control.d8 = buf.get8(i++);
    if (frame_control.b.manuf_specific) {
      manuf_code = buf.get16(i);
      i += 2;
    }
    transact_seq = buf.get8(i++);
    cmd_id = buf.get8(i++);
    ZCLFrame zcl_frame(frame_control.d8, manuf_code, transact_seq, cmd_id,
                       (const char *)(buf.buf() + i), len + offset - i,
                       clusterid, groupid);
    return zcl_frame;
  }

  void parseRawAttributes(JsonObject& json, uint8_t offset = 0);
  void postProcessAttributes(JsonObject& json);

  inline void setGroupId(uint16_t groupid) {
    _group_id = groupid;
  }

  inline void setClusterId(uint16_t clusterid) {
    _cluster_id = clusterid;
  }

  const SBuffer &getPayload(void) const {
    return _payload;
  }

private:
  ZCLHeaderFrameControl_t _frame_control = { .d8 = 0 };
  uint16_t                _manuf_code = 0;      // optional
  uint8_t                 _transact_seq = 0;    // transaction sequence number
  uint8_t                 _cmd_id = 0;
  uint16_t                _cluster_id = 0;
  uint16_t                _group_id = 0;
  SBuffer                 _payload;
};



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


uint32_t parseSingleAttribute(JsonObject& json, char *attrid_str, class SBuffer &buf,
                              uint32_t offset, uint32_t len) {

  uint32_t i = offset;
  uint32_t attrtype = buf.get8(i++);

  // fallback - enter a null value
  json[attrid_str] = (char*) nullptr;

  // now parse accordingly to attr type
  switch (attrtype) {
    case 0x00:      // nodata
    case 0xFF:      // unk
      break;
    case 0x10:      // bool
      {
        uint8_t val_bool = buf.get8(i++);
        if (0xFF != val_bool) {
          json[attrid_str] = (bool) (val_bool ? true : false);
        }
      }
      break;
    case 0x20:      // uint8
      {
        uint8_t uint8_val = buf.get8(i);
        i += 1;
        if (0xFF != uint8_val) {
          json[attrid_str] = uint8_val;
        }
      }
      break;
    case 0x21:      // uint16
      {
        uint16_t uint16_val = buf.get16(i);
        i += 2;
        if (0xFFFF != uint16_val) {
          json[attrid_str] = uint16_val;
        }
      }
      break;
    case 0x23:      // uint16
      {
        uint32_t uint32_val = buf.get32(i);
        i += 4;
        if (0xFFFFFFFF != uint32_val) {
          json[attrid_str] = uint32_val;
        }
      }
      break;
    // Note: uint40, uint48, uint56, uint64 are not used in ZCL, so they are not implemented (yet)
    case 0x24:    // int40
    case 0x25:    // int48
    case 0x26:    // int56
    case 0x27:    // int64
      i += attrtype - 0x1F;   // 5 - 8;
      break;
    case 0x28:      // uint8
      {
        int8_t int8_val = buf.get8(i);
        i += 1;
        if (0x80 != int8_val) {
          json[attrid_str] = int8_val;
        }
      }
      break;
    case 0x29:      // uint16
      {
        int16_t int16_val = buf.get16(i);
        i += 2;
        if (0x8000 != int16_val) {
          json[attrid_str] = int16_val;
        }
      }
      break;
    case 0x2B:      // uint16
      {
        int32_t int32_val = buf.get32(i);
        i += 4;
        if (0x80000000 != int32_val) {
          json[attrid_str] = int32_val;
        }
      }
      break;
    // Note: int40, int48, int56, int64 are not used in ZCL, so they are not implemented (yet)
    case 0x2C:    // int40
    case 0x2D:    // int48
    case 0x2E:    // int56
    case 0x2F:    // int64
      i += attrtype - 0x27;   // 5 - 8;
      break;

    case 0x41:      // octet string, 1 byte len
    case 0x42:      // char string, 1 byte len
    case 0x43:      // octet string, 2 bytes len
    case 0x44:      // char string, 2 bytes len
      // For strings, default is to try to do a real string, but reverts to octet stream if null char is present or on some exceptions
      {
        bool parse_as_string = true;
        uint32_t len = (attrtype <= 0x42) ? buf.get8(i) : buf.get16(i);    // len is 8 or 16 bits
        i += (attrtype <= 0x42) ? 1 : 2;                                   // increment pointer

        // check if we can safely use a string
        if ((0x41 == attrtype) || (0x43 == attrtype)) { parse_as_string = false; }
        else {
          for (uint32_t j = 0; j < len; j++) {
            if (0x00 == buf.get8(i+j)) {
              parse_as_string = false;
              break;
            }
          }
        }

        if (parse_as_string) {
          char str[len+1];
          strncpy(str, buf.charptr(i), len);
          str[len] = 0x00;
          json[attrid_str] = str;
        } else {
          // print as HEX
          char hex[2*len+1];
          ToHex_P(buf.buf(i), len, hex, sizeof(hex));
          json[attrid_str] = hex;
        }

        i += len;
        break;
      }
      i += buf.get8(i) + 1;
      break;


    // TODO
    case 0x08:      // data8
      i++;
      break;
    case 0x18:      // map8
      i++;
      break;
    case 0x19:      // map16
      i += 2;
      break;
    case 0x1B:      // map32
      i += 4;
      break;
    // enum
    case 0x30:      // enum8
    case 0x31:      // enum16
      i += attrtype - 0x2F;
      break;

    case 0x39:      // float
      i += 4;
      break;

    case 0xE0:      // ToD
    case 0xE1:      // date
    case 0xE2:      // UTC
      i += 4;
      break;

    case 0xE8:      // clusterId
    case 0xE9:      // attribId
      i += 2;
      break;
    case 0xEA:      // bacOID
      i += 4;
      break;

    case 0xF0:      // EUI64
      i += 8;
      break;
    case 0xF1:      // key128
      i += 16;
      break;

    // Other un-implemented data types
    case 0x09:      // data16
    case 0x0A:      // data24
    case 0x0B:      // data32
    case 0x0C:      // data40
    case 0x0D:      // data48
    case 0x0E:      // data56
    case 0x0F:      // data64
      i += attrtype - 0x07;   // 2-8
      break;
    // map<x>
    case 0x1A:      // map24
    case 0x1C:      // map40
    case 0x1D:      // map48
    case 0x1E:      // map56
    case 0x1F:      // map64
      i += attrtype - 0x17;
      break;
    // semi
    case 0x38:      // semi (float on 2 bytes)
      i += 2;
      break;
    case 0x3A:      // double precision
      i += 8;
      break;
  }

  String pp;    // pretty print
  json[attrid_str].prettyPrintTo(pp);
  // now store the attribute
  AddLog_P2(LOG_LEVEL_INFO, PSTR("ZIG: ZCL attribute decoded, id %s, type 0x%02X, val=%s"),
                                 attrid_str, attrtype, pp.c_str());
  return i - offset;    // how much have we increased the index
}


// First pass, parse all attributes in their native format
// The key is 32 bits, high 16 bits is cluserid, low 16 bits is attribute id
void ZCLFrame::parseRawAttributes(JsonObject& json, uint8_t offset) {
  uint32_t i = offset;
  uint32_t len = _payload.len();
  uint32_t attrid = _cluster_id << 16;      // set high 16 bits with cluster if

  while (len + offset - i >= 3) {
    attrid = (attrid & 0xFFFF0000) | _payload.get16(i);    // get lower 16 bits
    i += 2;

    char shortaddr[12];
    snprintf_P(shortaddr, sizeof(shortaddr), PSTR("0x%08X"), attrid);

    // exception for Xiaomi lumi.weather - specific field to be treated as octet and not char
    if (0x0000FF01 == attrid) {
      if (0x42 == _payload.get8(i)) {
        _payload.set8(i, 0x41);   // change type from 0x42 to 0x41
      }
    }

    i += parseSingleAttribute(json, shortaddr, _payload, i, len);


//          else if (0x0000FF01 == attrid) { parse_as_string = false; }    // special case for Xiamoi lumi.weather


  }

  // MqttPublishPrefixTopic_P(RESULT_OR_TELE, PSTR(D_JSON_ZIGBEEZCLSENT));
}

//static const char ZCL_TEMPERATURE[] PROGMEM = "0x04020000";
#define ZCL_MODELID       "0x00000005"
#define ZCL_TEMPERATURE   "0x04020000"
#define ZCL_PRESSURE      "0x04030000"
#define ZCL_PRESSURE_SCALED       "0x04030010"
#define ZCL_PRESSURE_SCALE        "0x04030014"
#define ZCL_HUMIDITY      "0x04050000"
#define ZCL_LUMI_WEATHER  "0x0000FF01"

void ZCLFrame::postProcessAttributes(JsonObject& json) {
  const __FlashStringHelper *key;

  // ModelID ZCL 3.2
  key = F(ZCL_MODELID);
  if (json.containsKey(key)) {
    json[F(D_JSON_MODEL D_JSON_ID)] = json[key];
    json.remove(key);
  }

  // Temperature ZCL 4.4
  key = F(ZCL_TEMPERATURE);
  if (json.containsKey(key)) {
    // parse temperature
    int32_t temperature = json[key];
    json.remove(key);
    json[F(D_JSON_TEMPERATURE)] = temperature / 100.0f;
  }

  // Pressure ZCL 4.5
  key = F(ZCL_PRESSURE);
  if (json.containsKey(key)) {
    // parse temperature
    int32_t pressure = json[key];
    json.remove(key);
    json[F(D_JSON_PRESSURE)] = pressure / 10.0f;
  }
  json.remove(F(ZCL_PRESSURE_SCALE));
  json.remove(F(ZCL_PRESSURE_SCALED));

  // Humidity ZCL 4.7
  key = F(ZCL_HUMIDITY);
  if (json.containsKey(key)) {
    // parse temperature
    uint32_t humidity = json[key];
    json.remove(key);
    json[F(D_JSON_HUMIDITY)] = humidity / 100.0f;
  }

  // Lumi.weather proprietary field
  key = F(ZCL_LUMI_WEATHER);
  if (json.containsKey(key)) {
    String hex = json[key];
    SBuffer buf2 = SBuffer::SBufferFromHex(hex.c_str(), hex.length());
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json_lumi = jsonBuffer.createObject();
    uint32_t i = 0;
    uint32_t len = buf2.len();
    char shortaddr[8];

    while (len - i >= 2) {
      uint8_t attrid = buf2.get8(i++);

      snprintf_P(shortaddr, sizeof(shortaddr), PSTR("0x%02X"), attrid);

      i += parseSingleAttribute(json_lumi, shortaddr, buf2, i, len);
    }
    // parse output
    if (json_lumi.containsKey("0x64")) {    // Temperature
      int32_t temperature = json_lumi["0x64"];
      json[F(D_JSON_TEMPERATURE)] = temperature / 100.0f;
    }
    if (json_lumi.containsKey("0x65")) {    // Humidity
      uint32_t humidity = json_lumi["0x65"];
      json[F(D_JSON_HUMIDITY)] = humidity / 100.0f;
    }
    if (json_lumi.containsKey("0x66")) {    // Pressure
      int32_t pressure = json_lumi["0x66"];
      json[F(D_JSON_PRESSURE)] = pressure / 100.0f;
    }

    json.remove(key);
  }

}

#endif // USE_ZIGBEE
