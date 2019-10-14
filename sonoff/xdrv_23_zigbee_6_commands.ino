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

//typedef int32_t (*Z_AttrConverter)(uint16_t shortaddr, JsonObject& json, const char *name, JsonVariant& value, const char *new_name, void * param);
typedef struct Z_CommandConverter {
  const char * tasmota_cmd;
  const char * zcl_cmd;
} Z_CommandConverter;

// list of post-processing directives
const Z_CommandConverter Z_Commands[] = {
  { "Power",        "0006!xx" },              // 0=Off, 1=On, 2=Toggle
  { "Dimmer",       "0008!04/xx0A00" },       // Move to Level with On/Off, xx=0..254 (255 is invalid)
  { "Dimmer+",      "0008!06/001902" },       // Step up by 10%, 0.2 secs
  { "Dimmer-",      "0008!06/011902" },       // Step down by 10%, 0.2 secs
  { "Hue",          "0300!00/xx000A00" },     // Move to Hue, shortest time, 1s
  { "Sat",          "0300!03/xx0A00" },       // Move to Sat
  { "HueSat",       "0300!06/xxyy0A00" },     // Hue, Sat
  { "Color",        "0300!07/xxxxyyyy0A00" }, // x, y (uint16)
  { "CT",           "0300!0A/xxxx0A00" },     // Color Temperature Mireds (uint16)
  { "ShutterOpen",  "0102!00"},
  { "ShutterClose", "0102!01"},
  { "ShutterStop",  "0102!02"},
  { "ShutterLift",  "0102!05xx"},           // Lift percentage, 0%=open, 100%=closed
  { "ShutterTilt",  "0102!08xx"},           // Tilt percentage
};

#endif // USE_ZIGBEE
