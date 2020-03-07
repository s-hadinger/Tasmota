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

void ZigbeeHandleHue(uint16_t shortaddr, uint32_t device_id, String &response) {
  uint8_t  power, colormode, bri, sat;
  uint16_t ct, hue;
  float    x, y;
  int code = 200;

  bool resp = false;  // is the response non null (add comma between parameters)
  bool on = false;

  uint8_t bulbtype = zigbee_devices.getAlexaBulbtype(shortaddr);

  if (WebServer->args()) {
    response = "[";

    StaticJsonBuffer<400> jsonBuffer;
    JsonObject &hue_json = jsonBuffer.parseObject(WebServer->arg((WebServer->args())-1));
    if (hue_json.containsKey("on")) {

      response += FPSTR(HUE_LIGHT_RESPONSE_JSON);
      response.replace("{id", String(EncodeLightId(0, shortaddr)));
      response.replace("{cm", "on");
      on = hue_json["on"];
      switch(on)
      {
        case false : // TODO
                    response.replace("{re", "false");
                    break;
        case true  : // TODO
                    response.replace("{re", "true");
                    break;
        default    : response.replace("{re", (power & 1) ? "true" : "false");
                    break;
      }
      resp = true;
    }

    if (hue_json.containsKey("bri")) {             // Brightness is a scale from 1 (the minimum the light is capable of) to 254 (the maximum). Note: a brightness of 1 is not off.
      bri = hue_json["bri"];
      if (resp) { response += ","; }
      response += FPSTR(HUE_LIGHT_RESPONSE_JSON);
      response.replace("{id", String(shortaddr));
      response.replace("{cm", "bri");
      response.replace("{re", String(bri));
      if (bri > 254) { bri = 254; }               // limit to 254
      if (LST_SINGLE <= bulbtype) {
        // TODO change
      }
      resp = true;
    }
    // handle xy before Hue/Sat
    // If the request contains both XY and HS, we wan't to give priority to HS
    if (hue_json.containsKey("xy")) {
      float x, y;
      x = hue_json["xy"][0];
      y = hue_json["xy"][1];
      if (resp) { response += ","; }
      response += FPSTR(HUE_LIGHT_RESPONSE_JSON);
      response.replace("{id", String(shortaddr));
      response.replace("{cm", "xy");
      response.replace("{re", "[" + String(x, 5) + "," + String(y, 5) + "]");
      resp = true;
      // TODO change
    }
    if (hue_json.containsKey("hue")) {             // The hue value is a wrapping value between 0 and 65535. Both 0 and 65535 are red, 25500 is green and 46920 is blue.
      hue = hue_json["hue"];
      if (resp) { response += ","; }
      response += FPSTR(HUE_LIGHT_RESPONSE_JSON);
      response.replace("{id", String(shortaddr));
      response.replace("{cm", "hue");
      response.replace("{re", String(hue));
      if (LST_RGB <= bulbtype) {
        uint8_t hue8 = changeUIntScale(hue, 0, 65535, 0, 254);
        // TODO
      }
      resp = true;
    }
    if (hue_json.containsKey("sat")) {             // Saturation of the light. 254 is the most saturated (colored) and 0 is the least saturated (white).
      sat = hue_json["sat"];
      if (resp) { response += ","; }
      response += FPSTR(HUE_LIGHT_RESPONSE_JSON);
      response.replace("{id", String(shortaddr));
      response.replace("{cm", "sat");
      response.replace("{re", String(sat));
      if (LST_RGB <= bulbtype) {
        // extend sat value if set to max
        if (254 <= sat) { sat = 255; }
        // TODO
      }
      resp = true;
    }
    if (hue_json.containsKey("ct")) {  // Color temperature 153 (Cold) to 500 (Warm)
      ct = hue_json["ct"];
      if (resp) { response += ","; }
      response += FPSTR(HUE_LIGHT_RESPONSE_JSON);
      response.replace("{id", String(shortaddr));
      response.replace("{cm", "ct");
      response.replace("{re", String(ct));
      if ((LST_COLDWARM == bulbtype) || (LST_RGBW <= bulbtype)) {
        // TODO
      }
      resp = true;
    }
    response += "]";
    if (2 == response.length()) {
      response = FPSTR(HUE_ERROR_JSON);
    }
  }
  else {
    response = FPSTR(HUE_ERROR_JSON);
  }
  AddLog_P2(LOG_LEVEL_DEBUG_MORE, PSTR(D_LOG_HTTP D_HUE " Result (%s)"), response.c_str());
  WSSend(code, CT_JSON, response);
}

#endif // USE_ZIGBEE
