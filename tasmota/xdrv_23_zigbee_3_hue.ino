/*
  xdrv_23_zigbee.ino - zigbee support for Tasmota

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

// Add global functions for Hue Emulation

// idx: index in the list of zigbee_devices
void HueLightStatus1Zigbee(uint32_t idx, uint16_t shortaddr, uint8_t local_light_subtype, String *response) {
  uint8_t  power, colormode, bri, sat;
  uint16_t ct, hue;
  float    x, y;
  String light_status = "";
  uint32_t echo_gen = findEchoGeneration();   // 1 for 1st gen =+ Echo Dot 2nd gen, 2 for 2nd gen and above

  zigbee_devices.getAlexaState(shortaddr, &power, &colormode, &bri, &sat, &ct, &hue, &x, &y);

  //bri = LightGetBri(device);   // get Dimmer corrected with SetOption68
  if (bri > 254)  bri = 254;    // Philips Hue bri is between 1 and 254
  if (bri < 1)    bri = 1;
  if (sat > 254)  sat = 254;  // Philips Hue only accepts 254 as max hue
  uint8_t hue8 = changeUIntScale(hue, 0, 360, 0, 254);    // default hue is 0..254, we don't use extended hue

  *response += FPSTR(HUE_LIGHTS_STATUS_JSON1);
  response->replace("{state}", (power & 1) ? "true" : "false");

  // Brightness for all devices with PWM
  if ((1 == echo_gen) || (LST_SINGLE <= local_light_subtype)) { // force dimmer for 1st gen Echo
    light_status += "\"bri\":";
    light_status += String(bri);
    light_status += ",";
  }
  if (LST_COLDWARM <= local_light_subtype) {
    light_status += F("\"colormode\":\"");
    if (1 == colormode) {
      light_status += "xy";
    } else if (2 == colormode) {
      light_status += "ct";
    } else {
      light_status += "hs";
    }
    light_status += "\",";
  }
  if (LST_RGB <= local_light_subtype) {  // colors
    light_status += "\"xy\":[";
    light_status += String(x, 5);
    light_status += ",";
    light_status += String(y, 5);
    light_status += "],";
    
    light_status += "\"hue\":";
    light_status += String(hue);
    light_status += ",";

    light_status += "\"sat\":";
    light_status += String(sat);
    light_status += ",";
  }
  if (LST_COLDWARM == local_light_subtype || LST_RGBW <= local_light_subtype) {  // white temp
    light_status += "\"ct\":";
    light_status += String(ct > 0 ? ct : 284);  // if no ct, default to medium white
    light_status += ",";
  }
  response->replace("{light_status}", light_status);
}

void HueLightStatus2Zigbee(uint32_t idx, uint16_t shortaddr, String *response)
{
  *response += FPSTR(HUE_LIGHTS_STATUS_JSON2);
  const String &friendlyName = zigbee_devices.devicesAt(idx).friendlyName;
  if (friendlyName.length() > 0) {
    response->replace("{j1", friendlyName);
  } else {
    char shortaddrname[8];
    snprintf_P(shortaddrname, sizeof(shortaddrname), PSTR("0x%04X"), shortaddr);
    response->replace("{j1", shortaddrname);
  }
  response->replace("{j2", GetHueDeviceId(idx));
}

void ZigbeeCheckHue(String * response, bool &appending) {
  uint32_t zigbee_num = zigbee_devices.devicesSize();
  for (uint32_t i = 0; i < zigbee_num; i++) {
    int8_t bulbtype = zigbee_devices.devicesAt(i).bulbtype;

    if (bulbtype >= 0) {
      uint16_t shortaddr = zigbee_devices.devicesAt(i).shortaddr;
      // this bulb is advertized
      if (appending) { *response += ","; }
      *response += "\"";
      *response += EncodeLightId(0, shortaddr);
      *response += F("\":{\"state\":");
      HueLightStatus1Zigbee(i, shortaddr, bulbtype, response);    // TODO
      HueLightStatus2Zigbee(i, shortaddr, response);
      appending = true;
    }
  }
}

void ZigbeeHueGroups(String * lights) {
  uint32_t zigbee_num = zigbee_devices.devicesSize();
  for (uint32_t i = 0; i < zigbee_num; i++) {
    int8_t bulbtype = zigbee_devices.devicesAt(i).bulbtype;

    if (bulbtype >= 0) {
      *lights += ",\"";
      *lights += EncodeLightId(i);
      *lights += "\"";
    }
  }
}

#endif // USE_ZIGBEE
