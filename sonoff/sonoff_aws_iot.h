/*
  sonoff_aws_iot.ino - TLS AWS IoT for Sonoff-Tasmota

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

#ifdef USE_MQTT_AWS_IOT

extern const char *fingerprint;
extern const char *AWS_IoT_client_cert;
extern const char *AWS_IoT_client_PrivKey;
extern const char *AmazonRootCA1_PEM;
extern const char *aws_iot_pub_key;

extern const br_ec_private_key *AWS_IoT_Private_Key;
extern const br_x509_certificate *AWS_IoT_Client_Certificate;

#endif  // USE_MQTT_AWS_IOT
