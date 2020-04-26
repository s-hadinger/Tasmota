/*
  xsns_40_pn532.ino - Support for PN532 (HSU) NFC Tag Reader on Tasmota

  Copyright (C) 2020  Andre Thomas and Theo Arends

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

#ifdef USE_PN532_HSU

#define XSNS_40                                     40

#define DEBUG_PN532

#ifdef DEBUG_PN532
char debug_pn532[2048];

void AddLog_P2f(PGM_P format, ...) {   // ignore log_level
  va_list arg;
  va_start(arg, format);
  size_t mlen = strlen(debug_pn532);
  if (mlen && (mlen < sizeof(debug_pn532)-1)) {
    debug_pn532[mlen++] = '\n';   // prepend with lf
    debug_pn532[mlen] = 0;   // prepend with lf
  }
  vsnprintf_P(debug_pn532 + mlen, sizeof(debug_pn532) - mlen, format, arg);
  va_end(arg);
}
#endif

#include <TasmotaSerial.h>

TasmotaSerial *PN532_Serial;

const int32_t PN532_INVALID_ACK                 = -1;
const int32_t PN532_TIMEOUT                     = -2;
const int32_t PN532_INVALID_FRAME               = -3;
const int32_t PN532_NO_SPACE                    = -4;
const int32_t PN532_INVALID_PREAMBLE            = -5;
const int32_t PN532_INVALID_LENGTH_CHECKSUM     = -6;

const uint8_t PN532_PREAMBLE                    = 0x00;
const uint8_t PN532_STARTCODE1                  = 0x00;
const uint8_t PN532_STARTCODE2                  = 0xFF;
const uint8_t PN532_POSTAMBLE                   = 0x00;

const uint8_t PN532_HOSTTOPN532                 = 0xD4;
const uint8_t PN532_PN532TOHOST                 = 0xD5;

const uint8_t PN532_ACK_WAIT_TIME               = 15;   // 15 ms

const uint8_t PN532_COMMAND_GETFIRMWAREVERSION  = 0x02;
const uint8_t PN532_COMMAND_SAMCONFIGURATION    = 0x14;
const uint8_t PN532_COMMAND_RFCONFIGURATION     = 0x32;
const uint8_t PN532_COMMAND_INDATAEXCHANGE      = 0x40;
const uint8_t PN532_COMMAND_INLISTPASSIVETARGET = 0x4A;

const uint8_t PN532_MIFARE_ISO14443A            = 0x00;
const uint8_t MIFARE_CMD_READ                   = 0x30;
const uint8_t MIFARE_CMD_AUTH_A                 = 0x60;
const uint8_t MIFARE_CMD_AUTH_B                 = 0x61;
const uint8_t MIFARE_CMD_WRITE                  = 0xA0;

uint8_t pn532_model = 0;          // Used to maintain detection flag
uint8_t pn532_command = 0;        // Used to carry command code between functions
uint8_t pn532_scantimer = 0;      // Used to prevent multiple successful reads within 2 second window

uint8_t pn532_packetbuffer[64];   // Global buffer used to store packet

#ifdef USE_PN532_DATA_FUNCTION
uint8_t pn532_function = 0;
uint8_t pn532_newdata[16];
uint8_t pn532_newdata_len = 0;
#endif // USE_PN532_DATA_FUNCTION

void PN532_Init(void) {
  if ((pin[GPIO_PN532_RXD] < 99) && (pin[GPIO_PN532_TXD] < 99)) {
    PN532_Serial = new TasmotaSerial(pin[GPIO_PN532_RXD], pin[GPIO_PN532_TXD], 1);
    if (PN532_Serial->begin(115200)) {
      if (PN532_Serial->hardwareSerial()) { ClaimSerial(); }
      //PN532_wakeup();
      uint32_t ver = PN532_getFirmwareVersion(); 
      if (ver) {
        PN532_setPassiveActivationRetries(0xFF);    // 0xFF = default, infinitely
        PN532_SAMConfig();
        pn532_model = 1;
        AddLog_P2(LOG_LEVEL_INFO,"NFC: PN532 NFC Reader detected (V%u.%u)",(ver>>16) & 0xFF, (ver>>8) & 0xFF);
      }
    }
  }
}

// Params
// - timeout: ms timeout between each received byte (blocking)
// TODO: unblocking mode
int32_t PN532_receive(uint8_t *buf, size_t len, uint16_t timeout) {
// #ifdef DEBUG_PN532
// AddLog_P2(LOG_LEVEL_DEBUG, PSTR("PN532_receive timeout = %d"), timeout);
// #endif
  int32_t   read_bytes = 0;
  int32_t   ret;
  uint32_t  start_millis;

  while (read_bytes < len) {
    start_millis = millis();
    do {
      ret = PN532_Serial->read();
      if (ret >= 0) {
        break;
      }
    } while((timeout == 0) || ((millis()- start_millis ) < timeout));

// #ifdef DEBUG_PN532
// if (ret >= 0) { AddLog_P2(LOG_LEVEL_DEBUG, PSTR("PN532_receive %02X"), ret); }
// if (ret < 0) { AddLog_P2(LOG_LEVEL_DEBUG, PSTR("PN532_receive timeout (%d)"), timeout); }
// #endif
    if (ret < 0) {
      if (read_bytes) {
        return read_bytes;
      } else {
        return PN532_TIMEOUT;
      }
    }
    buf[read_bytes] = (uint8_t)ret;
    read_bytes++;
  }
  return read_bytes;
}

int8_t PN532_readAckFrame(void)
{
  const uint8_t PN532_ACK[] = {0, 0, 0xFF, 0, 0xFF, 0};
  uint8_t ackBuf[sizeof(PN532_ACK)];

  if (PN532_receive(ackBuf, sizeof(PN532_ACK), PN532_ACK_WAIT_TIME) <= 0) {
    return PN532_TIMEOUT;
  }

  if (memcmp(&ackBuf, &PN532_ACK, sizeof(PN532_ACK))) {
    return PN532_INVALID_ACK;
  }
  return 0;
}

int8_t PN532_sendCommand(const uint8_t *header, uint8_t hlen, const uint8_t *body = nullptr, uint8_t blen = 0)
{
  // Clear the serial buffer just in case
  //PN532_wakeup();
  PN532_Serial->flush();

  pn532_command = header[0];
  PN532_Serial->write((uint8_t)PN532_PREAMBLE);
  PN532_Serial->write((uint8_t)PN532_STARTCODE1);
  PN532_Serial->write(PN532_STARTCODE2);

  uint8_t length = hlen + blen + 1;   // length of data field: TFI + DATA
  PN532_Serial->write(length);
  PN532_Serial->write(~length + 1);         // checksum of length

  PN532_Serial->write(PN532_HOSTTOPN532);
  uint8_t sum = PN532_HOSTTOPN532;    // sum of TFI + DATA

  PN532_Serial->write(header, hlen);
  for (uint32_t i = 0; i < hlen; i++) {
    sum += header[i];
  }

  PN532_Serial->write(body, blen);
  for (uint32_t i = 0; i < blen; i++) {
    sum += body[i];
  }

  uint8_t checksum = ~sum + 1;            // checksum of TFI + DATA
  PN532_Serial->write(checksum);
  PN532_Serial->write((uint8_t)PN532_POSTAMBLE);

#ifdef DEBUG_PN532
  char hex_h[hlen*2+2];
  char hex_b[hlen*2+2];
  hex_b[0] = 0;

  ToHex_P(header, hlen, hex_h, sizeof(hex_h));
  if (body && (blen > 0)) {
    ToHex_P(body, blen, hex_b, sizeof(hex_b));
  }
  AddLog_P2f(PSTR("PN532_sendCommand: > %02X%02X%02X-%02X%02X-%02X%s::%s:%02X%02X (%d,%d)"), 
                PN532_PREAMBLE, PN532_STARTCODE1, PN532_STARTCODE2,
                (uint8_t)length, (uint8_t)(~length + 1),
                PN532_HOSTTOPN532, hex_h, hex_b,
                checksum, PN532_POSTAMBLE,
                hlen, blen);
#endif

  return PN532_readAckFrame();
}

// Read and parse response
int32_t PN532_readResponse(uint8_t *buf, size_t buf_len, uint16_t timeout = 50) {
  uint8_t tmp[3];
  size_t pac_len;

#ifdef DEBUG_PN532
AddLog_P2f(PSTR("PN532_readResponse buf = 0x%08X, buf_len = %d, timeout = %d"), buf, buf_len, timeout);
#endif
  // Read preamble and start code
  if (PN532_receive(tmp, 3, timeout) <= 0) {
    return PN532_TIMEOUT;
  }
  if (0 != tmp[0] || 0!= tmp[1] || 0xFF != tmp[2]) {
    return PN532_INVALID_PREAMBLE;
  }

  // Get length of data to be received
  uint8_t length[2];
  if (PN532_receive(tmp, 2, timeout) <= 0) {
    return PN532_TIMEOUT;
  }
  // Validate that frame is valid
  if (0 != (uint8_t)(tmp[0] + tmp[1])) {
    return PN532_INVALID_LENGTH_CHECKSUM;
  }
  pac_len = tmp[0] - 2;
  if (pac_len > buf_len) {   // If this happens, then pn532_packetbuffer is not large enough
    return PN532_NO_SPACE;
  }

  // Get the command byte
  uint8_t cmd = pn532_command + 1;
  if (PN532_receive(tmp, 2, timeout) <= 0) { // Time out while receiving
    return PN532_TIMEOUT;
  }
  if (PN532_PN532TOHOST != tmp[0] || cmd != tmp[1]) { // Invalid frame received
    return PN532_INVALID_FRAME;
  }

  if (PN532_receive(buf, pac_len, timeout) != pac_len) { // Timed out
    return PN532_TIMEOUT;
  }

  uint8_t sum = PN532_PN532TOHOST + cmd;
  for (uint32_t i = 0; i < pac_len; i++) {
    sum += buf[i];
  }

  // Checksum & postamble
  if (PN532_receive(tmp, 2, timeout) <= 0) {
    return PN532_TIMEOUT;
  }
  if (0 != (uint8_t)(sum + tmp[0]) || 0 != tmp[1]) { // Checksum fail, so frame must be invalid
    return PN532_INVALID_FRAME;
  }

#ifdef DEBUG_PN532
  char hex[pac_len * 2+2];
  ToHex_P(buf, buf_len, hex, sizeof(hex));
  AddLog_P2f(PSTR("PN532_readResponse < %02X%02X%s"), PN532_PN532TOHOST, pn532_command + 1, hex);
#endif

  return pac_len;
}

uint32_t PN532_getFirmwareVersion(void) {
  uint32_t response;

  pn532_packetbuffer[0] = PN532_COMMAND_GETFIRMWAREVERSION;

  if (PN532_sendCommand(pn532_packetbuffer, 1)) {
    return 0;
  }

  // Read data packet
  int16_t status = PN532_readResponse(pn532_packetbuffer, sizeof(pn532_packetbuffer));
  if (0 > status) {
    return 0;
  }

  response = pn532_packetbuffer[0];
  response <<= 8;
  response |= pn532_packetbuffer[1];
  response <<= 8;
  response |= pn532_packetbuffer[2];
  response <<= 8;
  response |= pn532_packetbuffer[3];

#ifdef DEBUG_PN532
AddLog_P2f(PSTR("PN532_getFirmwareVersion response = 0x%08X"), response);
#endif
  return response;
}

void PN532_wakeup(void)
{
  uint8_t wakeup[] = {0x55, 0x55, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

#ifdef DEBUG_PN532
AddLog_P2f(PSTR("PN532_wakeup: > 5555000000"));
#endif
  PN532_Serial->write(wakeup, sizeof(wakeup));

  // Flush the serial buffer just in case there's garbage in there
  PN532_Serial->flush();
}

// returns status code
//   -10 : could not send command
//   -11 : could not read response
//   -12 : bad response packet
int32_t PN532_readPassiveTargetID(uint8_t cardbaudrate, uint8_t *uid, uint16_t timeout = 50) {
  uint8_t buf[24];

  buf[0] = PN532_COMMAND_INLISTPASSIVETARGET;
  buf[1] = 1;  // max 1 cards at once (we can set this to 2 later)
  buf[2] = cardbaudrate;
  if (PN532_sendCommand(buf, 3)) {
    return -10;  // command failed
  }
  // read data packet
  if (PN532_readResponse(buf, sizeof(buf), timeout) < 0) {
    return -11;
  }

  /* Check some basic stuff
     b0              Tags Found
     b1              Tag Number (only one used in this example)
     b2..3           SENS_RES
     b4              SEL_RES
     b5              NFCID Length
     b6..NFCIDLen    NFCID
    */

  if (buf[0] != 1) {
    return -12;
  }

  uint16_t sens_res = buf[2];
  sens_res <<= 8;
  sens_res |= buf[3];

  /* Card appears to be Mifare Classic */
  uint8_t uid_len = buf[5];

  for (uint32_t i = 0; i < uid_len; i++) {
    uid[i] = buf[6 + i];
  }

#ifdef DEBUG_PN532
  AddLog_P2f(PSTR("PN532_readPassiveTargetID: uid(%d) = %02X%02X%02X%02X"), uid_len, uid[0], uid[1], uid[2], uid[3]);
#endif
  return uid_len;
}

// Initial configuration of the device, configura max retries
// MxRtyATR = default
// MxRTYPSL = default
bool PN532_setPassiveActivationRetries(uint8_t maxRetries)
{
  pn532_packetbuffer[0] = PN532_COMMAND_RFCONFIGURATION;
  pn532_packetbuffer[1] = 5;    // Config item 5 (MaxRetries)
  pn532_packetbuffer[2] = 0xFF; // MxRtyATR (default = 0xFF)
  pn532_packetbuffer[3] = 0x01; // MxRtyPSL (default = 0x01)
  pn532_packetbuffer[4] = maxRetries;
  if (PN532_sendCommand(pn532_packetbuffer, 5)) {
    return false; // no ACK
  }
  return (0 < PN532_readResponse(pn532_packetbuffer, sizeof(pn532_packetbuffer)));
}

bool PN532_SAMConfig(void) {
  pn532_packetbuffer[0] = PN532_COMMAND_SAMCONFIGURATION;
  pn532_packetbuffer[1] = 0x01; // normal mode
  pn532_packetbuffer[2] = 0x14; // timeout 50ms * 20 = 1 second
  pn532_packetbuffer[3] = 0x00; // we don't need the external IRQ pin
  if (PN532_sendCommand(pn532_packetbuffer, 4)) {
    return false;
  }
  return (0 < PN532_readResponse(pn532_packetbuffer, sizeof(pn532_packetbuffer)));
}

#ifdef USE_PN532_DATA_FUNCTION

// Returns status code
//    0: success
//  -20: cannot send auth command
//  -21: bad auth response
int32_t mifareclassic_AuthenticateBlock(uint8_t *uid, uint8_t uidLen, uint32_t blockNumber, uint8_t keyNumber, uint8_t *keyData) {
  uint8_t _key[6];
  uint8_t _uid[7];
  uint8_t _uidLen;

  // Hang on to the key and uid data
  memcpy(&_key, keyData, 6);
  memcpy(&_uid, uid, uidLen);
  _uidLen = uidLen;

  // Prepare the authentication command //
  pn532_packetbuffer[0] = PN532_COMMAND_INDATAEXCHANGE;   // Data Exchange Header
  pn532_packetbuffer[1] = 1;                              // Max card numbers
  pn532_packetbuffer[2] = (keyNumber) ? MIFARE_CMD_AUTH_B : MIFARE_CMD_AUTH_A;
  pn532_packetbuffer[3] = blockNumber;                    // Block Number (1K = 0..63, 4K = 0..255
  memcpy(&pn532_packetbuffer[4], _key, 6);
  memcpy(&pn532_packetbuffer[10], _uid, _uidLen);

  if (PN532_sendCommand(pn532_packetbuffer, 10 + _uidLen)) { return -20; }

  // Read the response packet
  PN532_readResponse(pn532_packetbuffer, sizeof(pn532_packetbuffer));

  // Check if the response is valid and we are authenticated???
  // for an auth success it should be bytes 5-7: 0xD5 0x41 0x00
  // Mifare auth error is technically byte 7: 0x14 but anything other and 0x00 is not good
  if (pn532_packetbuffer[0] != 0x00) {
    // Authentification failed
    return -21;
  }

  return 0;
}

// Returns status code
//   0: success
// -30: cannot write packet
// -31: bad response
int32_t mifareclassic_ReadDataBlock (uint8_t blockNumber, uint8_t *data) {
  /* Prepare the command */
  pn532_packetbuffer[0] = PN532_COMMAND_INDATAEXCHANGE;
  pn532_packetbuffer[1] = 1;                      /* Card number */
  pn532_packetbuffer[2] = MIFARE_CMD_READ;        /* Mifare Read command = 0x30 */
  pn532_packetbuffer[3] = blockNumber;            /* Block Number (0..63 for 1K, 0..255 for 4K) */

  /* Send the command */
  if (PN532_sendCommand(pn532_packetbuffer, 4)) {
      return -30;
  }

  /* Read the response packet */
  PN532_readResponse(pn532_packetbuffer, sizeof(pn532_packetbuffer));

  /* If byte 8 isn't 0x00 we probably have an error */
  if (pn532_packetbuffer[0] != 0x00) {
      return -31;
  }

  /* Copy the 16 data bytes to the output buffer        */
  /* Block content starts at byte 9 of a valid response */
  memcpy (data, &pn532_packetbuffer[1], 16);

  return 0;
}

uint8_t mifareclassic_WriteDataBlock (uint8_t blockNumber, uint8_t *data)
{
    /* Prepare the first command */
    pn532_packetbuffer[0] = PN532_COMMAND_INDATAEXCHANGE;
    pn532_packetbuffer[1] = 1;                      /* Card number */
    pn532_packetbuffer[2] = MIFARE_CMD_WRITE;       /* Mifare Write command = 0xA0 */
    pn532_packetbuffer[3] = blockNumber;            /* Block Number (0..63 for 1K, 0..255 for 4K) */
    memcpy(&pn532_packetbuffer[4], data, 16);       /* Data Payload */

    /* Send the command */
    if (PN532_sendCommand(pn532_packetbuffer, 20)) {
        return 0;
    }

    /* Read the response packet */
    return (0 < PN532_readResponse(pn532_packetbuffer, sizeof(pn532_packetbuffer)));
}

#endif // USE_PN532_DATA_FUNCTION

// Returns:
// - status code:
//   >0 : number of bytes read
//   -1 : unsupported UID lenght
int32_t PN532_ReadBlock(uint32_t block, int64_t keyA, int64_t keyB, uint8_t *buf, size_t buf_len) {
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };    // 56 bits max uid
  uint8_t uid_len = 0;                        // placeholder for length
  uint8_t data[64];                           // block data buffer
  int32_t res;

  if (buf_len < 16) { return PN532_NO_SPACE; }

  PN532_wakeup();
  res = PN532_readPassiveTargetID(PN532_MIFARE_ISO14443A, uid);
  if (res <= 0) { return res; }    // error
  uid_len = res;

  if (uid_len != 4) { return -1; }    // we only support UID of 4 bytes

  // TODO check order of key
  uint8_t key1[6] = {
                    (uint8_t) ((uint64_t)keyA >>  0),
                    (uint8_t) ((uint64_t)keyA >>  8),
                    (uint8_t) ((uint64_t)keyA >> 16),
                    (uint8_t) ((uint64_t)keyA >> 24),
                    (uint8_t) ((uint64_t)keyA >> 32),
                    (uint8_t) ((uint64_t)keyA >> 40)
                    };

  res = mifareclassic_AuthenticateBlock(uid, uid_len, block, 1, (uint8_t*) &keyA);
  if (0 != res) { return res; }

  res = mifareclassic_AuthenticateBlock(uid, uid_len, block, 2, (uint8_t*) &keyB);
  if (0 != res) { return res; }

  res = mifareclassic_ReadDataBlock(block, buf);
  if (0 != res) { return res; }

  return 16;
}

void PN532_ScanForTag(void)
{
  if (!pn532_model) { return; }
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t card_data[16];
  bool erase_success = false;
  bool set_success = false;
  int32_t res;

  res = PN532_readPassiveTargetID(PN532_MIFARE_ISO14443A, uid);
  if (res > 0) {
      uint8_t uid_len = res;
      char uids[15];

#ifdef USE_PN532_DATA_FUNCTION
      char card_datas[34];
#endif // USE_PN532_DATA_FUNCTION

      ToHex_P((unsigned char*)uid, uid_len, uids, sizeof(uids));

#ifdef USE_PN532_DATA_FUNCTION
      if (uid_len == 4) { // Lets try to read block 1 of the mifare classic card for more information
        uint8_t keyuniversal[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
        if (!mifareclassic_AuthenticateBlock(uid, uid_len, 1, 1, keyuniversal)) {
          if (mifareclassic_ReadDataBlock(1, card_data)) {
#ifdef USE_PN532_DATA_RAW
            memcpy(&card_datas,&card_data,sizeof(card_data));
#else
            for (uint32_t i = 0;i < sizeof(card_data);i++) {
              if ((isalpha(card_data[i])) || ((isdigit(card_data[i])))) {
                card_datas[i] = char(card_data[i]);
              } else {
                card_datas[i] = '\0';
              }
            }
#endif // USE_PN532_DATA_RAW
          }
          if (pn532_function == 1) { // erase block 1 of card
            for (uint32_t i = 0;i<16;i++) {
              card_data[i] = 0x00;
            }
            if (mifareclassic_WriteDataBlock(1, card_data)) {
              erase_success = true;
              AddLog_P(LOG_LEVEL_INFO, PSTR("NFC: PN532 NFC - Erase success"));
              memcpy(&card_datas,&card_data,sizeof(card_data)); // Cast block 1 to a string
            }
          }
          if (pn532_function == 2) {
#ifdef USE_PN532_DATA_RAW
            memcpy(&card_data,&pn532_newdata,sizeof(card_data));
            if (mifareclassic_WriteDataBlock(1, card_data)) {
              set_success = true;
              AddLog_P(LOG_LEVEL_INFO, PSTR("NFC: PN532 NFC - Data write successful"));
              memcpy(&card_datas,&card_data,sizeof(card_data)); // Cast block 1 to a string
            }
#else
            bool IsAlphaNumeric = true;
            for (uint32_t i = 0;i < pn532_newdata_len;i++) {
              if ((!isalpha(pn532_newdata[i])) && (!isdigit(pn532_newdata[i]))) {
                IsAlphaNumeric = false;
              }
            }
            if (IsAlphaNumeric) {
              memcpy(&card_data,&pn532_newdata,pn532_newdata_len);
              card_data[pn532_newdata_len] = '\0'; // Enforce null termination
              if (mifareclassic_WriteDataBlock(1, card_data)) {
                set_success = true;
                AddLog_P(LOG_LEVEL_INFO, PSTR("NFC: PN532 NFC - Data write successful"));
                memcpy(&card_datas,&card_data,sizeof(card_data)); // Cast block 1 to a string
              }
            } else {
              AddLog_P(LOG_LEVEL_INFO, PSTR("NFC: PN532 NFC - Data must be alphanumeric"));
            }
#endif // USE_PN532_DATA_RAW
          }
        } else {
          sprintf(card_datas,"AUTHFAIL");
        }
      }
      switch (pn532_function) {
        case 0x01:
          if (!erase_success) {
            AddLog_P(LOG_LEVEL_INFO, PSTR("NFC: PN532 NFC - Erase fail - exiting erase mode"));
          }
          break;
        case 0x02:
          if (!set_success) {
            AddLog_P(LOG_LEVEL_INFO, PSTR("NFC: PN532 NFC - Write failed - exiting set mode"));
          }
        default:
          break;
      }
      pn532_function = 0;
#endif // USE_PN532_DATA_FUNCTION

#ifdef USE_PN532_DATA_FUNCTION
      ResponseTime_P(PSTR(",\"PN532\":{\"UID\":\"%s\", \"DATA\":\"%s\"}}"), uids, card_datas);
#else
      ResponseTime_P(PSTR(",\"PN532\":{\"UID\":\"%s\"}}"), uids);
#endif // USE_PN532_DATA_FUNCTION

      MqttPublishTeleSensor();

#ifdef USE_PN532_CAUSE_EVENTS

      char command[71];
#ifdef USE_PN532_DATA_FUNCTION
      sprintf(command,"backlog event PN532_UID=%s;event PN532_DATA=%s",uids,card_datas);
#else
      sprintf(command,"event PN532_UID=%s",uids);
#endif // USE_PN532_DATA_FUNCTION
      ExecuteCommand(command, SRC_RULE);
#endif // USE_PN532_CAUSE_EVENTS

      pn532_scantimer = 7; // Ignore tags found for two seconds
  }
}

#ifdef USE_PN532_DATA_FUNCTION

/*********************************************************************************************\
 * Sensor 40 Command
\*********************************************************************************************/
// Input: no parameter, everything is passed via XdrvMailbox
// Returns: true if command was serviced (ok)
bool PN532_Command(void)
{
  // New JSON Syntax
  // Read:
  //  Sensor40 {"ReadBlock":<b>,"Key":"<key_hex> (opt)","Key2":"<key2_hex> (opt)"}
  // Write:
  //  Sensor40 {"WriteBlock":<b>,"Data":"<data_hex>","Key":"<key_hex> (opt)","Key2":"<key2_hex> (opt)"}
  if (0 == XdrvMailbox.data_len) { return false; }    // ignore if no parameter

  if ('{' == XdrvMailbox.data[0]) {
    int32_t read_block = -1;        // which block to read
    int32_t write_block = -1;       // which block to write
    int64_t key = -1;               // auth key, key is 48 bits, <0 if unspecified. 0xFFFFFFFFFFFF is anyways the universal key
    // paramater is JSON
    DynamicJsonBuffer jsonBuf;
    const JsonObject &json = jsonBuf.parseObject((const char*) XdrvMailbox.data);
    if (!json.success()) { ResponseCmndChar_P(PSTR(D_JSON_INVALID_JSON)); return false; }

    const JsonVariant &val_read = getJsonCaseInsensitive(json, PSTR("ReadBlock"));
    if (nullptr != &val_read) { read_block = jsonToUInt(val_read); }
    const JsonVariant &val_write = getJsonCaseInsensitive(json, PSTR("WriteBlock"));
    if (nullptr != &val_write) { read_block = jsonToUInt(val_write); }

    const JsonVariant &val_key = getJsonCaseInsensitive(json, PSTR("Key"));
    if (nullptr != &val_key) {
      key = strtoull(val_key.as<const char*>(), nullptr, 0);
      if (key > 0xFFFFFFFFFFFFLL) { key = -1; }     // 48 bits only or ignore
    }

    // Check for valid numbers
    if (read_block > 63) { read_block = 63; }
    if (write_block > 63) { write_block = 63; }
    // if both negative, we don't have a command
    if ((read_block < 0) && (write_block < 0)) { ResponseCmndChar_P(PSTR("Missing \"ReadBlock\" or \"WriteBlock\"")); return false; }
    // if both specified, abort
    if ((read_block >= 0) && (write_block >=0)) { ResponseCmndChar_P(PSTR("Only \"ReadBlock\" or \"WriteBlock\"")); return false; }

    if (read_block >= 0) {
      // read
      uint8_t data[16];
      int32_t bytes_read;

      bytes_read = PN532_ReadBlock(read_block, key, key, data, sizeof(data));
      AddLog_P2f("PN532_ReadBlock -> %d", bytes_read);

      if (16 == bytes_read) {
        char hex[16*2+2];
        ToHex_P(data, sizeof(data), hex, sizeof(hex));
        ResponseTime_P(PSTR(",\"PN532\":{\"ReadBlock\":%d,\"Data\":\"%s\"}}"), hex);
        MqttPublishTeleSensor();
        XdrvRulesProcess();
      }


    } else if (write_block >= 0) {
      // write

    }
  } else {
    // Legacy code
    uint8_t paramcount = 1;
    char sub_string[XdrvMailbox.data_len];
    char sub_string_tmp[XdrvMailbox.data_len];
    for (uint32_t ca=0;ca<XdrvMailbox.data_len;ca++) {
      if ((' ' == XdrvMailbox.data[ca]) || ('=' == XdrvMailbox.data[ca])) { XdrvMailbox.data[ca] = ','; }
      if (',' == XdrvMailbox.data[ca]) { paramcount++; }
    }
    UpperCase(XdrvMailbox.data,XdrvMailbox.data);
    if (!strcmp(subStr(sub_string, XdrvMailbox.data, ",", 1),"E")) {
      pn532_function = 1; // Block 1 of next card/tag will be reset to 0x00...
      AddLog_P(LOG_LEVEL_INFO, PSTR("NFC: PN532 NFC - Next scanned tag data block 1 will be erased"));
      ResponseTime_P(PSTR(",\"PN532\":{\"COMMAND\":\"E\"}}"));
      return true;
    }
    if (!strcmp(subStr(sub_string, XdrvMailbox.data, ",", 1),"S")) {
      if (paramcount > 1) {
        if (XdrvMailbox.data[XdrvMailbox.data_len-1] == ',') {
          return false;
        }
        sprintf(sub_string_tmp,subStr(sub_string, XdrvMailbox.data, ",", 2));
        pn532_newdata_len = strlen(sub_string_tmp);
        if (pn532_newdata_len > 15) { pn532_newdata_len = 15; }
        memcpy(&pn532_newdata,&sub_string_tmp,pn532_newdata_len);
        pn532_newdata[pn532_newdata_len] = 0x00; // Null terminate the string
        pn532_function = 2;
        AddLog_P2(LOG_LEVEL_INFO, PSTR("NFC: PN532 NFC - Next scanned tag data block 1 will be set to '%s'"), pn532_newdata);
        ResponseTime_P(PSTR(",\"PN532\":{\"COMMAND\":\"S\"}}"));
        return true;
      }
    }
  }
}

#endif // USE_PN532_DATA_FUNCTION

bool Xsns40(uint8_t function)
{
  bool result = false;

#ifdef DEBUG_PN532
  debug_pn532[0] = 0;     // reset debug buffer
#endif

  switch (function) {
    case FUNC_INIT:
      PN532_Init();
      result = true;
      break;
    case FUNC_EVERY_50_MSECOND:
      break;
    case FUNC_EVERY_100_MSECOND:
      break;
    case FUNC_EVERY_250_MSECOND:
      // if (pn532_scantimer > 0) {
      //   pn532_scantimer--;
      // } else {
      //   PN532_ScanForTag();
      // }
      // TODO
      break;
    case FUNC_EVERY_SECOND:
      break;
#ifdef USE_PN532_DATA_FUNCTION
    case FUNC_COMMAND_SENSOR:
      if (XSNS_40 == XdrvMailbox.index) {
        result = PN532_Command();
      }
      break;
#endif
  }
#ifdef DEBUG_PN532
  if (debug_pn532[0]) {     // if buffer non-empty, dump debug buffer
    Serial.printf(debug_pn532);
    Serial.printf("\n");
    Serial.flush();
    //AddLog_P2(LOG_LEVEL_DEBUG, PSTR("%s"), debug_pn532);
  }
#endif
  return result;
}

#endif // USE_PN532_HSU
