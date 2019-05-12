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
/*********************************************************************************************\
 * LetsEncrypt IdenTrust DST Root CA X3 certificate valid until 20210930
 *
 * https://letsencrypt.org/certificates/
 * Downloaded from https://www.identrust.com/support/downloads
\*********************************************************************************************/

const char *fingerprint PROGMEM = "00:F5:1A:E7:A3:48:2A:F3:FC:E0:75:4D:24:D5:91:BD:BB:E1:6A:B4";

const char *AWS_IoT_client_cert PROGMEM =
"-----BEGIN CERTIFICATE-----\n"
"MIIDWjCCAkKgAwIBAgIVAIKFQOW7xbf4YK4Ic/p9webrulxpMA0GCSqGSIb3DQEB\n"
"CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n"
"IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0xOTA1MDkxOTAy\n"
"MTBaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n"
"dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQC4MTw3A73RNiy8wZXp\n"
"2RoG+8H80iMrdCEX2/MJ4K4BGoAaOk2fW4G1RXU+bvaLf/kehD2mdlsDXVyPyOBT\n"
"ixVu929HQTcTx8hoAHUdSCvb5AKWnPtgUB7/KEdNjjCMljGSR8O+VNarLg6jEcHT\n"
"t482Ep+ACFpJ1Jz4TEGru0v2NOgrnGd9AtmX//3mel4wOnv3pdYXmkty60UI4LNV\n"
"Gu3bOD62ubqDENGSPjoDcD4qMm3go94sIVe+HcgV9HMwDU+NPVwnWU5F4VLtn3z7\n"
"Fwqh6FWemM1QSSaJn1JRvcm6WoTYNp3Gd2oByR2yS28ts8kfnmJEUrr2ZK7gmEly\n"
"LACtAgMBAAGjYDBeMB8GA1UdIwQYMBaAFIplID6fTbJFp9mJGBxwbY35wskxMB0G\n"
"A1UdDgQWBBTx9KwjBgk/dgk9VM8vD+VC7F3UsTAMBgNVHRMBAf8EAjAAMA4GA1Ud\n"
"DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEALNyBLDXLwwVGg1CwhCVQA9DS\n"
"6BiiLxTarsvaKL02f94wWarmPk5Q0MG+d+y1yIFVpohyxpEZlHXT1d+61vhsjSrF\n"
"JUwJNe2KE+hBkscU1vb6WgExyqIHRy6UpJwrqHtgdhIfwIf48AoGvufy1QTt49HA\n"
"YjXa418pWE188QvB2SqJ1odJRD3JIRWI3kFM0H4uFF0nPzdRNJR+3KEMwF04pAfy\n"
"n85hT1c8+SE0FnU/q1UyCheb7v/vsbrEEWU/6beJERg0X0b5wMydd9CYPtqpyzm7\n"
"NXOGmdqCBHSAftk/A2a2QkV9GDSF1jN2fnOEKblEyPAxqG2VxYZNqspEPE3hsw==\n"
"-----END CERTIFICATE-----";

const char *AWS_IoT_client_PrivKey PROGMEM =
"-----BEGIN RSA PRIVATE KEY-----\n"
"MIIEowIBAAKCAQEAuDE8NwO90TYsvMGV6dkaBvvB/NIjK3QhF9vzCeCuARqAGjpN\n"
"n1uBtUV1Pm72i3/5HoQ9pnZbA11cj8jgU4sVbvdvR0E3E8fIaAB1HUgr2+QClpz7\n"
"YFAe/yhHTY4wjJYxkkfDvlTWqy4OoxHB07ePNhKfgAhaSdSc+ExBq7tL9jToK5xn\n"
"fQLZl//95npeMDp796XWF5pLcutFCOCzVRrt2zg+trm6gxDRkj46A3A+KjJt4KPe\n"
"LCFXvh3IFfRzMA1PjT1cJ1lOReFS7Z98+xcKoehVnpjNUEkmiZ9SUb3JulqE2Dad\n"
"xndqAckdsktvLbPJH55iRFK69mSu4JhJciwArQIDAQABAoIBAHFeFHLEAcPP9U8k\n"
"U3IAJu3fbLGAYRcwveGihf8xY8fYGLqL4hTQTJBWtOf9gg+wb5Nhz1QyiqgSgZMa\n"
"D0A8Xa/T6ZDQyeaJ04Z3qZ2hOyV3PESZUHsiNUHU97X7a1RMaSxgsVDnhM0NZwLl\n"
"PghidWnRoow6F+BTVV3aCZ16hTF+p8qQGabiyZE43syzh136NensWwsnld8OAmKY\n"
"P4l8xetSeS6JTlfa+ViZQFTrNlLx0rlXqdGhmuBjqzZ3gNOoVuqgSHjjAre+Ajjw\n"
"W8pUPD5TjM5OLT4GizDnoE69X54oklHho1m94oCcwwjLBIAQXW5qz9bxih3y/ogv\n"
"qXMkrgECgYEA84m3JX1mvlgrh9JPMrkt82ipSs9W1jmWCxisBZ/iCQtHgHSY101f\n"
"U91aFJktU0a1d5gJ6JIfXM3D78Ol5vCXywqG3iK75XgilT+0Vt36yjDI79MUWK4b\n"
"ZHWMdaa0sjY1uSCrBjDaUtn1ytVG5hoLBXD+qeGG4m43LWP670/7qC0CgYEAwZ4b\n"
"ey/pEwSQMQTANhX+gH9ikJQRnlHtLbLHsFFojBzQPUpYGMX/rDQ5ZKg8+COhr2eN\n"
"DKz7LgwqEiM2BeJsmNuYQbszlWB/ZX0CLQIOEEflmvRWoVMSErvOqst0o00ue9/v\n"
"U4218SFej/1XG7m+EQj3GQAudTSk3kjbgycEioECgYEA8jrbGIXnSJHoEjsDnR8E\n"
"7mL+Z7Nc2s0CSV0r1JhXOcmnP8Q5NYT2uTKkY3KL25Wr7x0hVdrpKORc68D85XwO\n"
"bty0koOXwkDAnRR06iX2SV9GrQuU5DOgeUZWA7thZRR4UP+GPC0hKmEykaGa2Em1\n"
"Bp+CHTR9dgBMD3CvaZJza60CgYBO/uYxfZu30a3PAiQ2LQUYgmDBolgJ411EvuOw\n"
"cZaZTAw+ZX3KJcaqCOi9w9KUX11RhotK96zH3diwa8NX5UjvmPDnKKzkLmnsC3P+\n"
"zw7T37GzZiuOSKlgEVZB4x7kndHwYq5vxarNBhNh5jhLLJ56rtC6V5Oc6Gy38Lv3\n"
"J803gQKBgBEUNaeDbN3Z7FfCqO4ke4OFPFzrT0KxVoDoN6IEY+SRT6dOJ9kUrY8s\n"
"fIzaSQfqUzNW/EgqCicHru7GzJk+QhmpyehLtgKEdqTpKCH32S8xftBaEeFXdOTD\n"
"CFGLlMbtVZL1HTciDloDwfinECnvxAraWxurcqUysTSs4//AlZzc\n"
"-----END RSA PRIVATE KEY-----";

const char *AmazonRootCA1_PEM PROGMEM =
"-----BEGIN CERTIFICATE-----\n"
"MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n"
"ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n"
"b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n"
"MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n"
"b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n"
"ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n"
"9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n"
"IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n"
"VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n"
"93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n"
"jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n"
"AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n"
"A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n"
"U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n"
"N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n"
"o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n"
"5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n"
"rqXRfboQnoZsG4q5WTP468SQvvG5\n"
"-----END CERTIFICATE-----";



#endif  // USE_MQTT_AWS_IOT
