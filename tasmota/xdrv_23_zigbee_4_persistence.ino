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

// Ensure persistence of devices into Flash
//
// Structure:
// (from file info):
// uint16 - start address in Flash (offset)
// uint16 - length in bytes (makes sure parsing stops)
//
// File structure:
// uint8 - number of devices, 0=none, 0xFF=invalid entry (probably Flash was erased)
//
// [Array of devices]
// [Offset = 2]
// uint8  - length of revice record
// uint16 - short address
// uint64 - long IEEE address
// uint8  - number of endpoints
// [Array of endpoints]
// uint8  - endpoint number
// uint16 - profileID of the endpoint
// Array of uint8 - clusters In  codes, 0xFF end marker
// Array of uint8 - clusters Out codes, 0xFF end marker
//
// str    - ModelID (null terminated C string, 32 chars max)
// str    - Manuf   (null terminated C string, 32 chars max)
// reserved for extensions

// encoding for the most commonly 32 clusters, used for binary encoding
const uint16_t Z_ClusterNumber[] PROGMEM = {
  0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007,
  0x0008, 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x000E, 0x000F,
  0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017,
  0x0018, 0x0019, 0x001A, 0x001B, 0x001C, 0x001D, 0x001E, 0x001F,
  0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027,
  0x0100, 0x0101, 0x0102,
  0x0201, 0x0202, 0x0203, 0x0204,
  0x0300, 0x0301,
  0x0400, 0x0401, 0x0402, 0x0403, 0x0404, 0x0405, 0x0406,
  0x0500, 0x0501, 0x0502,
  0x0700, 0x0701, 0x0702,
  0x0B00, 0x0B01, 0x0B02, 0x0B03, 0x0B04, 0x0B05,
  0x1000,
};

// convert a 1 byte cluster code to the actual cluster number
uint16_t fromClusterCode(uint8_t c) {
  if (c >= sizeof(Z_ClusterNumber)/sizeof(Z_ClusterNumber[0])) {
    return 0xFFFF;      // invalid
  }
  return pgm_read_word(&Z_ClusterNumber[c]);
}

// convert a cluster number to 1 byte, or 0xFF if not in table
uint8_t toClusterCode(uint16_t c) {
  for (uint32_t i = 0; i < sizeof(Z_ClusterNumber)/sizeof(Z_ClusterNumber[0]); i++) {
    if (c == pgm_read_word(&Z_ClusterNumber[i])) {
      return i;
    }
  }
  return 0xFF;        // not found
}

class SBuffer hibernateDevice(const struct Z_Device &device) {
  SBuffer buf(128);

  buf.add8(0x00);     // overall length, will be updated later
  buf.add16(device.shortaddr);
  buf.add64(device.longaddr);
  uint32_t endpoints = device.endpoints.size();
  if (endpoints > 254) { endpoints = 254; }
  buf.add8(endpoints);
  // iterate on endpoints
  for (std::vector<uint32_t>::const_iterator ite = device.endpoints.begin() ; ite != device.endpoints.end(); ++ite) {
    uint32_t ep_profile = *ite;
    uint8_t endpoint = (ep_profile >> 16) & 0xFF;
    uint16_t profileId = ep_profile & 0xFFFF;

    buf.add8(endpoint);
    buf.add16(profileId);
    for (std::vector<uint32_t>::const_iterator itc = device.clusters_in.begin() ; itc != device.clusters_in.end(); ++itc) {
      uint16_t cluster = *itc & 0xFFFF;
      uint8_t  c_endpoint = (*itc >> 16) & 0xFF;

      if (endpoint == c_endpoint) {
        uint8_t clusterCode = toClusterCode(cluster);
        if (0xFF != clusterCode) { buf.add8(clusterCode); }
      }
    }
    buf.add8(0xFF);      // end of endpoint marker

    for (std::vector<uint32_t>::const_iterator itc = device.clusters_out.begin() ; itc != device.clusters_out.end(); ++itc) {
      uint16_t cluster = *itc & 0xFFFF;
      uint8_t  c_endpoint = (*itc >> 16) & 0xFF;

      if (endpoint == c_endpoint) {
        uint8_t clusterCode = toClusterCode(cluster);
        if (0xFF != clusterCode) { buf.add8(clusterCode); }
      }
    }
    buf.add8(0xFF);      // end of endpoint marker
  }

  // ModelID
  size_t model_len = device.modelId.length();
  if (model_len > 32) { model_len = 32; }       // max 32 chars
  buf.addBuffer(device.modelId.c_str(), model_len);
  buf.add8(0x00);     // end of string marker

  // ManufID
  size_t manuf_len = device.manufacturerId.length();
  if (manuf_len > 32) {manuf_len = 32; }       // max 32 chars
  buf.addBuffer(device.manufacturerId.c_str(), manuf_len);
  buf.add8(0x00);     // end of string marker

  // FriendlyName
  size_t frname_len = device.friendlyName.length();
  if (frname_len > 32) {frname_len = 32; }       // max 32 chars
  buf.addBuffer(device.friendlyName.c_str(), frname_len);
  buf.add8(0x00);     // end of string marker

  // update overll length
  buf.set8(0, buf.len());
}

class SBuffer hibernateDevices(void) {
  SBuffer buf(2048);

  size_t devices_size = zigbee_devices.devicesSize();
  if (devices_size > 32) { devices_size = 32; }         // arbitrarily limit to 32 devices, for now
  buf.add8(devices_size);    // number of devices

  for (uint32_t i = 0; i < devices_size; i++) {
    const Z_Device & device = zigbee_devices.devicesAt(i);
    const SBuffer buf_device = hibernateDevice(device);
    buf.addBuffer(buf_device);
  }

  size_t buf_len = buf.len();
  if (buf_len > 2040) {
    AddLog_P2(LOG_LEVEL_ERROR, PSTR(D_LOG_ZIGBEE "Devices list too big to fit in Flash (%d)"), buf_len);
  }

  // Log
  char *hex_char = (char*) malloc((buf_len * 2) + 2);
  if (hex_char) {
    AddLog_P2(LOG_LEVEL_DEBUG, PSTR(D_LOG_ZIGBEE "ZigbeeFlashStore %s"),
                                    ToHex_P(buf.getBuffer(), buf_len, hex_char, (buf_len * 2) + 2));
    free(hex_char);
  }

  return buf;
}

#endif // USE_ZIGBEE
