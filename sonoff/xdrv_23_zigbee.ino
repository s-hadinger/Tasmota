/*
  xdrv_23_zigbee.ino - zigbee serial support for Sonoff-Tasmota

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

#define XDRV_23                    23

const uint32_t ZIGBEE_BUFFER_SIZE = 256;  // Max ZNP frame is SOF+LEN+CMD1+CMD2+250+FCS = 255
const uint8_t  ZIGBEE_SOF = 0xFE;

#include <TasmotaSerial.h>


const char kZigbeeCommands[] PROGMEM = D_CMND_ZIGBEEZNPSEND;

void (* const ZigbeeCommand[])(void) PROGMEM = { &CmndZigbeeZNPSend };

// return value: 0=Ok proceed to next step, <0 Error, >0 go to a specific state
typedef int32_t (*State_EnterFunc)(uint8_t state);
typedef int32_t (*State_ReceivedFrameFunc)(uint8_t state, class SBuffer &buf);

typedef struct ZigbeeInitState {
	uint8_t										state_cur;					// current state
	uint8_t                   state_next;					// next state if ok
	uint8_t                   state_err;					// next state if error (bad message)
	uint8_t                   state_timeout;			// next state if timeout
	uint16_t									timeout;						// timeout in ms
	const uint8_t *           msg_sent;           // message to send
	const uint8_t *           msg_recv;           // filter to accept received message
	uint8_t										msg_sent_len;				// sizeof msg_sent
	uint8_t                   msg_recv_len;       // sizeof msg_recv
	State_EnterFunc						init_func;					// function called when entering this state
	State_ReceivedFrameFunc	  recv_func;					// fucnrion called when receiving a frame in this state
	//uint16_t									timeout;						// timeout in ms in this state
	//uint8_t										ok_next_state;			// next state if no error
	//uint8_t										timeout_next_state;	// what is the next state if timeout
	//uint8_t										error_next_state;		// what is the next state if error
} ZigbeeInitState;

// State machine states
enum ZnpStates {
	S_START,
	S_BOOT,
	S_INIT,
	S_VERS,
	S_READY,										// all initialization complete, ready to operate
	S_ABORT,										// fatal error, abort zigbee
};

TasmotaSerial *ZigbeeSerial = nullptr;

SBuffer *zigbee_buffer = nullptr;
bool zigbee_active = true;
bool zigbee_init_state_machine = false;		// the cc2530 initialization state machine is working
bool zigbee_ready = false;								// cc2530 initialization is complet, ready to operate
uint8_t zigbee_state_cur = S_START;				// start at first step in state machine
uint8_t  zigbee_state_next = 0;						// mailbox for next state, O=no change

// ZBS_* Zigbee Send
// ZBR_* Zigbee Recv
static const uint8_t ZBS_RESET[] PROGMEM = { 0x41, 0x00, 0x01 };	// SYS_RESET_REQ Software reset
static const uint8_t ZBR_RESET[] PROGMEM = { 0x41, 0x80 };				// SYS_RESET_REQ Software reset response
static const uint8_t ZBS_VERS[]  PROGMEM =  { 0x21, 0x02 };				// SYS:version
static const uint8_t ZBR_VERS[]  PROGMEM = { 0x61, 0x02 };				// SYS:version


static const ZigbeeInitState zb_states[] PROGMEM = {
	// S_START - fake state that immediately transitions to next state
	{ S_START, S_BOOT, S_BOOT, S_BOOT, 0, nullptr, nullptr, 0, 0, nullptr, nullptr },
	// S_BOOT - wait for 1 second that the cc2530 is fully initialized, or if we receive any frame
	{ S_BOOT, S_INIT, S_INIT, S_INIT, 1000, nullptr, nullptr, 0, 0, nullptr, nullptr },
	// S_INIT - send reinit command to cc2530 and wait for response,
	{ S_INIT, S_VERS, S_ABORT, S_ABORT, 5000, ZBS_RESET, ZBR_RESET, sizeof(ZBS_RESET), sizeof(ZBR_RESET), nullptr, nullptr },
	// S_VERS - read version
	{ S_VERS, S_READY, S_ABORT, S_ABORT, 500, ZBS_RESET, ZBR_RESET, sizeof(ZBS_RESET), sizeof(ZBR_RESET), nullptr, &Z_Recv_Vers },

};

int32_t Z_Recv_Vers(uint8_t state, class SBuffer &buf) {
	return 0;	// ok
}

// static const ZigbeeInitState init_states[] PROGMEM = {
// 	{ &enter_NoOp, &recv_Err, 2000, S_READY, S_ABORT, S_ABORT },		// S_START = 0
// };

int32_t enter_NoOp(uint32_t state) {
	return 0;
}

int32_t recv_Err(uint32_t state, class SBuffer &buf) {
	return -1;	// error
}

// retrieve the detailed information for a specific state
const ZigbeeInitState * ZigbeeStateInfo(uint8_t state_cur) {
	size_t num_states = sizeof(zb_states) / sizeof(ZigbeeInitState);
  AddLog_P2(LOG_LEVEL_DEBUG, PSTR("ZigbeeStateInfo: num_states = %d"), num_states);

	for (uint8_t i = 0; i < num_states; i++) {
		const ZigbeeInitState * state_info = &zb_states[i];
		if (state_info->state_cur == state_cur) {
			return state_info;
		}
	}
	return nullptr;
}

// ZigbeeMoveToState(uint8_t state_next, State_EnterFunc func) {
// 	zigbee_state_cur = state_next;
// 	if (func) {
// 		int32_t res = (*func)(zigbee_state_cur);
// 		if ()
// 	}
// }

void ZigbeeInitStateMachine(void) {
	static uint32_t next_timeout = 0;			// when is the next timeout occurring
	bool state_entering = false;					// are we entering the new state?
	uint32_t now = millis();

	if (zigbee_state_next) {
		// a state transition is triggered
		zigbee_state_cur = zigbee_state_next;
		zigbee_state_next = 0;		// reinit mailbox
		state_entering = true;
	}

	const ZigbeeInitState * state = ZigbeeStateInfo(zigbee_state_cur);
	if (!state) {
		// Fatal error, abort everything
	  AddLog_P2(LOG_LEVEL_ERROR, PSTR("ZigbeeInitStateMachine: unknown state = %d"), zigbee_state_cur);
		zigbee_init_state_machine = false;
		return;
	}

	if (state_entering) {
		// We are entering a new state
		next_timeout = now + state->timeout;
		if (state->init_func) {
			int32_t res = (*state->init_func)(zigbee_state_cur);
			AddLog_P2(LOG_LEVEL_DEBUG, PSTR("ZigbeeInitStateMachine: called init_func() state = %d, res = %d"), zigbee_state_cur, res);
			if (res > 0) {
				zigbee_state_next = res;
			} else if (res < 0) {
				zigbee_state_next = state->state_err;
			}
			// if res == 0 then ok, no change
		}
	} else if (now > next_timeout) {
		// timeout occured, move to next state
		AddLog_P2(LOG_LEVEL_DEBUG, PSTR("ZigbeeInitStateMachine: timeout occured state = %d"), zigbee_state_cur);
		//ZigbeeMoveToState(uint8_t state_next);
		zigbee_state_next = state->state_timeout;
	}
}

void ZigbeeInput(void)
{
	static uint32_t zigbee_polling_window = 0;
	static uint8_t fcs = ZIGBEE_SOF;
	static uint32_t zigbee_frame_len = 5;		// minimal zigbee frame lenght, will be updated when buf[1] is read
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
		AddLog_P2(LOG_LEVEL_DEBUG_MORE, PSTR("ZigbeeInput byte=%d len=%d"), zigbee_in_byte, zigbee_buffer->len());

		if (0 == zigbee_buffer->len()) {  // make sure all variables are correctly initialized
			zigbee_frame_len = 5;
			fcs = ZIGBEE_SOF;
		}

    if ((0 == zigbee_buffer->len()) && (ZIGBEE_SOF != zigbee_in_byte)) {
      // waiting for SOF (Start Of Frame) byte, discard anything else
      AddLog_P2(LOG_LEVEL_DEBUG_MORE, PSTR("ZigbeeInput discarding byte %02X"), zigbee_in_byte);
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
		ToHex((unsigned char*)zigbee_buffer->getBuffer(), zigbee_buffer->len(), hex_char, sizeof(hex_char));

		// buffer received, now check integrity
		if (zigbee_buffer->len() != zigbee_frame_len) {
			// Len is not correct, log and reject frame
      AddLog_P2(LOG_LEVEL_DEBUG, PSTR(D_JSON_ZIGBEEZNPRECEIVED ": received frame of wrong size %s"), hex_char);
		} else if (0x00 != fcs) {
			// FCS is wrong, packet is corrupt, log and reject frame
      AddLog_P2(LOG_LEVEL_DEBUG, PSTR(D_JSON_ZIGBEEZNPRECEIVED ": received bad FCS frame %s, %d"), hex_char, fcs);
		} else {
			// frame is correct
			AddLog_P2(LOG_LEVEL_DEBUG, PSTR(D_JSON_ZIGBEEZNPRECEIVED ": received correct frame %s"), hex_char);

			// now process the message
			SBuffer znp_buffer = zigbee_buffer->subBuffer(2, zigbee_frame_len - 3);	// remove SOF, LEN and FCS

			ToHex((unsigned char*)znp_buffer.getBuffer(), znp_buffer.len(), hex_char, sizeof(hex_char));
	    Response_P(PSTR("{\"" D_JSON_ZIGBEEZNPRECEIVED "\":\"%s\"}"), hex_char);
	    MqttPublishPrefixTopic_P(RESULT_OR_TELE, PSTR(D_JSON_ZIGBEEZNPRECEIVED));
	    XdrvRulesProcess();
		}
		zigbee_buffer->setLen(0);		// empty buffer
  }
}

/********************************************************************************************/

void ZigbeeInit(void)
{
  zigbee_active = false;
  if ((pin[GPIO_ZIGBEE_RX] < 99) && (pin[GPIO_ZIGBEE_TX] < 99)) {
    ZigbeeSerial = new TasmotaSerial(pin[GPIO_ZIGBEE_RX], pin[GPIO_ZIGBEE_TX]);
    if (ZigbeeSerial->begin(115200)) {    // ZNP is 115200, RTS/CTS (ignored), 8N1
      if (ZigbeeSerial->hardwareSerial()) {
        ClaimSerial();
				zigbee_buffer = new PreAllocatedSBuffer(sizeof(serial_in_buffer), serial_in_buffer);
			} else {
				zigbee_buffer = new SBuffer(ZIGBEE_BUFFER_SIZE);
			}
      zigbee_active = true;
      ZigbeeSerial->flush();
    }
  }
}

/*********************************************************************************************\
 * Commands
\*********************************************************************************************/

// void CmndZigbeeZNPSend(void)
// {
//   if (ZigbeeSerial && (XdrvMailbox.data_len > 0)) {
//     uint8_t code;
//
//     char *codes = RemoveSpace(XdrvMailbox.data);
//     int32_t size = strlen(XdrvMailbox.data);
//
//     while (size > 0) {
//       char stemp[3];
//       strlcpy(stemp, codes, sizeof(stemp));
//       code = strtol(stemp, nullptr, 16);
//       ZigbeeSerial->write(code);
//       size -= 2;
//       codes += 2;
//     }
//   }
//   ResponseCmndDone();
// }
void CmndZigbeeZNPSend(void)
{
  if (ZigbeeSerial && (XdrvMailbox.data_len > 0)) {
    uint8_t code;

    char *codes = RemoveSpace(XdrvMailbox.data);
    int32_t size = strlen(XdrvMailbox.data);

		SBuffer buf((size+1)/2);

    while (size > 0) {
      char stemp[3];
      strlcpy(stemp, codes, sizeof(stemp));
      code = strtol(stemp, nullptr, 16);
			buf.add8(code);
      size -= 2;
      codes += 2;
    }
		ZigbeeZNPSend(buf);
  }
  ResponseCmndDone();
}

void ZigbeeZNPSend(class SBuffer &message) {
	size_t len = message.len();
	if ((len < 2) || (len > 252)) {
		// abort, message cannot be less than 2 bytes for CMD1 and CMD2
		AddLog_P2(LOG_LEVEL_DEBUG, PSTR(D_JSON_ZIGBEEZNPSENT ": bad message len %d"), len);
		return;
	}
	uint8_t data_len = len - 2;		// removing CMD1 and CMD2

  if (ZigbeeSerial) {
		uint8_t fcs = data_len;

		ZigbeeSerial->write(ZIGBEE_SOF);		// 0xFE
		AddLog_P2(LOG_LEVEL_DEBUG_MORE, PSTR("ZNPSend SOF %02X"), ZIGBEE_SOF);
		ZigbeeSerial->write(data_len);
		AddLog_P2(LOG_LEVEL_DEBUG_MORE, PSTR("ZNPSend LEN %02X"), data_len);
		for (uint32_t i = 0; i < len; i++) {
			uint8_t b = message.get8(i);
			ZigbeeSerial->write(b);
			fcs ^= b;
			AddLog_P2(LOG_LEVEL_DEBUG_MORE, PSTR("ZNPSend byt %02X"), b);
		}
		ZigbeeSerial->write(fcs);			// finally send fcs checksum byte
		AddLog_P2(LOG_LEVEL_DEBUG_MORE, PSTR("ZNPSend FCS %02X"), fcs);
  }
	// Now send a MQTT message to report the sent message
	char hex_char[(len * 2) + 2];
	Response_P(PSTR("{\"" D_JSON_ZIGBEEZNPSENT "\":\"%s\"}"),
			ToHex(message.getBuffer(), len, hex_char, sizeof(hex_char)));
	MqttPublishPrefixTopic_P(RESULT_OR_TELE, PSTR(D_JSON_ZIGBEEZNPSENT));
	XdrvRulesProcess();
}

/*********************************************************************************************\
 * Interface
\*********************************************************************************************/

bool Xdrv23(uint8_t function)
{
  bool result = false;

  if (zigbee_active) {
    switch (function) {
      case FUNC_LOOP:
        if (ZigbeeSerial) { ZigbeeInput(); }
				if (zigbee_init_state_machine) { ZigbeeInitStateMachine(); }
        break;
      case FUNC_PRE_INIT:
        ZigbeeInit();
        break;
      case FUNC_COMMAND:
        result = DecodeCommand(kZigbeeCommands, ZigbeeCommand);
        break;
    }
  }
  return result;
}

#endif // USE_ZIGBEE
