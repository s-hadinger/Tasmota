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

enum ZnpCommandType {
  POLL = 0x00,
  SREQ = 0x20,
  AREQ = 0x40,
  SRSP = 0x60 };
enum ZnpSubsystem {
  RPC_Error = 0x00,
  SYS = 0x01,
  MAC = 0x02,
  NWK = 0x03,
  AF = 0x04,
  ZDO = 0x05,
  SAPI = 0x06,
  UTIL = 0x07,
  DEBUG = 0x08,
  APP = 0x09
};

// Commands in the SYS subsystem
enum SysCommand {
  SYS_RESET = 0x00,
  SYS_PING = 0x01,
  SYS_VERSION = 0x02,
  SYS_SET_EXTADDR = 0x03,
  SYS_GET_EXTADDR = 0x04,
  SYS_RAM_READ = 0x05,
  SYS_RAM_WRITE = 0x06,
  SYS_OSAL_NV_ITEM_INIT = 0x07,
  SYS_OSAL_NV_READ = 0x08,
  SYS_OSAL_NV_WRITE = 0x09,
  SYS_OSAL_START_TIMER = 0x0A,
  SYS_OSAL_STOP_TIMER = 0x0B,
  SYS_RANDOM = 0x0C,
  SYS_ADC_READ = 0x0D,
  SYS_GPIO = 0x0E,
  SYS_STACK_TUNE = 0x0F,
  SYS_SET_TIME = 0x10,
  SYS_GET_TIME = 0x11,
  SYS_OSAL_NV_DELETE = 0x12,
  SYS_OSAL_NV_LENGTH = 0x13,
  SYS_TEST_RF = 0x40,
  SYS_TEST_LOOPBACK = 0x41,
  SYS_RESET_IND = 0x80,
  SYS_OSAL_TIMER_EXPIRED = 0x81,
};
// Commands in the SAPI subsystem
enum SapiCommand {
  START_REQUEST = 0x00,
  BIND_DEVICE = 0x01,
  ALLOW_BIND = 0x02,
  SEND_DATA_REQUEST = 0x03,
  READ_CONFIGURATION = 0x04,
  WRITE_CONFIGURATION = 0x05,
  GET_DEVICE_INFO = 0x06,
  FIND_DEVICE_REQUEST = 0x07,
  PERMIT_JOINING_REQUEST = 0x08,
  SYSTEM_RESET = 0x09,
  START_CONFIRM = 0x80,
  BIND_CONFIRM = 0x81,
  ALLOW_BIND_CONFIRM = 0x82,
  SEND_DATA_CONFIRM = 0x83,
  FIND_DEVICE_CONFIRM = 0x85,
  RECEIVE_DATA_INDICATION = 0x87,
};
enum Z_configuration {
  STARTUP_OPTION = 0x03,
  POLL_RATE = 0x24,
  QUEUED_POLL_RATE = 0x25,
  RESPONSE_POLL_RATE = 0x26,
  POLL_FAILURE_RETRIES = 0x29,
  INDIRECT_MSG_TIMEOUT = 0x2B,
  ROUTE_EXPIRY_TIME = 0x2C,
  EXTENDED_PAN_ID = 0x2D,
  BCAST_RETRIES = 0x2E,
  PASSIVE_ACK_TIMEOUT = 0x2F,
  BCAST_DELIVERY_TIME = 0x30,
  APS_FRAME_RETRIES = 0x43,
  APS_ACK_WAIT_DURATION = 0x44,
  BINDING_TIME = 0x46,
  PRECFGKEY = 0x62,
  PRECFGKEYS_ENABLE = 0x63,
  SECURITY_MODE = 0x64,
  USERDESC = 0x81,
  PANID = 0x83,
  CHANLIST = 0x84,
  LOGICAL_TYPE = 0x87,
  ZDO_DIRECT_CB = 0x8F
};
enum Z_Status {
  Z_Success = 0x00,
  Z_Failure = 0x01,
  Z_InvalidParameter = 0x02,
  Z_MemError = 0x03,
  Z_BufferFull = 0x11
};

#include <TasmotaSerial.h>


const char kZigbeeCommands[] PROGMEM = D_CMND_ZIGBEEZNPSEND;

void (* const ZigbeeCommand[])(void) PROGMEM = { &CmndZigbeeZNPSend };

// return value: 0=Ok proceed to next step, <0 Error, >0 go to a specific state
typedef int32_t (*State_EnterFunc)(uint8_t state);
typedef int32_t (*State_ReceivedFrameFunc)(uint8_t state, class SBuffer &buf);

typedef struct ZigbeeState {
	uint8_t										state_cur;					// current state
	uint8_t                   state_next;					// next state if ok
	uint8_t                   state_err;					// next state if error (bad message)
	uint8_t                   state_timeout;			// next state if timeout
	const uint8_t *           msg_sent;           // message to send
	const uint8_t *           msg_recv;           // filter to accept received message
	uint8_t										msg_sent_len;				// sizeof msg_sent
	uint8_t                   msg_recv_len;       // sizeof msg_recv
	uint16_t									timeout;						// timeout in ms
	State_EnterFunc						init_func;					// function called when entering this state
	State_ReceivedFrameFunc	  recv_func;					// fucnrion called when receiving a frame in this state
	//uint16_t									timeout;						// timeout in ms in this state
	//uint8_t										ok_next_state;			// next state if no error
	//uint8_t										timeout_next_state;	// what is the next state if timeout
	//uint8_t										error_next_state;		// what is the next state if error
} ZigbeeState;

// State machine states
enum ZnpStates {
	S_START = 0,
	S_BOOT,
	S_INIT,
	S_VERS,
  S_PANID,                    // check PANID
  S_EXTPAN,                   // Extended PANID
	S_READY,										// all initialization complete, ready to operate
	S_ABORT,										// fatal error, abort zigbee
};

TasmotaSerial *ZigbeeSerial = nullptr;

struct ZigbeeStatus {
  bool active = true;
  bool state_machine = false;		// the cc2530 initialization state machine is working
  bool ready = false;								  // cc2530 initialization is complet, ready to operate
  uint8_t state_cur = S_START;				// start at first step in state machine
  uint8_t state_next = 0;						  // mailbox for next state, O=no change
  bool init_phase = true;             // initialization phase, before accepting zigbee traffic
};
struct ZigbeeStatus zigbee;

SBuffer *zigbee_buffer = nullptr;
ZigbeeState zigbee_state_cur_info;

// ZBS_* Zigbee Send
// ZBR_* Zigbee Recv
static const uint8_t ZBS_RESET[] PROGMEM = { AREQ | SYS, SYS_RESET, 0x01 };	  // 410001 SYS_RESET_REQ Software reset
static const uint8_t ZBR_RESET[] PROGMEM = { AREQ | SYS, SYS_RESET_IND };			// 4180 SYS_RESET_REQ Software reset response
static const uint8_t ZBS_VERS[]  PROGMEM = { SREQ | SYS, SYS_VERSION };				// 2102 SYS:version
static const uint8_t ZBR_VERS[]  PROGMEM = { SRSP | SYS, SYS_VERSION };				// 6102 SYS:version
static const uint8_t ZBS_PAN[]   PROGMEM = { SREQ | SAPI, READ_CONFIGURATION, PANID };				// 260483
static const uint8_t ZBR_PAN[]   PROGMEM = { SRSP | SAPI, READ_CONFIGURATION, Z_Success, PANID, 0x02, 0xFF, 0xFF };				// 6604008302FFFF
static const uint8_t ZBS_EXTPAN[]   PROGMEM = { SREQ | SAPI, READ_CONFIGURATION, EXTENDED_PAN_ID };				// 26042D
static const uint8_t ZBR_EXTPAN[]   PROGMEM = { SRSP | SAPI, READ_CONFIGURATION, Z_Success, EXTENDED_PAN_ID,
                                                0x08 /* len */, 0x62, 0x63, 0x15, 0x1D, 0x00, 0x4B, 0x12, 0x00 };				// 6604002D086263151D004B1200


static const ZigbeeState zb_states[] PROGMEM = {
	// S_START - fake state that immediately transitions to next state
	{ S_START, S_BOOT, S_BOOT, S_BOOT, nullptr, nullptr, 0, 0, 0, nullptr, nullptr },
	// S_BOOT - wait for 1 second that the cc2530 is fully initialized, or if we receive any frame
	{ S_BOOT, S_INIT, S_INIT, S_INIT, nullptr, nullptr, 0, 0, 2000, nullptr, nullptr },
	// S_INIT - send reinit command to cc2530 and wait for response,
	{ S_INIT, S_VERS, S_ABORT, S_ABORT, ZBS_RESET, ZBR_RESET, sizeof(ZBS_RESET), sizeof(ZBR_RESET), 5000, nullptr, nullptr },
	// S_VERS - read version
	{ S_VERS, S_PANID, S_ABORT, S_ABORT, ZBS_VERS, ZBR_VERS, sizeof(ZBR_VERS), sizeof(ZBR_VERS), 500, nullptr, &Z_Recv_Vers },
	// S_PANID - check the PAN ID
	{ S_PANID, S_EXTPAN, S_ABORT, S_ABORT, ZBS_PAN, ZBR_PAN, sizeof(ZBS_PAN), sizeof(ZBR_PAN), 500, nullptr, nullptr },
	// S_PANID - check the PAN ID
	{ S_EXTPAN, S_READY, S_ABORT, S_ABORT, ZBS_EXTPAN, ZBR_EXTPAN, sizeof(ZBS_EXTPAN), sizeof(ZBR_EXTPAN), 500, nullptr, nullptr },

	// S_ABORT - fatal error, abort zigbee
	{ S_ABORT, S_ABORT, S_ABORT, S_ABORT, nullptr, nullptr, 0, 0, 0, &Z_State_Abort, nullptr },
};

int32_t Z_Recv_Vers(uint8_t state, class SBuffer &buf) {
  // check that the version is supported
  // typical version for ZNP 1.2
  // 61020200-020603D91434010200000000
    // TranportRev = 02
    // Product = 00
    // MajorRel = 2
    // MinorRel = 6
    // MaintRel = 3
    // Revision = 20190425 d (0x013414D9)
  if ((0x02 == buf.get8(4)) && (0x06 == buf.get8(5))) {
  	return 0;	  // version 2.6.x is ok
  } else {
    return -2;  // abort
  }
}


int32_t Z_Recv_Default(uint8_t state, class SBuffer &buf) {
  // Default message handler for new messages
  if (zigbee.init_phase) {
    // if still during initialization phase, ignore any unexpected message
  	return -1;	// ignore message
  } else {
    // for now ignore message
    return -1;
  }
}

int32_t Z_State_Abort(uint8_t state) {
	AddLog_P(LOG_LEVEL_DEBUG, PSTR("Z_State_Abort: aborting Zigbee initialization"));
	zigbee.state_machine = false;
	zigbee.active = false;
  return 0;
}

int32_t Z_State_Ready(uint8_t state) {
	AddLog_P(LOG_LEVEL_DEBUG, PSTR("Z_State_Ready: zigbee initialization complete"));
	zigbee.state_machine = false;
  zigbee.init_phase = false;            // initialization phase complete
  return 0;
}

int32_t enter_NoOp(uint32_t state) {
	return 0;
}

int32_t recv_Err(uint32_t state, class SBuffer &buf) {
	return -2;	// error
}

// copy the cur_state_info into ram for current state
ZigbeeState * ZigbeeStateInfo(uint8_t state_cur) {
	size_t num_states = sizeof(zb_states) / sizeof(ZigbeeState);

	for (uint8_t i = 0; i < num_states; i++) {
		const ZigbeeState * state_info = &zb_states[i];
		if (pgm_read_byte(&state_info->state_cur) == state_cur) {
			// copy from PROGMEM into RAM
			memcpy_P(&zigbee_state_cur_info, state_info, sizeof(zigbee_state_cur_info));
			return &zigbee_state_cur_info;
		}
	}
	return nullptr;
}

void ZigbeeNextState(uint8_t next) {
  zigbee.state_next = next;
  zigbee.state_machine = true;     // restart state machine if it was stopped
}

void ZigbeeStateMachine(void) {
	static uint32_t next_timeout = 0;			// when is the next timeout occurring
	bool state_entering = false;					// are we entering a new state?
	uint32_t now = millis();

	if (zigbee.state_next) {
		// a state transition is triggered
		AddLog_P2(LOG_LEVEL_DEBUG, PSTR("ZigbeeStateMachine: transitioning fram state %d to %d"), zigbee.state_cur, zigbee.state_next);
		zigbee.state_cur = zigbee.state_next;
		zigbee.state_next = 0;		// reinit mailbox
		state_entering = true;
	}

	const ZigbeeState * state = ZigbeeStateInfo(zigbee.state_cur);
	if (!state) {
		// Fatal error, abort everything
	  AddLog_P2(LOG_LEVEL_ERROR, PSTR("ZigbeeStateMachine: unknown state = %d"), zigbee.state_cur);
		zigbee.state_machine = false;
		return;
	}

	if (state_entering) {
		// We are entering a new state
		next_timeout = now + state->timeout;
		int32_t res = 0;
		if (state->init_func) {
			res = (*state->init_func)(zigbee.state_cur);
			AddLog_P2(LOG_LEVEL_DEBUG, PSTR("ZigbeeStateMachine: called init_func() state = %d, res = %d"), zigbee.state_cur, res);
			if (res > 0) {
        ZigbeeNextState(res);
			} else if (res < 0) {
        ZigbeeNextState(state->state_err);
			}
			// if res == 0 then ok, no change
		}
		// if res == 0 or no function called, send the ZNP message if any
		if ((0 == res) && (state->msg_sent) && (state->msg_sent_len)) {
			ZigbeeZNPSend(state->msg_sent, state->msg_sent_len);
		}
	} else if (now > next_timeout) {
		// timeout occured, move to next state
		AddLog_P2(LOG_LEVEL_DEBUG, PSTR("ZigbeeStateMachine: timeout occured state = %d"), zigbee.state_cur);
		//ZigbeeMoveToState(uint8_t state_next);
    ZigbeeNextState(state->state_timeout);
	}
}

void ZigbeeProcessInput(class SBuffer &buf) {
  if (zigbee.state_machine) {
    // state is known not to be null, otherwise the error would have been catched in ZigbeeStateMachine()
    const ZigbeeState * state = ZigbeeStateInfo(zigbee.state_cur);

    // apply the receive filter, acts as 'startsWith()'
    bool recv_filter_match = true;
    if ((state->msg_recv) && (state->msg_recv_len)) {
      for (uint32_t i = 0; i < state->msg_recv_len; i++) {
        if (pgm_read_byte(&state->msg_recv[i]) != buf.get8(i)) {
          recv_filter_match = false;
          break;
        }
      }
    }
    AddLog_P2(LOG_LEVEL_DEBUG, PSTR("ZigbeeProcessInput: recv_filter_match = %d"), recv_filter_match);

    // if there is a recv_callback, call it now
    int32_t res = 0;          // default to ok
                              // res  =  0   - proceed to next state
                              // res  >  0   - proceed to the specified state
                              // res  = -1  - silently ignore the message
                              // res <= -2 - move to error state
    if (recv_filter_match) {
      if (state->recv_func) {
        res = (*state->recv_func)(zigbee.state_cur, buf);
      }
    } else {
      // if filter does not match, call default handler
      Z_Recv_Default(zigbee.state_cur, buf);
    }
    AddLog_P2(LOG_LEVEL_DEBUG, PSTR("ZigbeeProcessInput: res = %d"), res);

    // change state accordingly
    if (0 == res) {
      // if ok, move to next ok state
      ZigbeeNextState(state->state_next);
    } else if (res > 0) {
      // move to arbitrary state
      ZigbeeNextState(res);
    } else if (-1 == res) {
      // -1 means ignore message
    } else {
      // any other negative value means error
      ZigbeeNextState(state->state_err);
    }
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
		ToHex_P((unsigned char*)zigbee_buffer->getBuffer(), zigbee_buffer->len(), hex_char, sizeof(hex_char));

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

			SBuffer znp_buffer = zigbee_buffer->subBuffer(2, zigbee_frame_len - 3);	// remove SOF, LEN and FCS

			ToHex_P((unsigned char*)znp_buffer.getBuffer(), znp_buffer.len(), hex_char, sizeof(hex_char));
	    Response_P(PSTR("{\"" D_JSON_ZIGBEEZNPRECEIVED "\":\"%s\"}"), hex_char);
	    MqttPublishPrefixTopic_P(RESULT_OR_TELE, PSTR(D_JSON_ZIGBEEZNPRECEIVED));
	    XdrvRulesProcess();

			// now process the message
      ZigbeeProcessInput(znp_buffer);
		}
		zigbee_buffer->setLen(0);		// empty buffer
  }
}

/********************************************************************************************/

void ZigbeeInit(void)
{
  zigbee.active = false;
  if ((pin[GPIO_ZIGBEE_RX] < 99) && (pin[GPIO_ZIGBEE_TX] < 99)) {
		AddLog_P2(LOG_LEVEL_DEBUG_MORE, PSTR("Zigbee: GPIOs Rx:%d Tx:%d"), pin[GPIO_ZIGBEE_RX], pin[GPIO_ZIGBEE_TX]);
    ZigbeeSerial = new TasmotaSerial(pin[GPIO_ZIGBEE_RX], pin[GPIO_ZIGBEE_TX]);
    if (ZigbeeSerial->begin(115200)) {    // ZNP is 115200, RTS/CTS (ignored), 8N1
      if (ZigbeeSerial->hardwareSerial()) {
        ClaimSerial();
				zigbee_buffer = new PreAllocatedSBuffer(sizeof(serial_in_buffer), serial_in_buffer);
			} else {
				zigbee_buffer = new SBuffer(ZIGBEE_BUFFER_SIZE);
			}
      zigbee.active = true;
      ZigbeeNextState(S_START);             // start state machine in S_START state
			zigbee.init_phase = true;			// start the state machine
      ZigbeeSerial->flush();
    }
  }
}

/*********************************************************************************************\
 * Commands
\*********************************************************************************************/

void CmndZigbeeZNPSend(void)
{
  AddLog_P2(LOG_LEVEL_DEBUG_MORE, PSTR("CmndZigbeeZNPSend: entering, data_len = %d"), XdrvMailbox.data_len);
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
		ZigbeeZNPSend(buf.getBuffer(), buf.len());
  }
  ResponseCmndDone();
}

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
		AddLog_P2(LOG_LEVEL_DEBUG_MORE, PSTR("ZNPSend SOF %02X"), ZIGBEE_SOF);
		ZigbeeSerial->write(data_len);
		AddLog_P2(LOG_LEVEL_DEBUG_MORE, PSTR("ZNPSend LEN %02X"), data_len);
		for (uint32_t i = 0; i < len; i++) {
			uint8_t b = pgm_read_byte(msg + i);
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
			ToHex_P(msg, len, hex_char, sizeof(hex_char)));
	MqttPublishPrefixTopic_P(RESULT_OR_TELE, PSTR(D_JSON_ZIGBEEZNPSENT));
	XdrvRulesProcess();
}

/*********************************************************************************************\
 * Interface
\*********************************************************************************************/

bool Xdrv23(uint8_t function)
{
  bool result = false;

  if (zigbee.active) {
    switch (function) {
      case FUNC_LOOP:
        if (ZigbeeSerial) { ZigbeeInput(); }
				if (zigbee.state_machine) {
					ZigbeeStateMachine();
				}
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
