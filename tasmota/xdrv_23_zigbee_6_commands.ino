/*
  xdrv_23_zigbee_converters.ino - zigbee support for Tasmota

  Copyright (C) 2020  Theo Arends and Stephan Hadinger

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

//typedef int32_t (*Z_AttrConverter)(uint16_t shortaddr, JsonObject& json, const char *name, JsonVariant& value, const char *new_name, void * param);
typedef struct Z_CommandConverter {
  const char * tasmota_cmd;
  const char * zcl_cmd;
} Z_CommandConverter;

typedef struct Z_CommandConverter2 {
  const char * tasmota_cmd;
  uint16_t     cluster;
  uint16_t     cmd;       // normally 8 bits, 0xFFFF means it's a parameter
  const char * param;
} Z_CommandConverter2;

// list of post-processing directives
const Z_CommandConverter2 Z_Commands2[] = {
  { "Power",          0x0006, 0xFFFF, "" },              // 0=Off, 1=On, 2=Toggle
  { "Dimmer",         0x0008, 0x04,   "xx0A00" },       // Move to Level with On/Off, xx=0..254 (255 is invalid)
  { "Dimmer+",        0x0008, 0x06,   "001902" },       // Step up by 10%, 0.2 secs
  { "Dimmer-",        0x0008, 0x06,   "011902" },       // Step down by 10%, 0.2 secs
  { "DimmerStop",     0x0008, 0x03,   "" },              // Stop any Dimmer animation
  { "ResetAlarm",     0x0009, 0x00,   "xxyyyy" },       // Reset alarm (alarm code + cluster identifier)
  { "ResetAllAlarms", 0x0009, 0x01,   "" },             // Reset all alarms
  { "Hue",            0x0300, 0x00,   "xx000A00" },     // Move to Hue, shortest time, 1s
  { "Sat",            0x0300, 0x03,   "xx0A00" },       // Move to Sat
  { "HueSat",         0x0300, 0x06,   "xxyy0A00" },     // Hue, Sat
  { "Color",          0x0300, 0x07,   "xxxxyyyy0A00" }, // x, y (uint16)
  { "CT",             0x0300, 0x0A,   "xxxx0A00" },     // Color Temperature Mireds (uint16)
  { "ShutterOpen",    0x0102, 0x00,   "" },
  { "ShutterClose",   0x0102, 0x01,   "" },
  { "ShutterStop",    0x0102, 0x02,   "" },
  { "ShutterLift",    0x0102, 0x05,   "xx" },            // Lift percentage, 0%=open, 100%=closed
  { "ShutterTilt",    0x0102, 0x08,   "xx" },            // Tilt percentage
  { "Shutter",        0x0102, 0xFFFF, "" },
  // Blitzwolf PIR
  { "",               0xEF00, 0x01,   ""},                // Specific decoder for Blitzwolf PIR, empty name means special treatment
  // Decoders only - normally not used to send, and names may be masked by previous definitions
  { "Dimmer",         0x0008, 0x00,   "xx" },
  { "DimmerMove",     0x0008, 0x01,   "xx0A" },
  { "DimmerStep",     0x0008, 0x02,   "xx190A00" },
  { "DimmerMove",     0x0008, 0x05,   "xx0A" },
  { "Dimmer+",        0x0008, 0x06,   "00" },
  { "Dimmer-",        0x0008, 0x06,   "01" },
  { "DimmerStop",     0x0300, 0x01,   "xx19" },
  { "HueStep",        0x0300, 0x02,   "xx190A00" },
  { "SatMove",        0x0300, 0x04,   "xx19" },
  { "SatStep",        0x0300, 0x05,   "xx190A" },
  { "ColorMove",      0x0300, 0x08,   "xxxxyyyy" },
  { "ColorStep",      0x0300, 0x09,   "xxxxyyyy0A00" },
};

// list of post-processing directives
const Z_CommandConverter Z_Commands[] = {
  { "Power",        "0006!xx" },              // 0=Off, 1=On, 2=Toggle
  { "Dimmer",       "0008!04/xx0A00" },       // Move to Level with On/Off, xx=0..254 (255 is invalid)
  { "Dimmer+",      "0008!06/001902" },       // Step up by 10%, 0.2 secs
  { "Dimmer-",      "0008!06/011902" },       // Step down by 10%, 0.2 secs
  { "DimmerStop",   "0008!03" },              // Stop any Dimmer animation
  { "ResetAlarm",   "0009!00/xxyyyy" },       // Reset alarm (alarm code + cluster identifier)
  { "ResetAllAlarms","0009!01" },             // Reset all alarms
  { "Hue",          "0300!00/xx000A00" },     // Move to Hue, shortest time, 1s
  { "Sat",          "0300!03/xx0A00" },       // Move to Sat
  { "HueSat",       "0300!06/xxyy0A00" },     // Hue, Sat
  { "Color",        "0300!07/xxxxyyyy0A00" }, // x, y (uint16)
  { "CT",           "0300!0A/xxxx0A00" },     // Color Temperature Mireds (uint16)
  { "Shutter",      "0102!xx" },
  { "ShutterOpen",  "0102!00" },
  { "ShutterClose", "0102!01" },
  { "ShutterStop",  "0102!02" },
  { "ShutterLift",  "0102!05/xx" },            // Lift percentage, 0%=open, 100%=closed
  { "ShutterTilt",  "0102!08/xx" },            // Tilt percentage
  // Blitzwolf PIR
  { "",             "EF00!01"},                // Specific decoder for Blitzwolf PIR, empty name means special treatment
  // Decoders only - normally not used to send, and names may be masked by previous definitions
  { "Dimmer",       "0008!00/xx" },
  { "DimmerMove",   "0008!01/xxFF" },
  { "DimmerStep",   "0008!02/xx19FFFF" },
  { "DimmerMove",   "0008!05/xxFF" },
  { "Dimmer+",      "0008!06/00" },
  { "Dimmer-",      "0008!06/01" },
  { "DimmerStop",   "0008!07" },
  { "HueMove",      "0300!01/xx19" },
  { "HueStep",      "0300!02/xx190A00" },
  { "SatMove",      "0300!04/xx19" },
  { "SatStep",      "0300!05/xx190A" },
  { "ColorMove",    "0300!08/xxxxyyyy" },
  { "ColorStep",    "0300!09/xxxxyyyy0A00" },
};

#define ZLE(x) ((x) & 0xFF), ((x) >> 8)     // Little Endian

// Below are the attributes we wand to read from each cluster
const uint8_t CLUSTER_0006[] = { ZLE(0x0000) };    // Power
const uint8_t CLUSTER_0008[] = { ZLE(0x0000) };    // CurrentLevel
const uint8_t CLUSTER_0009[] = { ZLE(0x0000) };    // AlarmCount
const uint8_t CLUSTER_0300[] = { ZLE(0x0000), ZLE(0x0001), ZLE(0x0003), ZLE(0x0004), ZLE(0x0007) };    // Hue, Sat, X, Y, CT

// This callback is registered after a cluster specific command and sends a read command for the same cluster
int32_t Z_ReadAttrCallback(uint16_t shortaddr, uint16_t cluster, uint16_t endpoint, uint32_t value) {
  size_t         attrs_len = 0;
  const uint8_t* attrs = nullptr;

  switch (cluster) {
    case 0x0006:                              // for On/Off
      attrs = CLUSTER_0006;
      attrs_len = sizeof(CLUSTER_0006);
      break;
    case 0x0008:                              // for Dimmer
      attrs = CLUSTER_0008;
      attrs_len = sizeof(CLUSTER_0008);
      break;
    case 0x0009:                              // for Alarms
      attrs = CLUSTER_0009;
      attrs_len = sizeof(CLUSTER_0009);
      break;
    case 0x0300:                              // for Lights
      attrs = CLUSTER_0300;
      attrs_len = sizeof(CLUSTER_0300);
      break;
  }
  if (attrs) {
    ZigbeeZCLSend(shortaddr, cluster, endpoint, ZCL_READ_ATTRIBUTES, false, attrs, attrs_len, false /* we do want a response */);
  }
}

// set a timer to read back the value in the future
void zigbeeSetCommandTimer(uint16_t shortaddr, uint16_t cluster, uint16_t endpoint) {
  uint32_t wait_ms = 0;

  switch (cluster) {
    case 0x0006:        // for On/Off
    case 0x0009:        // for Alamrs
      wait_ms = 200;    // wait 0.2 s
      break;
    case 0x0008:        // for Dimmer
    case 0x0300:        // for Color
      wait_ms = 1050;   // wait 1.0 s
      break;
    case 0x0102:        // for Shutters
      wait_ms = 10000;  // wait 10.0 s
      break;
  }
  if (wait_ms) {
    zigbee_devices.setTimer(shortaddr, wait_ms, cluster, endpoint, 0 /* value */, &Z_ReadAttrCallback);
  }
}

inline bool isXYZ(char c) {
  return (c >= 'x') && (c <= 'z');
}

// truncate at first 'x', 'y' or 'z'
void truncateAtXYZ(char *p) {
  while (*p) {
    if (isXYZ(*p)) {
      *p = 0;
      break;
    }
    p++;
  }
}

// https://stackoverflow.com/questions/4770985/how-to-check-if-a-string-starts-with-another-string-in-c
bool startsWith(const char *pre, const char *str)
{
  size_t lenpre = strlen(pre),
         lenstr = strlen(str);
  return lenstr < lenpre ? false : memcmp_P(pre, str, lenpre) == 0;
}

void convertClusterSpecific(JsonObject& json, uint16_t cluster, uint8_t cmd, const SBuffer &payload) {
  char hex_char[payload.len()*2+2];
  ToHex_P((unsigned char*)payload.getBuffer(), payload.len(), hex_char, sizeof(hex_char));

  for (uint32_t i = 0; i < sizeof(Z_Commands) / sizeof(Z_Commands[0]); i++) {
    char command[32];
    char command_prefix[32];
    const Z_CommandConverter *conv = &Z_Commands[i];
    strcpy_P(command, conv->zcl_cmd);
    // 
    strcpy_P(command_prefix, conv->zcl_cmd);
    truncateAtXYZ(command_prefix);
    
  }

  char attrid_str[12];
  snprintf_P(attrid_str, sizeof(attrid_str), PSTR("%04X!%02X"), cluster, cmd);

  json[attrid_str] = hex_char;
}

// Find the command details by command name
// Returns if found:
//  - cluster number
//  - command number or 0xFFFF if command is part of the variable part
//  - the payload in the form of a HEX string with x/y/z variables
// If not found:
//  - returns nullptr
const __FlashStringHelper* zigbeeFindCommand2(const char *command, uint16_t *cluster, uint16_t *cmd) {
  for (uint32_t i = 0; i < sizeof(Z_Commands2) / sizeof(Z_Commands2[0]); i++) {
    const Z_CommandConverter2 *conv = &Z_Commands2[i];
    if (0 == strcasecmp_P(command, conv->tasmota_cmd)) {
      *cluster = conv->cluster;
      *cmd = conv->cmd;
      return (const __FlashStringHelper*) conv->param;
    }
  }

  return nullptr;
}
const __FlashStringHelper* zigbeeFindCommand(const char *command) {
  for (uint32_t i = 0; i < sizeof(Z_Commands) / sizeof(Z_Commands[0]); i++) {
    const Z_CommandConverter *conv = &Z_Commands[i];
    if (0 == strcasecmp_P(command, conv->tasmota_cmd)) {
      return (const __FlashStringHelper*) conv->zcl_cmd;
    }
  }

  return nullptr;
}

// take the lower 4 bits and turn it to an hex char
inline char hexDigit(uint32_t h) {
  uint32_t nybble = h & 0x0F;
  return (nybble > 9) ? 'A' - 10 + nybble : '0' + nybble;
}

// replace all xx/yy/zz substrings with unsigned ints, and the corresponding len (8, 16 or 32 bits)
String zigbeeCmdAddParams(const char *zcl_cmd_P, uint32_t x, uint32_t y, uint32_t z) {
  size_t len = strlen_P(zcl_cmd_P);
  char zcl_cmd[len+1];
  strcpy_P(zcl_cmd, zcl_cmd_P);     // copy into RAM

  char *p = zcl_cmd;
  while (*p) {
    if (isXYZ(*p) && (*p == *(p+1))) {    // if char is [x-z] and followed by same char
      uint8_t val;
      switch (*p) {
        case 'x':
          val = x & 0xFF;
          x = x >> 8;
          break;
        case 'y':
          val = y & 0xFF;
          y = y >> 8;
          break;
        case 'z':
          val = z & 0xFF;
          z = z >> 8;
          break;
      }
      *p = hexDigit(val >> 4);
      *(p+1) = hexDigit(val);
      p++;
    }
    p++;
  }
  AddLog_P2(LOG_LEVEL_DEBUG, PSTR("SendZCLCommand_P: zcl_cmd = %s"), zcl_cmd);

  return String(zcl_cmd);
}

const char kZ_Alias[] PROGMEM = "OFF|" D_OFF "|" D_FALSE "|" D_STOP  "|" "OPEN" "|"           // 0
                                "ON|"  D_ON  "|" D_TRUE  "|" D_START "|" "CLOSE" "|"          // 1
                                "TOGGLE|" D_TOGGLE "|"                                        // 2
                                "ALL" ;                                                       // 255

const uint8_t kZ_Numbers[] PROGMEM = { 0,0,0,0,0,
                                       1,1,1,1,1,
                                       2,2,
                                       255 };

// Convert an alias like "On" to the corresponding number
uint32_t ZigbeeAliasOrNumber(const char *state_text) {
  char command[16];
  int state_number = GetCommandCode(command, sizeof(command), state_text, kZ_Alias);
  if (state_number >= 0) {
    // found an alias, get its value
    return pgm_read_byte(kZ_Numbers + state_number);
  } else {
    // no alias found, convert it as number
    return strtoul(state_text, nullptr, 0);
  }
}

#endif // USE_ZIGBEE
