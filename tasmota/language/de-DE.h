/*
  de-DE.h - localization for German - Germany for Tasmota

  Copyright (C) 2019  VinceMasuka

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

#ifndef _LANGUAGE_DE_DE_H_
#define _LANGUAGE_DE_DE_H_

/*************************** ATTENTION *******************************\
 *
 * Due to memory constraints only UTF-8 is supported.
 * To save code space keep text as short as possible.
 * Time and Date provided by SDK can not be localized (yet).
 * Use online command StateText to translate ON, OFF, HOLD and TOGGLE.
 * Use online command Prefix to translate cmnd, stat and tele.
 *
 * Updated until v6.6.0.21
\*********************************************************************/

//#define LANGUAGE_MODULE_NAME         // Enable to display "Module Generic" (ie Spanish), Disable to display "Generic Module" (ie English)

#define LANGUAGE_LCID 1031
// HTML (ISO 639-1) Language Code
#define D_HTML_LANGUAGE "de"

// "2017-03-07T11:08:02" - ISO8601:2004
#define D_YEAR_MONTH_SEPARATOR "."
#define D_MONTH_DAY_SEPARATOR "."
#define D_DATE_TIME_SEPARATOR " "
#define D_HOUR_MINUTE_SEPARATOR ":"
#define D_MINUTE_SECOND_SEPARATOR ":"

#define D_DAY3LIST "So Mo Di Mi Do Fr Sa "
#define D_MONTH3LIST "JanFebMärAprMaiJunJulAugSepOktNovDez"

// Non JSON decimal separator
#define D_DECIMAL_SEPARATOR "."

// Common
#define D_ADMIN "Admin"
#define D_AIR_QUALITY "Luftqualität"
#define D_AP "AP"                    // Access Point
#define D_AS "als"
#define D_AUTO "AUTO"
#define D_BLINK "Blinken"
#define D_BLINKOFF "BlinkenAus"
#define D_BOOT_COUNT "Anzahl Startvorgänge"
#define D_BRIGHTLIGHT "hell"
#define D_BSSID "BSSId"
#define D_BUTTON "Knopf"
#define D_BY "von"                   // Written by me
#define D_BYTES "Bytes"
#define D_CELSIUS "Celsius"
#define D_CHANNEL "Kanal"
#define D_CO2 "CO²"
#define D_CODE "code"                // Button code
#define D_COLDLIGHT "kalt"
#define D_COMMAND "Befehl"
#define D_CONNECTED "verbunden"
#define D_COUNT "zählen"
#define D_COUNTER "Zähler"
#define D_CURRENT "Strom"          // As in Voltage and Current
#define D_DATA "Daten"
#define D_DARKLIGHT "dunkel"
#define D_DEBUG "debug"
#define D_DISABLED "deaktiviert"
#define D_DISTANCE "Abstand"
#define D_DNS_SERVER "DNS-Server"
#define D_DONE "erledigt"
#define D_DST_TIME "DST"
#define D_ECO2 "eCO2"
#define D_EMULATION "Emulation"
#define D_ENABLED "aktiviert"
#define D_ERASE "löschen"
#define D_ERROR "Fehler"
#define D_FAHRENHEIT "Fahrenheit"
#define D_FAILED "fehlgeschlagen"
#define D_FALLBACK "Fallback"
#define D_FALLBACK_TOPIC "Fallback-Topic"
#define D_FALSE "falsch"
#define D_FILE "Datei"
#define D_FLOW_RATE "Durchflussmenge"
#define D_FREE_MEMORY "Freier Arbeitsspeicher"
#define D_FREQUENCY "Frequenz"
#define D_GAS "Gas"
#define D_GATEWAY "Gateway"
#define D_GROUP "Gruppe"
#define D_HOST "Host"
#define D_HOSTNAME "Hostname"
#define D_HUMIDITY "Feuchtigkeit"
#define D_ILLUMINANCE "Beleuchtungsintensität"
#define D_IMMEDIATE "direkt"      // Button immediate
#define D_INDEX "Index"
#define D_INFO "Info"
#define D_INFRARED "Infrarot"
#define D_INITIALIZED "initialisiert"
#define D_IP_ADDRESS "IP-Adresse"
#define D_LIGHT "Licht"
#define D_LWT "LWT"
#define D_MODULE "Modul"
#define D_MQTT "MQTT"
#define D_MULTI_PRESS "Mehrfachdruck"
#define D_NOISE "Lautstärke"
#define D_NONE "keine"
#define D_OFF "aus"
#define D_OFFLINE "Offline"
#define D_OK "OK"
#define D_ON "an"
#define D_ONLINE "Online"
#define D_PASSWORD "Passwort"
#define D_PORT "Port"
#define D_POWER_FACTOR "Leistungsfaktor"
#define D_POWERUSAGE "Leistung"
#define D_POWERUSAGE_ACTIVE "Wirkleistung"
#define D_POWERUSAGE_APPARENT "Scheinleistung"
#define D_POWERUSAGE_REACTIVE "Blindleistung"
#define D_PRESSURE "Luftdruck"
#define D_PRESSUREATSEALEVEL "Luftdruck auf Meereshöhe"
#define D_PROGRAM_FLASH_SIZE "Ges. Flash Speicher"
#define D_PROGRAM_SIZE "Ben. Flash Speicher"
#define D_PROJECT "Projekt"
#define D_RAIN "Regen"
#define D_RECEIVED "erhalten"
#define D_RESTART "Neustart"
#define D_RESTARTING "starte neu"
#define D_RESTART_REASON "Grund für Neustart"
#define D_RESTORE "Wiederherstellung"
#define D_RETAINED "beibehalten"
#define D_RULE "Regel"
#define D_SAVE "Speichern"
#define D_SENSOR "Sensor"
#define D_SSID "SSID"
#define D_START "Start"
#define D_STD_TIME "STD"
#define D_STOP "Stop"
#define D_SUBNET_MASK "Subnetzmaske"
#define D_SUBSCRIBE_TO "abonniere"
#define D_UNSUBSCRIBE_FROM "löse abo. von"
#define D_SUCCESSFUL "erfolgreich"
#define D_SUNRISE "Sonnenaufgang"
#define D_SUNSET "Sonnenuntergang"
#define D_TEMPERATURE "Temperatur"
#define D_TO "zu"
#define D_TOGGLE "An/Aus"
#define D_TOPIC "topic"
#define D_TOTAL_USAGE "Gesamtverbrauch"
#define D_TRANSMIT "Übertragen"
#define D_TRUE "wahr"
#define D_TVOC "TVOC"
#define D_UPGRADE "update"
#define D_UPLOAD "Upload"
#define D_UPTIME "Laufzeit"
#define D_USER "Benutzer"
#define D_UTC_TIME "UTC"
#define D_UV_INDEX "UV-Index"
#define D_UV_INDEX_1 "Niedrig"
#define D_UV_INDEX_2 "Mittel"
#define D_UV_INDEX_3 "Hoch"
#define D_UV_INDEX_4 "Intensiv"
#define D_UV_INDEX_5 "Gefährlich"
#define D_UV_INDEX_6 "Schädlich"
#define D_UV_INDEX_7 "Messwert!"
#define D_UV_LEVEL "UV-Level"
#define D_UV_POWER "UV Intensität"
#define D_VERSION "Version"
#define D_VOLTAGE "Spannung"
#define D_WEIGHT "Gewicht"
#define D_WARMLIGHT "warm"
#define D_WEB_SERVER "Web-Server"

// tasmota.ino
#define D_WARNING_MINIMAL_VERSION "ACHTUNG: Diese Version unterstützt keine persistenten Einstellungen"
#define D_LEVEL_10 "level 1-0"
#define D_LEVEL_01 "level 0-1"
#define D_SERIAL_LOGGING_DISABLED "Serielles Logging deaktiviert"
#define D_SYSLOG_LOGGING_REENABLED "Syslog-Logging aktiviert"

#define D_SET_BAUDRATE_TO "Setze Baudrate auf"
#define D_RECEIVED_TOPIC "empfangenes topic"
#define D_DATA_SIZE "Datengröße"
#define D_ANALOG_INPUT "Analog"

// support.ino
#define D_OSWATCH "osWatch"
#define D_BLOCKED_LOOP "Schleife blockiert."
#define D_WPS_FAILED_WITH_STATUS "WPS fehlgeschlagen mit Status"
#define D_ACTIVE_FOR_3_MINUTES "aktiv für 3 Minuten"
#define D_FAILED_TO_START "Starten fehlgeschlagen"
#define D_PATCH_ISSUE_2186 "Repariere Problem #2186"
#define D_CONNECTING_TO_AP "verbinden mit AP"
#define D_IN_MODE "in Modus"
#define D_CONNECT_FAILED_NO_IP_ADDRESS "Verbindung fehlgeschlagen, da keine IP-Adresse zugeteilt wurde"
#define D_CONNECT_FAILED_AP_NOT_REACHED "Verbindung fehlgeschlagen, da AP nicht erreicht werden konnte"
#define D_CONNECT_FAILED_WRONG_PASSWORD "Verbindung fehlgeschlagen, da das Passwort falsch ist"
#define D_CONNECT_FAILED_AP_TIMEOUT "Verbindung fehlgeschlagen, da der AP nicht antwortet (timeout)"
#define D_ATTEMPTING_CONNECTION "Verbindungsversuch..."
#define D_CHECKING_CONNECTION "Prüfe Verbindung..."
#define D_QUERY_DONE "Suchanfrage abgeschlossen. MQTT-Services gefunden"
#define D_MQTT_SERVICE_FOUND "MQTT-Service gefunden bei"
#define D_FOUND_AT "gefunden bei"
#define D_SYSLOG_HOST_NOT_FOUND "Syslog-Host nicht gefunden"

// settings.ino
#define D_SAVED_TO_FLASH_AT "in Flash gespeichert am"
#define D_LOADED_FROM_FLASH_AT "aus Flash geladen am"
#define D_USE_DEFAULTS "Standard verwenden"
#define D_ERASED_SECTOR "gelöschter Sektor"

// xdrv_02_webserver.ino
#define D_NOSCRIPT "JavaScript aktivieren um Tasmota benutzen zu können"
#define D_MINIMAL_FIRMWARE_PLEASE_UPGRADE "MINIMUM-Firmware<br>bitte upgraden"
#define D_WEBSERVER_ACTIVE_ON "Web-Server aktiv bei"
#define D_WITH_IP_ADDRESS "mit IP-Adresse"
#define D_WEBSERVER_STOPPED "Web-Server angehalten"
#define D_FILE_NOT_FOUND "Datei nicht gefunden"
#define D_REDIRECTED "umgeleitet zu captive portal"
#define D_WIFIMANAGER_SET_ACCESSPOINT_AND_STATION "WLAN-Manager AccessPoint gesetzt und behält Station"
#define D_WIFIMANAGER_SET_ACCESSPOINT "WLAN-Manager AccessPoint gesetzt"
#define D_TRYING_TO_CONNECT "Versuche Gerät mit Netzwerk zu verbinden"

#define D_RESTART_IN "Neustart in"
#define D_SECONDS "Sekunden"
#define D_DEVICE_WILL_RESTART "Gerät wird jetzt neu gestartet"
#define D_BUTTON_TOGGLE "An/Aus"
#define D_CONFIGURATION "Einstellungen"
#define D_INFORMATION "Informationen"
#define D_FIRMWARE_UPGRADE "Firmware Update"
#define D_CONSOLE "Konsole"
#define D_CONFIRM_RESTART "Wirklich neustarten?"

#define D_CONFIGURE_MODULE "Gerät konfigurieren"
#define D_CONFIGURE_WIFI "WLAN konfigurieren"
#define D_CONFIGURE_MQTT "MQTT konfigurieren"
#define D_CONFIGURE_DOMOTICZ "Domoticz konfigurieren"
#define D_CONFIGURE_LOGGING "Logging konfigurieren"
#define D_CONFIGURE_OTHER "Sonstige Konfiguration"
#define D_CONFIRM_RESET_CONFIGURATION "Zurücksetzen der Konfiguration bestätigen"
#define D_RESET_CONFIGURATION "Konfiguration zurücksetzen"
#define D_BACKUP_CONFIGURATION "Konfiguration sichern"
#define D_RESTORE_CONFIGURATION "Konfiguration wiederherstellen"
#define D_MAIN_MENU "Hauptmenü"

#define D_MODULE_PARAMETERS "Geräte-Einstellungen"
#define D_MODULE_TYPE "Gerätetyp"
#define D_PULLUP_ENABLE "Kein Taster/Schalter Pull-up"
#define D_ADC "ADC"
#define D_GPIO "GPIO"
#define D_SERIAL_IN "serieller Eingang [serial in]"
#define D_SERIAL_OUT "serieller Ausgang [serial out]"

#define D_WIFI_PARAMETERS "WLAN-Einstellungen"
#define D_SCAN_FOR_WIFI_NETWORKS "WLAN-Netzwerk suchen und auswählen"
#define D_SCAN_DONE "Suche abgeschlossen"
#define D_NO_NETWORKS_FOUND "Keine Netzwerke gefunden"
#define D_REFRESH_TO_SCAN_AGAIN "Aktualisieren, um erneut zu suchen"
#define D_DUPLICATE_ACCESSPOINT "AccessPoint duplizieren"
#define D_SKIPPING_LOW_QUALITY "überspringe wegen niedriger Qualität"
#define D_RSSI "RSSI"
#define D_WEP "WEP"
#define D_WPA_PSK "WPA-PSK"
#define D_WPA2_PSK "WPA2-PSK"
#define D_AP1_SSID "WLAN 1 - SSID"
#define D_AP1_PASSWORD "WLAN 1 - Passwort"
#define D_AP2_SSID "WLAN 2 - SSID"
#define D_AP2_PASSWORD "WLAN 2 - Passwort"

#define D_MQTT_PARAMETERS "MQTT-Einstellungen"
#define D_CLIENT "client"
#define D_FULL_TOPIC "full topic"

#define D_LOGGING_PARAMETERS "Logging-Einstellungen"
#define D_SERIAL_LOG_LEVEL "Seriell-Log Level"
#define D_MQTT_LOG_LEVEL "Mqtt-Log Level"
#define D_WEB_LOG_LEVEL "Web-Log Level"
#define D_SYS_LOG_LEVEL "Sys-Log Level"
#define D_MORE_DEBUG "Mehr Details"
#define D_SYSLOG_HOST "Sys-Log Host"
#define D_SYSLOG_PORT "Sys-Log Port"
#define D_TELEMETRY_PERIOD "Telemetrieperiode"

#define D_OTHER_PARAMETERS "Sonstige Einstellungen"
#define D_TEMPLATE "Vorlage"
#define D_ACTIVATE "Aktivieren"
#define D_WEB_ADMIN_PASSWORD "Passwort für Web Oberfläche"
#define D_MQTT_ENABLE "MQTT aktivieren"
#define D_FRIENDLY_NAME "Name [friendly name]"
#define D_BELKIN_WEMO "Belkin WeMo"
#define D_HUE_BRIDGE "Hue Bridge"
#define D_SINGLE_DEVICE "Einzelnes Gerät"
#define D_MULTI_DEVICE "Mehrfachgerät"

#define D_CONFIGURE_TEMPLATE "Vorlage konfigurieren"
#define D_TEMPLATE_PARAMETERS "Vorlage Parameter"
#define D_TEMPLATE_NAME "Name"
#define D_BASE_TYPE "basiert auf"
#define D_TEMPLATE_FLAGS "Options"

#define D_SAVE_CONFIGURATION "Konfiguration speichern"
#define D_CONFIGURATION_SAVED "Konfiguration gespeichert"
#define D_CONFIGURATION_RESET "Konfiguration zurücksetzen"

#define D_PROGRAM_VERSION "Tasmota Version"
#define D_BUILD_DATE_AND_TIME "Build-Datum & -Uhrzeit"
#define D_CORE_AND_SDK_VERSION "Core-/SDK-Version"
#define D_FLASH_WRITE_COUNT "Anz. Flash Schreibzugriffe"
#define D_MAC_ADDRESS "MAC-Adresse"
#define D_MQTT_HOST "MQTT Host"
#define D_MQTT_PORT "MQTT Port"
#define D_MQTT_CLIENT "MQTT Client"
#define D_MQTT_USER "MQTT Benutzer"
#define D_MQTT_TOPIC "MQTT Topic"
#define D_MQTT_GROUP_TOPIC "MQTT Group Topic"
#define D_MQTT_FULL_TOPIC "MQTT Full Topic"
#define D_MDNS_DISCOVERY "mDNS-Ermittlung"
#define D_MDNS_ADVERTISE "mDNS-Bekanntmachung"
#define D_ESP_CHIP_ID "ESP Chip ID"
#define D_FLASH_CHIP_ID "Flash Chip ID"
#define D_FLASH_CHIP_SIZE "Realer Flash Speicher"
#define D_FREE_PROGRAM_SPACE "Verf. Flash Speicher"

#define D_UPGRADE_BY_WEBSERVER "Update über Web-Server"
#define D_OTA_URL "OTA-URL"
#define D_START_UPGRADE "Update starten"
#define D_UPGRADE_BY_FILE_UPLOAD "Update Datei hochladen"
#define D_UPLOAD_STARTED "Upload gestartet"
#define D_UPGRADE_STARTED "Update gestartet"
#define D_UPLOAD_DONE "Upload abgeschlossen"
#define D_UPLOAD_ERR_1 "Keine Datei ausgewählt"
#define D_UPLOAD_ERR_2 "Ungenügend Speicherplatz"
#define D_UPLOAD_ERR_3 "Magic Byte ist nicht 0xE9"
#define D_UPLOAD_ERR_4 "Datei überschreitet vorhdn. Flashspeicher"
#define D_UPLOAD_ERR_5 "Upload Buffer Vergleich weicht ab"
#define D_UPLOAD_ERR_6 "Upload fehlgeschlagen. Aktiviere logging 3"
#define D_UPLOAD_ERR_7 "Upload abgebrochen"
#define D_UPLOAD_ERR_8 "Datei ungültig"
#define D_UPLOAD_ERR_9 "Datei zu groß"
#define D_UPLOAD_ERR_10 "RF Chip init fehlgeschlagen"
#define D_UPLOAD_ERR_11 "RF Chip löschen fehlgeschlagen"
#define D_UPLOAD_ERR_12 "RF Chip beschreiben fehlgeschlagen"
#define D_UPLOAD_ERR_13 "RF Firmware ungültig"
#define D_UPLOAD_ERROR_CODE "Upload Fehler Nummer"

#define D_ENTER_COMMAND "Befehl eingeben"
#define D_ENABLE_WEBLOG_FOR_RESPONSE "Aktivere Web Log Level 2 falls Reaktion erwartet"
#define D_NEED_USER_AND_PASSWORD "Benötige user=<Benutzername>&password=<Passwort>"

// xdrv_01_mqtt.ino
#define D_FINGERPRINT "TLS-Fingerabdruck wird verifiziert..."
#define D_TLS_CONNECT_FAILED_TO "TLS-Verbindung fehlgeschlagen an"
#define D_RETRY_IN "Wiederversuch in"
#define D_VERIFIED "verifiziert mit Fingerabdruck"
#define D_INSECURE "unsichere Verbindung aufgrund ungültigen Fingerabdrucks"
#define D_CONNECT_FAILED_TO "Verbindung fehlgeschlagen aufgrund von"

// xplg_wemohue.ino
#define D_MULTICAST_DISABLED "Multicast deaktiviert"
#define D_MULTICAST_REJOINED "Multicast (wieder-)verbunden"
#define D_MULTICAST_JOIN_FAILED "Multicast Verbindung fehlgeschlagen"
#define D_FAILED_TO_SEND_RESPONSE "Antwort senden fehlgeschlagen"

#define D_WEMO "WeMo"
#define D_WEMO_BASIC_EVENT "WeMo basic event"
#define D_WEMO_EVENT_SERVICE "WeMo event service"
#define D_WEMO_META_SERVICE "WeMo meta service"
#define D_WEMO_SETUP "WeMo-Setup"
#define D_RESPONSE_SENT "Antwort gesendet"

#define D_HUE "Hue"
#define D_HUE_BRIDGE_SETUP "Hue-Setup"
#define D_HUE_API_NOT_IMPLEMENTED "Hue-API nicht implementiert"
#define D_HUE_API "Hue-API"
#define D_HUE_POST_ARGS "Hue POST-Argumente"
#define D_3_RESPONSE_PACKETS_SENT "3 Antwortpakete gesendet"

// xdrv_07_domoticz.ino
#define D_DOMOTICZ_PARAMETERS "Domoticz-Parameter"
#define D_DOMOTICZ_IDX "Idx"
#define D_DOMOTICZ_KEY_IDX "Key idx"
#define D_DOMOTICZ_SWITCH_IDX "Switch idx"
#define D_DOMOTICZ_SENSOR_IDX "Sensor idx"
  #define D_DOMOTICZ_TEMP "Temp"
  #define D_DOMOTICZ_TEMP_HUM "Temp,Hum"
  #define D_DOMOTICZ_TEMP_HUM_BARO "Temp,Hum,Baro"
  #define D_DOMOTICZ_POWER_ENERGY "Power,Energy"
  #define D_DOMOTICZ_ILLUMINANCE "Illuminance"
  #define D_DOMOTICZ_COUNT "Count/PM1"
  #define D_DOMOTICZ_VOLTAGE "Voltage/PM2.5"
  #define D_DOMOTICZ_CURRENT "Current/PM10"
  #define D_DOMOTICZ_AIRQUALITY "AirQuality"
  #define D_DOMOTICZ_P1_SMART_METER "P1SmartMeter"
#define D_DOMOTICZ_UPDATE_TIMER "Update Zeitplan"

// xdrv_09_timers.ino
#define D_CONFIGURE_TIMER "Zeitplan konfigurieren"
#define D_TIMER_PARAMETERS "Zeitplan-Einstellungen"
#define D_TIMER_ENABLE "Zeitpläne aktivieren"
#define D_TIMER_ARM "Aktiv"
#define D_TIMER_TIME "Uhrzeit"
#define D_TIMER_DAYS "Wochentage"
#define D_TIMER_REPEAT "Wiederholen"
#define D_TIMER_OUTPUT "Ausgang"
#define D_TIMER_ACTION "Aktion"

// xdrv_10_knx.ino
#define D_CONFIGURE_KNX "KNX konfigurieren"
#define D_KNX_PARAMETERS "KNX-Parameter"
#define D_KNX_GENERAL_CONFIG "Allgemein"
#define D_KNX_PHYSICAL_ADDRESS "Physikalische Adresse"
#define D_KNX_PHYSICAL_ADDRESS_NOTE "( Muss einmalig im KNX-Netzwerk sein )"
#define D_KNX_ENABLE "KNX aktivieren"
#define D_KNX_GROUP_ADDRESS_TO_WRITE "Daten zum Senden an Gruppenadresse"
#define D_ADD "Hinzufügen"
#define D_DELETE "Löschen"
#define D_REPLY "Antworten"
#define D_KNX_GROUP_ADDRESS_TO_READ "Gruppenadresse zum Emfang von Daten"
#define D_LOG_KNX "KNX: "
#define D_RECEIVED_FROM "Empfangen von"
#define D_KNX_COMMAND_WRITE "Schreiben"
#define D_KNX_COMMAND_READ "Lesen"
#define D_KNX_COMMAND_OTHER "Andere"
#define D_SENT_TO "gesendet an"
#define D_KNX_WARNING "Die Gruppenadresse (0/0/0) ist reserviert und kann nicht verwendet werden."
#define D_KNX_ENHANCEMENT "Erweiterte Kommunikation"
#define D_KNX_TX_SLOT "KNX TX"
#define D_KNX_RX_SLOT "KNX RX"

// xdrv_03_energy.ino
#define D_ENERGY_TODAY "Energie heute"
#define D_ENERGY_YESTERDAY "Energie gestern"
#define D_ENERGY_TOTAL "Energie insgesamt"

// xdrv_27_shutter.ino
#define D_OPEN "Öffnen"
#define D_CLOSE "Schliessen"
#define D_DOMOTICZ_SHUTTER "Rollo"

// xdrv_28_pcf8574.ino
#define D_CONFIGURE_PCF8574 "Konfiguriere PCF8574"
#define D_PCF8574_PARAMETERS "PCF8574 Parameter"
#define D_INVERT_PORTS "Invertiere Ports"
#define D_DEVICE "Gerät"
#define D_DEVICE_INPUT "Eingang"
#define D_DEVICE_OUTPUT "Ausgang"

// xsns_05_ds18b20.ino
#define D_SENSOR_BUSY "Sensor beschäftigt"
#define D_SENSOR_CRC_ERROR "Sensor CRC-Fehler"
#define D_SENSORS_FOUND "Sensor gefunden"

// xsns_06_dht.ino
#define D_TIMEOUT_WAITING_FOR "Timeout während Warten auf"
#define D_START_SIGNAL_LOW "Startausschlag niedrig"
#define D_START_SIGNAL_HIGH "Startausschlag hoch"
#define D_PULSE "Puls"
#define D_CHECKSUM_FAILURE "Checksum-Fehler"

// xsns_07_sht1x.ino
#define D_SENSOR_DID_NOT_ACK_COMMAND "Sensor hat ACK-Befehl nicht ausgeführt"
#define D_SHT1X_FOUND "SHT1X gefunden"

// xsns_18_pms5003.ino
#define D_STANDARD_CONCENTRATION "CF-1 PM"     // Standard Particle CF-1 Particle Matter
#define D_ENVIRONMENTAL_CONCENTRATION "PM"     // Environmetal Particle Matter
#define D_PARTICALS_BEYOND "Partikel"

// xsns_32_mpu6050.ino
#define D_AX_AXIS "Beschl. X-Achse"
#define D_AY_AXIS "Beschl. Y-Achse"
#define D_AZ_AXIS "Beschl. Z-Achse"
#define D_GX_AXIS "Gyroskop X-Achse"
#define D_GY_AXIS "Gyroskop Y-Achse"
#define D_GZ_AXIS "Gyroskop Z-Achse"

// xsns_34_hx711.ino
#define D_HX_CAL_REMOVE "Wägegut entfernen"
#define D_HX_CAL_REFERENCE "Referenzgewicht auflegen"
#define D_HX_CAL_DONE "kalibriert"
#define D_HX_CAL_FAIL "Kalibrierung fehlgeschlagen"
#define D_RESET_HX711 "Tara"
#define D_CONFIGURE_HX711 "Tara Wert?"
#define D_HX711_PARAMETERS "Skala Parameter"
#define D_ITEM_WEIGHT "Wägegut Gewicht"
#define D_REFERENCE_WEIGHT "Referenz Gewicht"
#define D_CALIBRATE "kalibriert"
#define D_CALIBRATION "Kalibrierung"

//xsns_35_tx20.ino
#define D_TX20_WIND_DIRECTION "Wind Richtung"
#define D_TX20_WIND_SPEED "Windgeschwindigkeit"
#define D_TX20_WIND_SPEED_AVG "Ø Windgeschwindigkeit"
#define D_TX20_WIND_SPEED_MAX "max Windgeschwindigkeit"
#define D_TX20_NORTH "N"
#define D_TX20_EAST "O"
#define D_TX20_SOUTH "S"
#define D_TX20_WEST "W"

//xsns_43_hre.ino
#define D_LOG_HRE "HRE: "

// tasmota_template.h - keep them as short as possible to be able to fit them in GUI drop down box
#define D_SENSOR_NONE          "None"
#define D_SENSOR_USER          "User"
#define D_SENSOR_DHT11         "DHT11"
#define D_SENSOR_AM2301        "AM2301"
#define D_SENSOR_SI7021        "SI7021"
#define D_SENSOR_DS18X20       "DS18x20"
#define D_SENSOR_I2C_SCL       "I2C SCL"
#define D_SENSOR_I2C_SDA       "I2C SDA"
#define D_SENSOR_WS2812        "WS2812"
#define D_SENSOR_DFR562        "MP3 Player"
#define D_SENSOR_IRSEND        "IRsend"
#define D_SENSOR_SWITCH        "Switch"     // Suffix "1"
#define D_SENSOR_BUTTON        "Button"     // Suffix "1"
#define D_SENSOR_RELAY         "Relay"      // Suffix "1i"
#define D_SENSOR_LED           "Led"        // Suffix "1i"
#define D_SENSOR_LED_LINK      "LedLink"    // Suffix "i"
#define D_SENSOR_PWM           "PWM"        // Suffix "1"
#define D_SENSOR_COUNTER       "Counter"    // Suffix "1"
#define D_SENSOR_IRRECV        "IRrecv"
#define D_SENSOR_MHZ_RX        "MHZ Rx"
#define D_SENSOR_MHZ_TX        "MHZ Tx"
#define D_SENSOR_PZEM004_RX    "PZEM004 Rx"
#define D_SENSOR_PZEM016_RX    "PZEM016 Rx"
#define D_SENSOR_PZEM017_RX    "PZEM017 Rx"
#define D_SENSOR_PZEM0XX_TX    "PZEM0XX Tx"
#define D_SENSOR_SAIR_RX       "SAir Rx"
#define D_SENSOR_SAIR_TX       "SAir Tx"
#define D_SENSOR_SPI_CS        "SPI CS"
#define D_SENSOR_SPI_DC        "SPI DC"
#define D_SENSOR_SPI_MISO      "SPI MISO"
#define D_SENSOR_SPI_MOSI      "SPI MOSI"
#define D_SENSOR_SPI_CLK       "SPI CLK"
#define D_SENSOR_BACKLIGHT     "Backlight"
#define D_SENSOR_PMS5003       "PMS5003"
#define D_SENSOR_SDS0X1_RX     "SDS0X1 Rx"
#define D_SENSOR_SDS0X1_TX     "SDS0X1 Tx"
#define D_SENSOR_HPMA_RX       "HPMA Rx"
#define D_SENSOR_HPMA_TX       "HPMA Tx"
#define D_SENSOR_SBR_RX        "SerBr Rx"
#define D_SENSOR_SBR_TX        "SerBr Tx"
#define D_SENSOR_SR04_TRIG     "SR04 Tri"
#define D_SENSOR_SR04_ECHO     "SR04 Ech"
#define D_SENSOR_SDM120_TX     "SDMx20 Tx"
#define D_SENSOR_SDM120_RX     "SDMx20 Rx"
#define D_SENSOR_SDM630_TX     "SDM630 Tx"
#define D_SENSOR_SDM630_RX     "SDM630 Rx"
#define D_SENSOR_TM1638_CLK    "TM16 CLK"
#define D_SENSOR_TM1638_DIO    "TM16 DIO"
#define D_SENSOR_TM1638_STB    "TM16 STB"
#define D_SENSOR_HX711_SCK     "HX711 SCK"
#define D_SENSOR_HX711_DAT     "HX711 DAT"
#define D_SENSOR_TX20_TX       "TX20"
#define D_SENSOR_RFSEND        "RFSend"
#define D_SENSOR_RFRECV        "RFrecv"
#define D_SENSOR_TUYA_TX       "Tuya Tx"
#define D_SENSOR_TUYA_RX       "Tuya Rx"
#define D_SENSOR_MGC3130_XFER  "MGC3130 Xfr"
#define D_SENSOR_MGC3130_RESET "MGC3130 Rst"
#define D_SENSOR_SSPI_MISO     "SSPI MISO"
#define D_SENSOR_SSPI_MOSI     "SSPI MOSI"
#define D_SENSOR_SSPI_SCLK     "SSPI SCLK"
#define D_SENSOR_SSPI_CS       "SSPI CS"
#define D_SENSOR_SSPI_DC       "SSPI DC"
#define D_SENSOR_RF_SENSOR     "RF Sensor"
#define D_SENSOR_AZ_RX         "AZ Rx"
#define D_SENSOR_AZ_TX         "AZ Tx"
#define D_SENSOR_MAX31855_CS   "MX31855 CS"
#define D_SENSOR_MAX31855_CLK  "MX31855 CLK"
#define D_SENSOR_MAX31855_DO   "MX31855 DO"
#define D_SENSOR_NRG_SEL       "HLWBL SEL"  // Suffix "i"
#define D_SENSOR_NRG_CF1       "HLWBL CF1"
#define D_SENSOR_HLW_CF        "HLW8012 CF"
#define D_SENSOR_HJL_CF        "BL0937 CF"
#define D_SENSOR_MCP39F5_TX    "MCP39F5 Tx"
#define D_SENSOR_MCP39F5_RX    "MCP39F5 Rx"
#define D_SENSOR_MCP39F5_RST   "MCP39F5 Rst"
#define D_SENSOR_CSE7766_TX    "CSE7766 Tx"
#define D_SENSOR_CSE7766_RX    "CSE7766 Rx"
#define D_SENSOR_PN532_TX      "PN532 Tx"
#define D_SENSOR_PN532_RX      "PN532 Rx"
#define D_SENSOR_SM16716_CLK   "SM16716 CLK"
#define D_SENSOR_SM16716_DAT   "SM16716 DAT"
#define D_SENSOR_SM16716_POWER "SM16716 PWR"
#define D_SENSOR_MY92X1_DI     "MY92x1 DI"
#define D_SENSOR_MY92X1_DCKI   "MY92x1 DCKI"
#define D_SENSOR_ARIRFRCV      "ALux IrRcv"
#define D_SENSOR_ARIRFSEL      "ALux IrSel"
#define D_SENSOR_TXD           "Serial Tx"
#define D_SENSOR_RXD           "Serial Rx"
#define D_SENSOR_ROTARY        "Rotary"     // Suffix "1A"
#define D_SENSOR_HRE_CLOCK     "HRE Clock"
#define D_SENSOR_HRE_DATA      "HRE Data"
#define D_SENSOR_ADE7953_IRQ   "ADE7953 IRQ"
#define D_SENSOR_BUZZER        "Buzzer"
#define D_SENSOR_OLED_RESET    "OLED Reset"
#define D_SENSOR_ZIGBEE_TXD    "Zigbee Tx"
#define D_SENSOR_ZIGBEE_RXD    "Zigbee Rx"
#define D_SENSOR_SOLAXX1_TX    "SolaxX1 Tx"
#define D_SENSOR_SOLAXX1_RX    "SolaxX1 Rx"
#define D_SENSOR_IBEACON_TX    "iBeacon TX"
#define D_SENSOR_IBEACON_RX    "iBeacon RX"
#define D_SENSOR_RDM6300_RX    "RDM6300 RX"
#define D_SENSOR_CC1101_CS     "CC1101 CS"
#define D_SENSOR_A4988_DIR     "A4988 DIR"
#define D_SENSOR_A4988_STP     "A4988 STP"
#define D_SENSOR_A4988_ENA     "A4988 ENA"
#define D_SENSOR_A4988_MS1     "A4988 MS1"
#define D_SENSOR_A4988_MS2     "A4988 MS2"
#define D_SENSOR_A4988_MS3     "A4988 MS3"
#define D_SENSOR_DDS2382_TX    "DDS238-2 Tx"
#define D_SENSOR_DDS2382_RX    "DDS238-2 Rx"
#define D_SENSOR_DDSU666_TX    "DDSU666 Tx"
#define D_SENSOR_DDSU666_RX    "DDSU666 Rx"
#define D_SENSOR_SM2135_CLK    "SM2135 Clk"
#define D_SENSOR_SM2135_DAT    "SM2135 Dat"
#define D_SENSOR_DEEPSLEEP     "DeepSleep"
#define D_SENSOR_EXS_ENABLE    "EXS Enable"
#define D_SENSOR_SLAVE_TX    "Slave TX"
#define D_SENSOR_SLAVE_RX    "Slave RX"
#define D_SENSOR_SLAVE_RESET "Slave RST"

// Units
#define D_UNIT_AMPERE "A"
#define D_UNIT_CENTIMETER "cm"
#define D_UNIT_HERTZ "Hz"
#define D_UNIT_HOUR "h"
#define D_UNIT_GALLONS "gal"
#define D_UNIT_GALLONS_PER_MIN "g/m"
#define D_UNIT_INCREMENTS "inc"
#define D_UNIT_KILOGRAM "kg"
#define D_UNIT_KILOMETER_PER_HOUR "km/h"
#define D_UNIT_KILOOHM "kΩ"
#define D_UNIT_KILOWATTHOUR "kWh"
#define D_UNIT_LUX "lx"
#define D_UNIT_MICROGRAM_PER_CUBIC_METER "µg/m3"
#define D_UNIT_MICROMETER "µm"
#define D_UNIT_MICROSECOND "µs"
#define D_UNIT_MILLIAMPERE "mA"
#define D_UNIT_MILLIMETER "mm"
#define D_UNIT_MILLIMETER_MERCURY "mmHg"
#define D_UNIT_MILLISECOND "ms"
#define D_UNIT_MINUTE "min"
#define D_UNIT_PARTS_PER_BILLION "ppb"
#define D_UNIT_PARTS_PER_DECILITER "ppd"
#define D_UNIT_PARTS_PER_MILLION "ppm"
#define D_UNIT_PRESSURE "hPa"
#define D_UNIT_SECOND "s"
#define D_UNIT_SECTORS "Sektoren"
#define D_UNIT_VA "VA"
#define D_UNIT_VAR "VAr"
#define D_UNIT_VOLT "V"
#define D_UNIT_WATT "W"
#define D_UNIT_WATTHOUR "Wh"
#define D_UNIT_WATT_METER_QUADRAT "W/m²"

// Log message prefix
#define D_LOG_APPLICATION "APP: "  // Application
#define D_LOG_BRIDGE "BRG: "       // Bridge
#define D_LOG_CONFIG "CFG: "       // Settings
#define D_LOG_COMMAND "CMD: "      // Command
#define D_LOG_DEBUG "DBG: "        // Debug
#define D_LOG_DHT "DHT: "          // DHT sensor
#define D_LOG_DOMOTICZ "DOM: "     // Domoticz
#define D_LOG_DSB "DSB: "          // DS18xB20 sensor
#define D_LOG_HTTP "HTP: "         // HTTP webserver
#define D_LOG_I2C "I2C: "          // I2C
#define D_LOG_IRR "IRR: "          // Infra Red Received
#define D_LOG_LOG "LOG: "          // Logging
#define D_LOG_MODULE "MOD: "       // Module
#define D_LOG_MDNS "DNS: "         // mDNS
#define D_LOG_MQTT "MQT: "         // MQTT
#define D_LOG_OTHER "OTH: "        // Other
#define D_LOG_RESULT "RSL: "       // Result
#define D_LOG_RFR "RFR: "          // RF Received
#define D_LOG_SERIAL "SER: "       // Serial
#define D_LOG_SHT1 "SHT: "         // SHT1x sensor
#define D_LOG_UPLOAD "UPL: "       // Upload
#define D_LOG_UPNP "UPP: "         // UPnP
#define D_LOG_WIFI "WIF: "         // Wifi
#define D_LOG_ZIGBEE "ZIG: "       // Zigbee

//SDM220
#define D_PHASE_ANGLE     "Phasenwinkel"
#define D_IMPORT_ACTIVE   "Importiere Wirk"
#define D_EXPORT_ACTIVE   "Exportiere Wirk"
#define D_IMPORT_REACTIVE "Importiere Blind"
#define D_EXPORT_REACTIVE "Exportiere Blind"
#define D_TOTAL_REACTIVE  "Total Blind"
#define D_UNIT_KWARH      "kVArh"
#define D_UNIT_ANGLE      "Grad"

//SOLAXX1
#define D_PV1_VOLTAGE     "PV1 Spannung"
#define D_PV1_CURRENT     "PV1 Strom"
#define D_PV1_POWER       "PV1 Leistung"
#define D_PV2_VOLTAGE     "PV2 Spannung"
#define D_PV2_CURRENT     "PV2 Strom"
#define D_PV2_POWER       "PV2 Leistung"
#define D_SOLAR_POWER     "solare Leistung"
#define D_INVERTER_POWER  "Inverter Leistung"
#define D_STATUS          "Status"
#define D_WAITING         "warten"
#define D_CHECKING        "prüfen"
#define D_WORKING         "arbeitet"
#define D_FAILURE         "Fehler"
#define D_SOLAX_ERROR_0   "Kein Fehler Code"
#define D_SOLAX_ERROR_1   "Fehler im Solarstromnetz"
#define D_SOLAX_ERROR_2   "Spannungsfehler im Solarstromnetz"
#define D_SOLAX_ERROR_3   "Frequenzfehler im Solarstromnetz"
#define D_SOLAX_ERROR_4   "Pv Spannungsfehler"
#define D_SOLAX_ERROR_5   "Isolationsfehler"
#define D_SOLAX_ERROR_6   "Übertemperatur"
#define D_SOLAX_ERROR_7   "Lüfterfehler"
#define D_SOLAX_ERROR_8   "sonstiger Fehler"

#endif  // _LANGUAGE_DE_DE_H_
