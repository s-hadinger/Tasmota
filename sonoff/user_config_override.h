/*
  user_config_override.h - user configuration overrides my_user_config.h for Sonoff-Tasmota

  Copyright (C) 2019  Theo Arends

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

#ifndef _USER_CONFIG_OVERRIDE_H_
#define _USER_CONFIG_OVERRIDE_H_

// force the compiler to show a warning to confirm that this file is included
#warning **** user_config_override.h: Using Settings from this File ****

/*****************************************************************************************************\
 * USAGE:
 *   To modify the stock configuration without changing the my_user_config.h file:
 *   (1) copy this file to "user_config_override.h" (It will be ignored by Git)
 *   (2) define your own settings below
 *   (3) for platformio:
 *         define USE_CONFIG_OVERRIDE as a build flags.
 *         ie1 : export PLATFORMIO_BUILD_FLAGS='-DUSE_CONFIG_OVERRIDE'
 *         ie2 : enable in file platformio.ini "build_flags = -Wl,-Tesp8266.flash.1m0.ld -DUSE_CONFIG_OVERRIDE"
 *       for Arduino IDE:
 *         enable define USE_CONFIG_OVERRIDE in my_user_config.h
 ******************************************************************************************************
 * ATTENTION:
 *   - Changes to SECTION1 PARAMETER defines will only override flash settings if you change define CFG_HOLDER.
 *   - Expect compiler warnings when no ifdef/undef/endif sequence is used.
 *   - You still need to update my_user_config.h for major define USE_MQTT_TLS.
 *   - All parameters can be persistent changed online using commands via MQTT, WebConsole or Serial.
\*****************************************************************************************************/

/*
Examples :

// -- Master parameter control --------------------
#undef  CFG_HOLDER
#define CFG_HOLDER        4617                   // [Reset 1] Change this value to load SECTION1 configuration parameters to flash

// -- Setup your own Wifi settings  ---------------
#undef  STA_SSID1
#define STA_SSID1         "YourSSID"             // [Ssid1] Wifi SSID

#undef  STA_PASS1
#define STA_PASS1         "YourWifiPassword"     // [Password1] Wifi password

// -- Setup your own MQTT settings  ---------------
#undef  MQTT_HOST
#define MQTT_HOST         "your-mqtt-server.com" // [MqttHost]

#undef  MQTT_PORT
#define MQTT_PORT         1883                   // [MqttPort] MQTT port (10123 on CloudMQTT)

#undef  MQTT_USER
#define MQTT_USER         "YourMqttUser"         // [MqttUser] Optional user

#undef  MQTT_PASS
#define MQTT_PASS         "YourMqttPass"         // [MqttPassword] Optional password

// You might even pass some parameters from the command line ----------------------------
// Ie:  export PLATFORMIO_BUILD_FLAGS='-DUSE_CONFIG_OVERRIDE -DMY_IP="192.168.1.99" -DMY_GW="192.168.1.1" -DMY_DNS="192.168.1.1"'

#ifdef MY_IP
#undef  WIFI_IP_ADDRESS
#define WIFI_IP_ADDRESS   MY_IP                  // Set to 0.0.0.0 for using DHCP or enter a static IP address
#endif

#ifdef MY_GW
#undef  WIFI_GATEWAY
#define WIFI_GATEWAY      MY_GW                  // if not using DHCP set Gateway IP address
#endif

#ifdef MY_DNS
#undef  WIFI_DNS
#define WIFI_DNS          MY_DNS                 // If not using DHCP set DNS IP address (might be equal to WIFI_GATEWAY)
#endif

*/


// -- MQTT - Domoticz -----------------------------
#undef USE_DOMOTICZ                             // Enable Domoticz (+6k code, +0.3k mem)

// -- MQTT - Home Assistant Discovery -------------
#undef USE_HOME_ASSISTANT                       // Enable Home Assistant Discovery Support (+7k code)

// -- MQTT - TLS - AWS IoT ------------------------
// Using TLS starting with version v6.5.0.16 compilation will only work using Core 2.4.2 and 2.5.2. No longer supported: 2.3.0
#define USE_MQTT_TLS                             // Use TLS for MQTT connection (+34.5k code, +7.0k mem and +4.8k additional during connection handshake)
  #define USE_MQTT_TLS_CA_CERT                   // Force full CA validation instead of fingerprints, slower, but simpler to use (+2.2k code, +1.9k mem during connection handshake)
//  #define USE_MQTT_TLS_FORCE_EC_CIPHER           // Force Elliptic Curve cipher (higher security) required by some servers (automatically enabled with USE_MQTT_AWS_IOT) (+11.4k code, +0.4k mem)
  #define USE_MQTT_AWS_IOT                       // Enable MQTT for AWS IoT - requires a private key (+11.9k code, +0.4k mem)
                                                 //   Note: you need to generate a private key + certificate per device and update 'sonoff/sonoff_aws_iot.cpp'
                                                 //   Full documentation here: https://github.com/arendst/Sonoff-Tasmota/wiki/AWS-IoT

// -- KNX IP Protocol -----------------------------
#undef USE_KNX                                  // Enable KNX IP Protocol Support (+9.4k code, +3k7 mem)

// -- mDNS ----------------------------------------
#undef USE_DISCOVERY                            // Enable mDNS for the following services (+8k code or +23.5k code with core 2_5_x, +0.3k mem)

// -- Optional modules ----------------------------
#undef USE_BUZZER                               // Add support for a buzzer (+0k6 code)
#undef USE_SONOFF_IFAN                          // Add support for Sonoff iFan02 and iFan03 (+2k code)
#undef USE_TUYA_DIMMER                          // Add support for Tuya Serial Dimmer
#undef USE_ARMTRONIX_DIMMERS                    // Add support for Armtronix Dimmers (+1k4 code)
#undef USE_PS_16_DZ                             // Add support for PS-16-DZ Dimmer and Sonoff L1 (+2k code)

// -- One wire sensors ----------------------------
#undef USE_DS18x20                              // Optional for more than one DS18x20 sensors with id sort, single scan and read retry (+1k3 code)

// -- I2C sensors ---------------------------------
#undef USE_I2C                                  // I2C using library wire (+10k code, 0k2 mem, 124 iram)

// -- SPI sensors ---------------------------------
#undef USE_SPI                                  // Hardware SPI using GPIO12(MISO), GPIO13(MOSI) and GPIO14(CLK) in addition to two user selectable GPIOs(CS and DC)

// -- Serial sensors ------------------------------
#undef USE_MHZ19                                // Add support for MH-Z19 CO2 sensor (+2k code)
#undef USE_SENSEAIR                             // Add support for SenseAir K30, K70 and S8 CO2 sensor (+2k3 code)
#undef USE_PMS5003                              // Add support for PMS5003 and PMS7003 particle concentration sensor (+1k3 code)
#undef USE_NOVA_SDS                             // Add support for SDS011 and SDS021 particle concentration sensor (+0k7 code)
#undef USE_SERIAL_BRIDGE                        // Add support for software Serial Bridge (+0k8 code)

// Power monitoring sensors -----------------------
//#undef USE_ENERGY_MARGIN_DETECTION              // Add support for Energy Margin detection (+1k6 code)
#undef USE_PZEM004T                             // Add support for PZEM004T Energy monitor (+2k code)
#undef USE_PZEM_AC                              // Add support for PZEM014,016 Energy monitor (+1k1 code)
#undef USE_PZEM_DC                              // Add support for PZEM003,017 Energy monitor (+1k1 code)
#undef USE_MCP39F501                            // Add support for MCP39F501 Energy monitor as used in Shelly 2 (+3k1 code)

// -- Low level interface devices -----------------
#undef USE_DHT                                  // Add support for DHT11, AM2301 (DHT21, DHT22, AM2302, AM2321) and SI7021 Temperature and Humidity sensor (1k6 code)

// -- Rules or Script  ----------------------------
// Select none or only one of the below defines
#undef USE_RULES                                // Add support for rules (+8k code)
#define USE_SCRIPT                               // Add support for script (+17k code)
  //#define USE_SCRIPT_FATFS 4                     // Script: Add FAT FileSystem Support
#define USE_RF_SENSOR                            // Add support for RF sensor receiver (434MHz or 868MHz) (+0k8 code)

// -- Zigbee interface ----------------------------
#define USE_ZIGBEE                               // Enable serial communication with Zigbee CC2530 flashed with ZNP
  #undef USE_ZIGBEE_CHANNEL
  #define USE_ZIGBEE_CHANNEL  26                  // Zigbee Channel (11-26)

// ------------------------------------------------


#undef USE_IR_REMOTE                            // Send IR remote commands using library IRremoteESP8266 and ArduinoJson (+4k3 code, 0k3 mem, 48 iram)

#undef USE_WS2812                               // WS2812 Led string using library NeoPixelBus (+5k code, +1k mem, 232 iram) - Disable by //

#undef USE_ARILUX_RF                            // Add support for Arilux RF remote controller (+0k8 code, 252 iram (non 2.3.0))

#undef USE_SR04                                 // Add support for HC-SR04 ultrasonic devices (+1k code)

#undef USE_HX711                                // Add support for HX711 load cell (+1k5 code)

#undef USE_RF_FLASH                             // Add support for flashing the EFM8BB1 chip on the Sonoff RF Bridge. C2CK must be connected to GPIO4, C2D to GPIO5 on the PCB (+3k code)

//#undef USE_SM16716                              // Add support for SM16716 RGB LED controller (+0k7 code)

// // ------------------------------------------------
// #define USE_I2C
//   #define USE_DISPLAY                            // Add I2C Display Support (+2k code)

//     #define USE_DISPLAY_MODES1TO5                // Enable display mode 1 to 5 in addition to mode 0
//     #undef USE_DISPLAY_LCD                      // [DisplayModel 1] Enable Lcd display (I2C addresses 0x27 and 0x3F) (+6k code)
//     #define USE_DISPLAY_SSD1306                  // [DisplayModel 2] Enable SSD1306 Oled 128x64 display (I2C addresses 0x3C and 0x3D) (+16k code)
//     #undef USE_DISPLAY_MATRIX                   // [DisplayModel 3] Enable 8x8 Matrix display (I2C adresseses see below) (+11k code)
// #define SHOW_SPLASH	//Enable initialization splash message on the display
// #define USE_AWATCH	//Enables analog watch support
// // #define NUM_GRAPHS
// // #define USE_GRAPH	//Enable line charts. Also requires NUM_GRAPHS

#endif  // _USER_CONFIG_OVERRIDE_H_
