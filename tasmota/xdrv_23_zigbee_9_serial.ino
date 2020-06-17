/*
  xdrv_23_zigbee_9_serial.ino - zigbee: serial communication with MCU

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

#ifdef USE_ZIGBEE_ZNP
const uint32_t ZIGBEE_BUFFER_SIZE = 256;  // Max ZNP frame is SOF+LEN+CMD1+CMD2+250+FCS = 255
const uint8_t  ZIGBEE_SOF = 0xFE;
const uint8_t  ZIGBEE_SOF_ALT = 0xFF;
#endif // USE_ZIGBEE_ZNP

#ifdef USE_ZIGBEE_EZSP
const uint32_t ZIGBEE_BUFFER_SIZE = 256;
const uint8_t  ZIGBEE_EZSP_CANCEL = 0x1A;  // cancel byte
const uint8_t  ZIGBEE_EZSP_EOF = 0x7E;          // end of frame
const uint8_t  ZIGBEE_EZSP_ESCAPE = 0x7D;       // escape byte

class EZSP_Serial_t {
public:
  uint8_t  to_ack = 0;      // 0..7, frame number of next id to send
  uint8_t  from_ack = 0;    // 0..7, frame to ack
};

EZSP_Serial_t EZSP_Serial;

#endif // USE_ZIGBEE_EZSP

#include <TasmotaSerial.h>
TasmotaSerial *ZigbeeSerial = nullptr;

/********************************************************************************************/
//
// Called at event loop, checks for incoming data from the CC2530
//
void ZigbeeInputLoop(void) {

#ifdef USE_ZIGBEE_ZNP
	static uint32_t zigbee_polling_window = 0;    // number of milliseconds since first byte
	static uint8_t fcs = ZIGBEE_SOF;
	static uint32_t zigbee_frame_len = 5;		      // minimal zigbee frame length, will be updated when buf[1] is read
  // Receive only valid ZNP frames:
  // 00 - SOF = 0xFE
  // 01 - Length of Data Field - 0..250
  // 02 - CMD1 - first byte of command
  // 03 - CMD2 - second byte of command
  // 04..FD - Data Field
  // FE (or last) - FCS Checksum

  while (ZigbeeSerial->available()) {
    yield();
    uint8_t zigbee_in_byte = ZigbeeSerial->read();
		//AddLog_P2(LOG_LEVEL_DEBUG_MORE, PSTR("ZbInput byte=%d len=%d"), zigbee_in_byte, zigbee_buffer->len());

		if (0 == zigbee_buffer->len()) {  // make sure all variables are correctly initialized
			zigbee_frame_len = 5;
			fcs = ZIGBEE_SOF;
      // there is a rare race condition when an interrupt occurs when receiving the first byte
      // in this case the first bit (lsb) is missed and Tasmota receives 0xFF instead of 0xFE
      // We forgive this mistake, and next bytes are automatically resynchronized
      if (ZIGBEE_SOF_ALT == zigbee_in_byte) {
        AddLog_P2(LOG_LEVEL_INFO, PSTR("ZbInput forgiven first byte %02X (only for statistics)"), zigbee_in_byte);
        zigbee_in_byte = ZIGBEE_SOF;
      }
		}

    if ((0 == zigbee_buffer->len()) && (ZIGBEE_SOF != zigbee_in_byte)) {
      // waiting for SOF (Start Of Frame) byte, discard anything else
      AddLog_P2(LOG_LEVEL_INFO, PSTR("ZbInput discarding byte %02X"), zigbee_in_byte);
      continue;     // discard
    }

    if (zigbee_buffer->len() < zigbee_frame_len) {
			zigbee_buffer->add8(zigbee_in_byte);
      zigbee_polling_window = millis();                               // Wait for more data
			fcs ^= zigbee_in_byte;
    }

		if (zigbee_buffer->len() >= zigbee_frame_len) {
      zigbee_polling_window = 0;                                      // Publish now
      break;
    }

    // recalculate frame length
    if (02 == zigbee_buffer->len()) {
      // We just received the Lenght byte
      uint8_t len_byte = zigbee_buffer->get8(1);
      if (len_byte > 250)  len_byte = 250;    // ZNP spec says len is 250 max

      zigbee_frame_len = len_byte + 5;        // SOF + LEN + CMD1 + CMD2 + FCS = 5 bytes overhead
    }
  }

  if (zigbee_buffer->len() && (millis() > (zigbee_polling_window + ZIGBEE_POLLING))) {
    char hex_char[(zigbee_buffer->len() * 2) + 2];
		ToHex_P((unsigned char*)zigbee_buffer->getBuffer(), zigbee_buffer->len(), hex_char, sizeof(hex_char));

    AddLog_P2(LOG_LEVEL_DEBUG_MORE, PSTR(D_LOG_ZIGBEE "Bytes follow_read_metric = %0d"), ZigbeeSerial->getLoopReadMetric());
		// buffer received, now check integrity
		if (zigbee_buffer->len() != zigbee_frame_len) {
			// Len is not correct, log and reject frame
      AddLog_P2(LOG_LEVEL_INFO, PSTR(D_JSON_ZIGBEEZNPRECEIVED ": received frame of wrong size %s, len %d, expected %d"), hex_char, zigbee_buffer->len(), zigbee_frame_len);
		} else if (0x00 != fcs) {
			// FCS is wrong, packet is corrupt, log and reject frame
      AddLog_P2(LOG_LEVEL_INFO, PSTR(D_JSON_ZIGBEEZNPRECEIVED ": received bad FCS frame %s, %d"), hex_char, fcs);
		} else {
			// frame is correct
			//AddLog_P2(LOG_LEVEL_DEBUG_MORE, PSTR(D_JSON_ZIGBEEZNPRECEIVED ": received correct frame %s"), hex_char);

			SBuffer znp_buffer = zigbee_buffer->subBuffer(2, zigbee_frame_len - 3);	// remove SOF, LEN and FCS

			ToHex_P((unsigned char*)znp_buffer.getBuffer(), znp_buffer.len(), hex_char, sizeof(hex_char));
      Response_P(PSTR("{\"" D_JSON_ZIGBEEZNPRECEIVED "\":\"%s\"}"), hex_char);
      if (Settings.flag3.tuya_serial_mqtt_publish) {
        MqttPublishPrefixTopic_P(TELE, PSTR(D_RSLT_SENSOR));
        XdrvRulesProcess();
      } else {
        AddLog_P2(LOG_LEVEL_DEBUG, PSTR(D_LOG_ZIGBEE "%s"), mqtt_data);
      }
			// now process the message
      ZigbeeProcessInput(znp_buffer);
		}
		zigbee_buffer->setLen(0);		// empty buffer
  }
#endif // USE_ZIGBEE_ZNP

#ifdef USE_ZIGBEE_EZSP
	static uint32_t zigbee_polling_window = 0;    // number of milliseconds since first byte
  static bool escape = false;                          // was the previous byte an escape?
  bool frame_complete = false;                  // frame is ready and complete
  // Receive only valid EZSP frames:
  // 1A - Cancel - cancel all previous bytes
  // 7D - Escape byte - following byte is escaped
  // 7E - end of frame

  while (ZigbeeSerial->available()) {
    yield();
    uint8_t zigbee_in_byte = ZigbeeSerial->read();
		AddLog_P2(LOG_LEVEL_DEBUG_MORE, PSTR("ZIG: ZbInput byte=0x%02X len=%d"), zigbee_in_byte, zigbee_buffer->len());

		// if (0 == zigbee_buffer->len()) {  // make sure all variables are correctly initialized
    //   escape = false;
    //   frame_complete = false;
		// }

    if ((0x11 == zigbee_in_byte) || (0x13 == zigbee_in_byte)) {
      continue;           // ignore reserved bytes XON/XOFF
    }

    if (ZIGBEE_EZSP_ESCAPE == zigbee_in_byte) {
      AddLog_P2(LOG_LEVEL_DEBUG_MORE, PSTR("ZIG: Escape byte received"));
      escape = true;
      continue;
    }

    if (ZIGBEE_EZSP_CANCEL == zigbee_in_byte) {
      AddLog_P2(LOG_LEVEL_DEBUG_MORE, PSTR("ZIG: ZbInput byte=0x1A, cancel byte received, discarding %d bytes"), zigbee_buffer->len());
      zigbee_buffer->setLen(0);		// empty buffer
      escape = false;
      frame_complete = false;
      continue;                   // re-loop
    }

    if (ZIGBEE_EZSP_EOF == zigbee_in_byte) {
      // end of frame
      frame_complete = true;
      break;
    }

    if (zigbee_buffer->len() < ZIGBEE_BUFFER_SIZE) {
      if (escape) {
        // invert bit 5
        zigbee_in_byte ^= 0x20; 
        escape = false;
      }

			zigbee_buffer->add8(zigbee_in_byte);
      zigbee_polling_window = millis();                               // Wait for more data
    }   // adding bytes
  }     // while (ZigbeeSerial->available())

  uint32_t frame_len = zigbee_buffer->len();
  if (frame_complete || (frame_len && (millis() > (zigbee_polling_window + ZIGBEE_POLLING)))) {
    char hex_char[frame_len * 2 + 2];
    ToHex_P((unsigned char*)zigbee_buffer->getBuffer(), zigbee_buffer->len(), hex_char, sizeof(hex_char));

    AddLog_P2(LOG_LEVEL_DEBUG_MORE, PSTR(D_LOG_ZIGBEE "Bytes follow_read_metric = %0d"), ZigbeeSerial->getLoopReadMetric());
    if ((frame_complete) && (frame_len >= 3)) {
      // frame received and has at least 3 bytes (without EOF), checking CRC
      // AddLog_P2(LOG_LEVEL_INFO, PSTR(D_JSON_ZIGBEE_EZSP_RECEIVED ": received raw frame %s"), hex_char);
      uint16_t crc = 0xFFFF;                 // frame CRC
			// compute CRC
      for (uint32_t i=0; i<frame_len-2; i++) {
        crc = crc ^ ((uint16_t)zigbee_buffer->get8(i) << 8);
        for (uint32_t i=0; i<8; i++) {
          if (crc & 0x8000) {
            crc = (crc << 1) ^ 0x1021;          // polynom is x^16 + x^12 + x^5 + 1, CCITT standard
          } else {
            crc <<= 1;
          }
        }
      }

      uint16_t crc_received = zigbee_buffer->get8(frame_len - 2) << 8 | zigbee_buffer->get8(frame_len - 1);
      // remove 2 last bytes

      if (crc_received != crc) {
        AddLog_P2(LOG_LEVEL_INFO, PSTR(D_JSON_ZIGBEE_EZSP_RECEIVED ": bad crc (received 0x%04X, computed 0x%04X) %s"), crc_received, crc, hex_char);
      } else {
        // copy buffer
    	  SBuffer ezsp_buffer = zigbee_buffer->subBuffer(0, frame_len - 2);	// CRC

        // CRC is correct, apply de-stuffing if DATA frame
        if (0 == (ezsp_buffer.get8(0) & 0x80)) {
          // DATA frame
          uint8_t rand = 0x42;
          for (uint32_t i=1; i<ezsp_buffer.len(); i++) {
            ezsp_buffer.set8(i, ezsp_buffer.get8(i) ^ rand);
            if (rand & 1) { rand = (rand >> 1) ^ 0xB8; }
            else          { rand = (rand >> 1); }
          }
        }

        ToHex_P((unsigned char*)ezsp_buffer.getBuffer(), ezsp_buffer.len(), hex_char, sizeof(hex_char));
        Response_P(PSTR("{\"" D_JSON_ZIGBEE_EZSP_RECEIVED "\":\"%s\"}"), hex_char);
        if (Settings.flag3.tuya_serial_mqtt_publish) {
          MqttPublishPrefixTopic_P(TELE, PSTR(D_RSLT_SENSOR));
          XdrvRulesProcess();
        } else {
          AddLog_P2(LOG_LEVEL_INFO, PSTR(D_LOG_ZIGBEE "%s"), mqtt_data);    // TODO move to LOG_LEVEL_DEBUG when stable
        }
        // now process the message
        ZigbeeProcessInputRaw(ezsp_buffer);
      }
    } else {
      // the buffer timed-out, print error and discard
      AddLog_P2(LOG_LEVEL_INFO, PSTR(D_JSON_ZIGBEE_EZSP_RECEIVED ": time-out, discarding %s, %d"), hex_char);
    }
    zigbee_buffer->setLen(0);		// empty buffer
    escape = false;
    frame_complete = false;
  }

#endif // USE_ZIGBEE_EZSP

}

/********************************************************************************************/

// Initialize internal structures
void ZigbeeInitSerial(void)
{
// AddLog_P2(LOG_LEVEL_INFO, PSTR("ZigbeeInit Mem1 = %d"), ESP_getFreeHeap());
  zigbee.active = false;
  if (PinUsed(GPIO_ZIGBEE_RX) && PinUsed(GPIO_ZIGBEE_TX)) {
		AddLog_P2(LOG_LEVEL_DEBUG_MORE, PSTR(D_LOG_ZIGBEE "GPIOs Rx:%d Tx:%d"), Pin(GPIO_ZIGBEE_RX), Pin(GPIO_ZIGBEE_TX));
    // if seriallog_level is 0, we allow GPIO 13/15 to switch to Hardware Serial
    ZigbeeSerial = new TasmotaSerial(Pin(GPIO_ZIGBEE_RX), Pin(GPIO_ZIGBEE_TX), seriallog_level ? 1 : 2, 0, 256);   // set a receive buffer of 256 bytes
    ZigbeeSerial->begin(115200);
    if (ZigbeeSerial->hardwareSerial()) {
      ClaimSerial();
      uint32_t aligned_buffer = ((uint32_t)serial_in_buffer + 3) & ~3;
			zigbee_buffer = new PreAllocatedSBuffer(sizeof(serial_in_buffer) - 3, (char*) aligned_buffer);
		} else {
// AddLog_P2(LOG_LEVEL_INFO, PSTR("ZigbeeInit Mem2 = %d"), ESP_getFreeHeap());
			zigbee_buffer = new SBuffer(ZIGBEE_BUFFER_SIZE);
// AddLog_P2(LOG_LEVEL_INFO, PSTR("ZigbeeInit Mem3 = %d"), ESP_getFreeHeap());
		}
    zigbee.active = true;
		zigbee.init_phase = true;			// start the state machine
    zigbee.state_machine = true;      // start the state machine
    ZigbeeSerial->flush();
  }
// AddLog_P2(LOG_LEVEL_INFO, PSTR("ZigbeeInit Mem9 = %d"), ESP_getFreeHeap());
}

#ifdef USE_ZIGBEE_ZNP

void ZigbeeZNPSend(const uint8_t *msg, size_t len) {
	if ((len < 2) || (len > 252)) {
		// abort, message cannot be less than 2 bytes for CMD1 and CMD2
		AddLog_P2(LOG_LEVEL_DEBUG, PSTR(D_JSON_ZIGBEEZNPSENT ": bad message len %d"), len);
		return;
	}
	uint8_t data_len = len - 2;		// removing CMD1 and CMD2

  if (ZigbeeSerial) {
		uint8_t fcs = data_len;

		ZigbeeSerial->write(ZIGBEE_SOF);		// 0xFE
		//AddLog_P2(LOG_LEVEL_DEBUG_MORE, PSTR("ZNPSend SOF %02X"), ZIGBEE_SOF);
		ZigbeeSerial->write(data_len);
		//AddLog_P2(LOG_LEVEL_DEBUG_MORE, PSTR("ZNPSend LEN %02X"), data_len);
		for (uint32_t i = 0; i < len; i++) {
			uint8_t b = pgm_read_byte(msg + i);
			ZigbeeSerial->write(b);
			fcs ^= b;
			//AddLog_P2(LOG_LEVEL_DEBUG_MORE, PSTR("ZNPSend byt %02X"), b);
		}
		ZigbeeSerial->write(fcs);			// finally send fcs checksum byte
		//AddLog_P2(LOG_LEVEL_DEBUG_MORE, PSTR("ZNPSend FCS %02X"), fcs);
  }
	// Now send a MQTT message to report the sent message
	char hex_char[(len * 2) + 2];
  AddLog_P2(LOG_LEVEL_DEBUG, PSTR(D_LOG_ZIGBEE D_JSON_ZIGBEEZNPSENT " %s"),
                               		ToHex_P(msg, len, hex_char, sizeof(hex_char)));
}

//
// Same code for `ZbZNPSend` and `ZbZNPReceive`
// building the complete message (intro, length)
//
void CmndZbZNPSendOrReceive(bool send)
{
  if (ZigbeeSerial && (XdrvMailbox.data_len > 0)) {
    uint8_t code;

    char *codes = RemoveSpace(XdrvMailbox.data);
    int32_t size = strlen(XdrvMailbox.data);

		SBuffer buf((size+1)/2);

    while (size > 1) {
      char stemp[3];
      strlcpy(stemp, codes, sizeof(stemp));
      code = strtol(stemp, nullptr, 16);
			buf.add8(code);
      size -= 2;
      codes += 2;
    }
    if (send) {
      // Command was `ZbZNPSend`
      ZigbeeZNPSend(buf.getBuffer(), buf.len());
    } else {
      // Command was `ZbZNPReceive`
      ZigbeeProcessInput(buf);
    }
  }
  ResponseCmndDone();
}

// For debug purposes only, simulates a message received
void CmndZbZNPReceive(void)
{
  CmndZbZNPSendOrReceive(false);
}

void CmndZbZNPSend(void)
{
  CmndZbZNPSendOrReceive(true);
}

#endif // USE_ZIGBEE_ZNP

#ifdef USE_ZIGBEE_EZSP

// internal function to output a byte, and escape it (stuffing) if needed
void ZigbeeEZSPSend_Out(uint8_t out_byte) {
  switch (out_byte) {
    case 0x7E:      // Flag byte
    case 0x11:      // XON
    case 0x13:      // XOFF
    case 0x18:      // Substitute byte
    case 0x1A:      // Cancel byte
    case 0x7D:      // Escape byte
      ZigbeeSerial->write(ZIGBEE_EZSP_ESCAPE);      // send Escape byte 0x7D
      ZigbeeSerial->write(out_byte ^ 0x20);           // send with bit 5 inverted
      break;
    default:
      ZigbeeSerial->write(out_byte);                  // send unchanged
      break;
  }
}
// Send low-level EZSP frames
//
// The frame should contain the Control Byte and Data Field
// The frame shouldn't be escaped, nor randomized
//
// Before sending:
// - send Cancel byte (0x1A) if requested
// - randomize Data Field if DATA Frame
// - compute CRC16
// - escape (stuff) reserved bytes
// - add EOF (0x7E)
// - send frame
// send_cancel: should we first send a EZSP_CANCEL (0x1A) before the message to clear any leftover
void ZigbeeEZSPSendRaw(const uint8_t *msg, size_t len, bool send_cancel) {
	if ((len < 1) || (len > 252)) {
		// abort, message cannot be less than 2 bytes for CMD1 and CMD2
		AddLog_P2(LOG_LEVEL_DEBUG, PSTR(D_JSON_ZIGBEE_EZSP_SENT ": bad message len %d"), len);
		return;
	}
	uint8_t data_len = len - 2;		// removing CMD1 and CMD2

  if (ZigbeeSerial) {
    if (send_cancel) {
      ZigbeeSerial->write(ZIGBEE_EZSP_CANCEL);		// 0x1A
    }

    bool data_frame = (0 == (msg[0] & 0x80));
    uint8_t rand = 0x42;          // pseudo-randomizer initial value
    uint16_t crc = 0xFFFF;        // CRC16 CCITT initialization
    
    for (uint32_t i=0; i<len; i++) {
      uint8_t out_byte = msg[i];

      // apply randomization if DATA field
      if (data_frame && (i > 0)) {
        out_byte ^= rand;
        if (rand & 1) { rand = (rand >> 1) ^ 0xB8; }
        else          { rand = (rand >> 1); }
      }

      // compute CRC
      crc = crc ^ ((uint16_t)out_byte << 8);
      for (uint32_t i=0; i<8; i++) {
        if (crc & 0x8000) {
          crc = (crc << 1) ^ 0x1021;          // polynom is x^16 + x^12 + x^5 + 1, CCITT standard
        } else {
          crc <<= 1;
        }
      }

      // output byte
      ZigbeeEZSPSend_Out(out_byte);
    }
    // send CRC16 in big-endian
    ZigbeeEZSPSend_Out(crc >> 8);
    ZigbeeEZSPSend_Out(crc & 0xFF);

    // finally send End of Frame
    ZigbeeSerial->write(ZIGBEE_EZSP_EOF);		// 0x1A
  }
  // Now send a MQTT message to report the sent message
  char hex_char[(len * 2) + 2];
  AddLog_P2(LOG_LEVEL_DEBUG, PSTR(D_LOG_ZIGBEE D_JSON_ZIGBEE_EZSP_SENT_RAW " %s"),
                                  ToHex_P(msg, len, hex_char, sizeof(hex_char)));
}

// Send an EZSP DATA frame, automatically calculating the correct frame numbers
void ZigbeeEZSPSend(const uint8_t *msg, size_t len, bool send_cancel) {
  uint8_t control_byte = ((EZSP_Serial.to_ack & 0x07) << 4) + (EZSP_Serial.from_ack & 0x07);
  // increment to_ack
  EZSP_Serial.to_ack = (EZSP_Serial.to_ack + 1) & 0x07;
  // build complete frame
  SBuffer buf(len+1);
  buf.add8(control_byte);
  buf.addBuffer(msg, len);
  // send
  ZigbeeEZSPSendRaw(buf.getBuffer(), buf.len(), true);
}

// Receive raw ASH frame (CRC was removed, data unstuffed) but still contains frame numbers
int32_t ZigbeeProcessInputRaw(class SBuffer &buf) {
  uint8_t control_byte = buf.get8(0);
  uint8_t ack_num = control_byte & 0x07;        // keep 3 LSB
  if (control_byte & 0x80) {

    // non DATA frame
    uint8_t frame_type = control_byte & 0xE0;   // keep 3 MSB
    if (frame_type == 0x80) {

      // ACK
      EZSP_Serial.from_ack = ack_num;           // update ack num
    } else if (frame_type == 0xA0) {

      // NAK
      AddLog_P2(LOG_LEVEL_INFO, PSTR("ZIG: Received NAK %d, resending not implemented"), ack_num);
    } else if (control_byte == 0xC1) {
      
      // RSTACK
      // received just after boot, either because of Power up, hardware reset or RST
      Z_EZSP_RSTACK(buf.get8(2));
    } else if (control_byte == 0xC2) {
      
      // ERROR
      Z_EZSP_ERROR(buf.get8(2));
      zigbee.active = false;           // stop all zigbee activities
    } else {

      // Unknown
      AddLog_P2(LOG_LEVEL_DEBUG, PSTR("ZIG: Received unknown control byte 0x%02X"), control_byte);
    }
  } else {

    // DATA Frame
    // check the frame number, and send ACK or NAK
    if ((control_byte & 0x07) != EZSP_Serial.to_ack) {
      AddLog_P2(LOG_LEVEL_INFO, PSTR("ZIG: wrong ack, received %d, expected %d"), control_byte & 0x07, EZSP_Serial.to_ack);
      //EZSP_Serial.to_ack = control_byte & 0x07;
    }
    // MCU acknowledged the correct frame
    // we acknowledge the frame too
    EZSP_Serial.from_ack = ((control_byte >> 4) + 1) & 0x07;
    uint8_t ack_byte = 0x80 | EZSP_Serial.from_ack;
    ZigbeeEZSPSendRaw(&ack_byte, 1, false);   // send a 1-byte ACK
  }
}

//
// Same code for `ZbZNPSend` and `ZbZNPReceive`
// building the complete message (intro, length)
//
void CmndZbEZSPSendOrReceiveRaw(bool send)
{
  if (ZigbeeSerial && (XdrvMailbox.data_len > 0)) {
    uint8_t code;

    char *codes = RemoveSpace(XdrvMailbox.data);
    int32_t size = strlen(XdrvMailbox.data);

		SBuffer buf((size+1)/2);

    while (size > 1) {
      char stemp[3];
      strlcpy(stemp, codes, sizeof(stemp));
      code = strtol(stemp, nullptr, 16);
			buf.add8(code);
      size -= 2;
      codes += 2;
    }
    if (send) {
      // Command was `ZbEZSPSend`
      ZigbeeEZSPSendRaw(buf.getBuffer(), buf.len(), true);
    } else {
      // Command was `ZbEZSPReceive`
      ZigbeeProcessInputRaw(buf);
    }
  }
  ResponseCmndDone();
}

// For debug purposes only, simulates a message received
void CmndZbEZSPReceiveRaw(void)
{
  CmndZbEZSPSendOrReceiveRaw(false);
}

void CmndZbEZSPSendRaw(void)
{
  CmndZbEZSPSendOrReceiveRaw(true);
}

//
//
void CmndZbEZSPSendOrReceive(bool send)
{
  if (ZigbeeSerial && (XdrvMailbox.data_len > 0)) {
    uint8_t code;

    char *codes = RemoveSpace(XdrvMailbox.data);
    int32_t size = strlen(XdrvMailbox.data);

		SBuffer buf((size+1)/2);

    while (size > 1) {
      char stemp[3];
      strlcpy(stemp, codes, sizeof(stemp));
      code = strtol(stemp, nullptr, 16);
			buf.add8(code);
      size -= 2;
      codes += 2;
    }
    if (send) {
      // Command was `ZbEZSPSend`
      ZigbeeEZSPSend(buf.getBuffer(), buf.len(), true);
    } else {
      // Command was `ZbEZSPReceive`
      ZigbeeProcessInput(buf);
    }
  }
  ResponseCmndDone();
}
// Variants with managed ASH frame numbers
// For debug purposes only, simulates a message received
void CmndZbEZSPReceive(void)
{
  CmndZbEZSPSendOrReceive(false);
}

void CmndZbEZSPSend(void)
{
  CmndZbEZSPSendOrReceive(true);
}
#endif // USE_ZIGBEE_EZSP

//
// Internal function, send the low-level frame
// Input:
// - shortaddr: 16-bits short address, or 0x0000 if group address
// - groupaddr: 16-bits group address, or 0x0000 if unicast using shortaddr
// - clusterIf: 16-bits cluster number
// - endpoint:  8-bits target endpoint (source is always 0x01), unused for group addresses. Should not be 0x00 except when sending to group address.
// - cmdId:     8-bits ZCL command number
// - clusterSpecific: boolean, is the message general cluster or cluster specific, used to create the FC byte of ZCL
// - msg:       pointer to byte array, payload of ZCL message (len is following), ignored if nullptr
// - len:       length of the 'msg' payload
// - needResponse: boolean, true = we ask the target to respond, false = the target should not respond
// - transacId: 8-bits, transation id of message (should be incremented at each message), used both for Zigbee message number and ZCL message number
// Returns: None
//
void ZigbeeZCLSend_Raw(uint16_t shortaddr, uint16_t groupaddr, uint16_t clusterId, uint8_t endpoint, uint8_t cmdId, bool clusterSpecific, uint16_t manuf, const uint8_t *msg, size_t len, bool needResponse, uint8_t transacId) {

#ifdef USE_ZIGBEE_ZNP
  SBuffer buf(32+len);
  buf.add8(Z_SREQ | Z_AF);          // 24
  buf.add8(AF_DATA_REQUEST_EXT);    // 02
  if (BAD_SHORTADDR == shortaddr) {        // if no shortaddr we assume group address
    buf.add8(Z_Addr_Group);         // 01
    buf.add64(groupaddr);           // group address, only 2 LSB, upper 6 MSB are discarded
    buf.add8(0xFF);                 // dest endpoint is not used for group addresses
  } else {
    buf.add8(Z_Addr_ShortAddress);  // 02
    buf.add64(shortaddr);           // dest address, only 2 LSB, upper 6 MSB are discarded
    buf.add8(endpoint);             // dest endpoint
  }
  buf.add16(0x0000);                // dest Pan ID, 0x0000 = intra-pan
  buf.add8(0x01);                   // source endpoint
  buf.add16(clusterId);
  buf.add8(transacId);              // transacId
  buf.add8(0x30);                   // 30 options
  buf.add8(0x1E);                   // 1E radius

  buf.add16(3 + len + (manuf ? 2 : 0));
  buf.add8((needResponse ? 0x00 : 0x10) | (clusterSpecific ? 0x01 : 0x00) | (manuf ? 0x04 : 0x00));                 // Frame Control Field
  if (manuf) {
    buf.add16(manuf);               // add Manuf Id if not null
  }
  buf.add8(transacId);              // Transaction Sequance Number
  buf.add8(cmdId);
  if (len > 0) {
    buf.addBuffer(msg, len);        // add the payload
  }

  ZigbeeZNPSend(buf.getBuffer(), buf.len());
#endif // USE_ZIGBEE_ZNP
}

#endif // USE_ZIGBEE
