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

#endif // USE_ZIGBEE
