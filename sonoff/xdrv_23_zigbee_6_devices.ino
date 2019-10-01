/*
  xdrv_23_zigbee.ino - zigbee support for Sonoff-Tasmota

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

#include <vector>
#include <map>

typedef struct Z_Device {
  uint16_t              shortaddr;
  uint64_t              longaddr;       // 0x00 means unspecified
  std::vector<uint32_t> endpoints;      // encoded as high 16 bits is endpoint, low 16 bits is ProfileId
  std::vector<uint32_t> clusters_in;    // encoded as high 16 bits is endpoint, low 16 bits is cluster number
  std::vector<uint32_t> clusters_out;   // encoded as high 16 bits is endpoint, low 16 bits is cluster number
} Z_Device;

class Z_Devices {
public:
  Z_Devices() {};

  // Add new device, provide ShortAddr and optional longAddr
  void addDevice(uint16_t shortaddr, uint64_t longaddr = 0);

  // Add an endpoint to a device
  void addEndoint(uint16_t shortaddr, uint8_t endpoint);

  // Add endpoint profile
  void addEndointProfile(uint16_t shortaddr, uint8_t endpoint, uint16_t profileId);

  // Add cluster
  void addCluster(uint16_t shortaddr, uint8_t endpoint, uint16_t cluster, bool out);

  // Dump json
  String dump(void) const;

private:
  std::map<uint16_t, Z_Device> _devices = {};

  // add Short and Long address when it is known not to be present, true if added
  bool addIfNotPresent(uint16_t shortaddr, uint64_t longaddr = 0);

  template < typename T>
  static bool findInVector(const std::vector<T>  & vecOfElements, const T  & element);

  template < typename T>
  static int32_t findEndpointInVector(const std::vector<T>  & vecOfElements, const T  & element);
};

Z_Devices zigbee_devices = Z_Devices();

// https://thispointer.com/c-how-to-find-an-element-in-vector-and-get-its-index/
template < typename T>
bool Z_Devices::findInVector(const std::vector<T>  & vecOfElements, const T  & element) {
	// Find given element in vector
	auto it = std::find(vecOfElements.begin(), vecOfElements.end(), element);

	if (it != vecOfElements.end()) {
		return true;
	} else {
		return false;
	}
}

template < typename T>
int32_t Z_Devices::findEndpointInVector(const std::vector<T>  & vecOfElements, const T  & element) {
	// Find given element in vector

  int32_t found = 0;
  for (auto &elem : vecOfElements) {
    if ((elem >> 16) & 0xFF == element) { return found; }
    found++;
  }

  return -1;
}

// insert an entry when it is known it is missing
bool Z_Devices::addIfNotPresent(uint16_t shortaddr, uint64_t longaddr) {
  if (0 == _devices.count(shortaddr)) {
    Z_Device device = { shortaddr, longaddr,
                        std::vector<uint32_t>(),
                        std::vector<uint32_t>(),
                        std::vector<uint32_t>() };
    _devices[shortaddr] = device;
    return true;
  }
  return false;
}

void Z_Devices::addDevice(uint16_t shortaddr, uint64_t longaddr) {
  if (!addIfNotPresent(shortaddr, longaddr)) {
    // if already present
    Z_Device &device = _devices[shortaddr];
    if (device.longaddr != longaddr) {
      // new device, i.e. collision
      device.longaddr = longaddr;
      device.endpoints.clear();
      device.clusters_in.clear();
      device.clusters_out.clear();
    }
  }
}

void Z_Devices::addEndoint(uint16_t shortaddr, uint8_t endpoint) {
  uint32_t ep_profile = (endpoint << 16);
  addIfNotPresent(shortaddr);
  Z_Device &device = _devices[shortaddr];
  if (findEndpointInVector(device.endpoints, ep_profile) < 0) {    // TODO search only on enpoint
    device.endpoints.push_back(ep_profile);
  }
}

void Z_Devices::addEndointProfile(uint16_t shortaddr, uint8_t endpoint, uint16_t profileId) {
  uint32_t ep_profile = (endpoint << 16) | profileId;
  addIfNotPresent(shortaddr);
  Z_Device &device = _devices[shortaddr];
  int32_t found = findEndpointInVector(device.endpoints, ep_profile);
  if (found < 0) {    // TODO search only on enpoint
    device.endpoints.push_back(ep_profile);
  } else {
    device.endpoints[found] = ep_profile;
  }
}

void Z_Devices::addCluster(uint16_t shortaddr, uint8_t endpoint, uint16_t cluster, bool out) {
  addIfNotPresent(shortaddr);
  Z_Device &device = _devices[shortaddr];
  uint32_t ep_cluster = (endpoint << 16) | cluster;
  if (!out) {
    if (!findInVector(device.clusters_in, ep_cluster)) {
      device.clusters_in.push_back(ep_cluster);
    }
  } else { // out
    if (!findInVector(device.clusters_out, ep_cluster)) {
      device.clusters_out.push_back(ep_cluster);
    }
  }
}

String Z_Devices::dump(void) const {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  JsonObject& devices = json.createNestedObject(F("ZigbeeDevices"));

  for (std::map<uint16_t, Z_Device>::const_iterator it = _devices.begin(); it != _devices.end(); ++it) {
    uint16_t shortaddr = it->first;
    const Z_Device& device = it->second;
    char hex[20];

    snprintf_P(hex, sizeof(hex), PSTR("0x%04X"), shortaddr);
    JsonObject& dev = devices.createNestedObject(hex);
    dev[F("ShortAddr")] = hex;

    Uint64toHex(device.longaddr, hex, 64);
    dev[F("IEEEAddr")] = hex;

    JsonArray& dev_endpoints = dev.createNestedArray(F("Endpoints"));
    for (std::vector<uint32_t>::const_iterator ite = device.endpoints.begin() ; ite != device.endpoints.end(); ++ite) {
      uint32_t ep_profile = *ite;
      uint8_t endpoint = (ep_profile >> 16) & 0xFF;
      uint16_t profileId = ep_profile & 0xFFFF;

      snprintf_P(hex, sizeof(hex), PSTR("%02X-%04X"), endpoint, profileId);
      dev_endpoints.add(hex);
    }

    JsonObject& dev_clusters_in = dev.createNestedObject(F("Clusters_in"));
    for (std::vector<uint32_t>::const_iterator itc = device.clusters_in.begin() ; itc != device.clusters_in.end(); ++itc) {
      uint16_t cluster = *itc & 0xFFFF;
      uint8_t  endpoint = (*itc >> 16) & 0xFF;

      snprintf_P(hex, sizeof(hex), PSTR("0x%02X"), endpoint);
      if (!dev_clusters_in.containsKey(hex)) {
        dev_clusters_in.createNestedArray(hex);
      }
      JsonArray &cluster_arr = dev_clusters_in[hex];

      snprintf_P(hex, sizeof(hex), PSTR("0x%04X"), cluster);
      cluster_arr.add(hex);
    }

    JsonObject& dev_clusters_out = dev.createNestedObject(F("Clusters_out"));
    for (std::vector<uint32_t>::const_iterator itc = device.clusters_out.begin() ; itc != device.clusters_out.end(); ++itc) {
      uint16_t cluster = *itc & 0xFFFF;
      uint8_t  endpoint = (*itc >> 16) & 0xFF;

      snprintf_P(hex, sizeof(hex), PSTR("0x%02X"), endpoint);
      if (!dev_clusters_out.containsKey(hex)) {
        dev_clusters_out.createNestedArray(hex);
      }
      JsonArray &cluster_arr = dev_clusters_out[hex];

      snprintf_P(hex, sizeof(hex), PSTR("0x%04X"), cluster);
      cluster_arr.add(hex);
    }
  }
  String payload = "";
  payload.reserve(200);
  json.printTo(payload);
  return payload;
}

#endif // USE_ZIGBEE
