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

#define XDRV_23                    23

const uint32_t ZIGBEE_BUFFER_SIZE = 256;  // Max ZNP frame is SOF+LEN+CMD1+CMD2+250+FCS = 255
const uint8_t  ZIGBEE_SOF = 0xFE;

//#define Z_USE_SOFTWARE_SERIAL

#ifdef Z_USE_SOFTWARE_SERIAL
#include <SoftwareSerial.h>
SoftwareSerial *ZigbeeSerial = nullptr;
#else
#include <TasmotaSerial.h>
TasmotaSerial *ZigbeeSerial = nullptr;
#endif


const char kZigbeeCommands[] PROGMEM = "|" D_CMND_ZIGBEEZNPSEND "|" D_CMND_ZIGBEE_PERMITJOIN;

void (* const ZigbeeCommand[])(void) PROGMEM = { &CmndZigbeeZNPSend, &CmndZigbeePermitJoin };

int32_t Z_ReceiveDeviceInfo(int32_t res, class SBuffer &buf) {
  // Ex= 6700.00.6263151D004B1200.0000.07.09.02.83869991
  // IEEE Adr (8 bytes) = 0x00124B001D156362
  // Short Addr (2 bytes) = 0x0000
  // Device Type (1 byte) = 0x07 (coord?)
  // Device State (1 byte) = 0x09 (coordinator started)
  // NumAssocDevices (1 byte) = 0x02
  // List of devices: 0x8683, 0x9199
  Z_IEEEAddress  long_adr = buf.get64(3);
  Z_ShortAddress short_adr = buf.get16(11);
  uint8_t device_type = buf.get8(13);
  uint8_t device_state = buf.get8(14);
  uint8_t device_associated = buf.get8(15);

  char hex[20];
  Uint64toHex(long_adr, hex, 64);
  Response_P(PSTR("{\"" D_JSON_ZIGBEE_STATUS "\":{"
                  "\"Status\":%d,\"IEEEAddr\":\"%s\",\"ShortAddr\":\"0x%04X\""
                  ",\"DeviceType\":%d,\"DeviceState\":%d"
                  ",\"NumAssocDevices\":%d"),
                  ZIGBEE_STATUS_CC_INFO, hex, short_adr, device_type, device_state,
                  device_associated);

  if (device_associated > 0) {
    uint idx = 16;
    ResponseAppend_P(PSTR(",\"AssocDevicesList\":["));
    for (uint32_t i = 0; i < device_associated; i++) {
      if (i > 0) { ResponseAppend_P(PSTR(",")); }
      ResponseAppend_P(PSTR("\"0x%04X\""), buf.get16(idx));
      idx += 2;
    }
    ResponseAppend_P(PSTR("]"));
  }

  ResponseJsonEnd();      // append '}'
  ResponseJsonEnd();      // append '}'
  MqttPublishPrefixTopic_P(RESULT_OR_TELE, PSTR(D_JSON_ZIGBEE_STATUS));
  XdrvRulesProcess();

  return res;
}

int32_t Z_CheckNVWrite(int32_t res, class SBuffer &buf) {
  // Check the status after NV Init "ZNP Has Configured"
  // Good response should be 610700 or 610709 (Success or Created)
  // We only filter the response on 6107 and check the code in this function
  uint8_t status = buf.get8(2);
  if ((0x00 == status) || (0x09 == status)) {
    return 0;   // Ok, continue
  } else {
    return -2;  // Error
  }
}

int32_t Z_ReceiveCheckVersion(int32_t res, class SBuffer &buf) {
  // check that the version is supported
  // typical version for ZNP 1.2
  // 61020200-02.06.03.D9143401.0200000000
  // TranportRev = 02
  // Product = 00
  // MajorRel = 2
  // MinorRel = 6
  // MaintRel = 3
  // Revision = 20190425 d (0x013414D9)
  uint8_t major_rel = buf.get8(4);
  uint8_t minor_rel = buf.get8(5);
  uint8_t maint_rel = buf.get8(6);
  uint32_t revision = buf.get32(7);

  Response_P(PSTR("{\"" D_JSON_ZIGBEE_STATUS "\":{"
                  "\"Status\":%d,\"MajorRel\":%d,\"MinorRel\":%d"
                  ",\"MaintRel\":%d,\"Revision\":%d}}"),
                  ZIGBEE_STATUS_CC_VERSION, major_rel, minor_rel,
                  maint_rel, revision);

  MqttPublishPrefixTopic_P(RESULT_OR_TELE, PSTR(D_JSON_ZIGBEE_STATUS));
  XdrvRulesProcess();

  if ((0x02 == major_rel) && (0x06 == minor_rel)) {
  	return 0;	  // version 2.6.x is ok
  } else {
    return ZIGBEE_LABEL_UNSUPPORTED_VERSION;  // abort
  }
}

bool Z_ReceiveMatchPrefix(const class SBuffer &buf, const uint8_t *match) {
  if ( (pgm_read_byte(&match[0]) == buf.get8(0)) &&
       (pgm_read_byte(&match[1]) == buf.get8(1)) ) {
    return true;
  } else {
    return false;
  }
}

int32_t Z_ReceivePermitJoinStatus(int32_t res, const class SBuffer &buf) {
  // we received a PermitJoin status change
  uint8_t     duration = buf.get8(2);
  uint8_t     status_code;
  const char* message;

  if (0xFF == duration) {
    status_code = ZIGBEE_STATUS_PERMITJOIN_OPEN_XX;
    message = PSTR("Enable Pairing mode until next boot");
  } else if (duration > 0) {
    status_code = ZIGBEE_STATUS_PERMITJOIN_OPEN_60;
    message = PSTR("Enable Pairing mode for %d seconds");
  } else {
    status_code = ZIGBEE_STATUS_PERMITJOIN_CLOSE;
    message = PSTR("Disable Pairing mode");
  }
  Response_P(PSTR("{\"" D_JSON_ZIGBEE_STATUS "\":{"
                  "\"Status\":%d,\"Message\":\""),
                  status_code);
  ResponseAppend_P(message, duration);
  ResponseAppend_P(PSTR("\"}}"));

  MqttPublishPrefixTopic_P(RESULT_OR_TELE, PSTR(D_JSON_ZIGBEE_STATUS));
  XdrvRulesProcess();
  return -1;
}

// Send ACTIVE_EP_REQ to collect active endpoints for this address
void Z_SendActiveEpReq(uint16_t shortaddr) {
  uint8_t ActiveEpReq[] = { Z_SREQ | Z_ZDO, ZDO_ACTIVE_EP_REQ,
              Z_B0(shortaddr), Z_B1(shortaddr), Z_B0(shortaddr), Z_B1(shortaddr) };

  uint8_t NodeDescReq[] = { Z_SREQ | Z_ZDO, ZDO_NODE_DESC_REQ,
              Z_B0(shortaddr), Z_B1(shortaddr), Z_B0(shortaddr), Z_B1(shortaddr) };

  ZigbeeZNPSend(ActiveEpReq, sizeof(ActiveEpReq));
  ZigbeeZNPSend(NodeDescReq, sizeof(NodeDescReq));
}

const char* Z_DeviceType[] = { "Coordinator", "Router", "End Device", "Unknown" };
int32_t Z_ReceiveNodeDesc(int32_t res, const class SBuffer &buf) {
  // Received ZDO_NODE_DESC_RSP
  Z_ShortAddress    srcAddr = buf.get16(2);
  uint8_t           status  = buf.get8(4);
  Z_ShortAddress    nwkAddr = buf.get16(5);
  uint8_t           logicalType = buf.get8(7);
  uint8_t           apsFlags = buf.get8(8);
  uint8_t           MACCapabilityFlags = buf.get8(9);
  uint16_t          manufacturerCapabilities = buf.get16(10);
  uint8_t           maxBufferSize = buf.get8(12);
  uint16_t          maxInTransferSize = buf.get16(13);
  uint16_t          serverMask = buf.get16(15);
  uint16_t          maxOutTransferSize = buf.get16(17);
  uint8_t           descriptorCapabilities = buf.get8(19);

  if (0 == status) {
    uint8_t           deviceType = logicalType & 0x7;   // 0=coordinator, 1=router, 2=end device
    if (deviceType > 3) { deviceType = 3; }
    bool              complexDescriptorAvailable = (logicalType & 0x08) ? 1 : 0;

    Response_P(PSTR("{\"" D_JSON_ZIGBEE_STATUS "\":{"
                    "\"Status\":%d,\"NodeType\":\"%s\",\"ComplexDesc\":%s}}"),
                    ZIGBEE_STATUS_NODE_DESC, Z_DeviceType[deviceType],
                    complexDescriptorAvailable ? "true" : "false"
                    );

    MqttPublishPrefixTopic_P(RESULT_OR_TELE, PSTR(D_JSON_ZIGBEEZCLRECEIVED));
    XdrvRulesProcess();
  }

  return -1;
}

int32_t Z_ReceiveActiveEp(int32_t res, const class SBuffer &buf) {
  // Received ZDO_ACTIVE_EP_RSP
  Z_ShortAddress    srcAddr = buf.get16(2);
  uint8_t           status  = buf.get8(4);
  Z_ShortAddress    nwkAddr = buf.get16(5);
  uint8_t           activeEpCount = buf.get8(7);
  uint8_t*          activeEpList = (uint8_t*) buf.charptr(8);

  // TODO add active EPs to Device list

  Response_P(PSTR("{\"" D_JSON_ZIGBEE_STATUS "\":{"
                  "\"Status\":%d,\"ActiveEndpoints\":["),
                  ZIGBEE_STATUS_ACTIVE_EP);
  for (uint32_t i = 0; i < activeEpCount; i++) {
    if (i > 0) { ResponseAppend_P(PSTR(",")); }
    char hex[8];
    ResponseAppend_P(PSTR("\"0x%02X\""), activeEpList[i]);
  }
  ResponseAppend_P(PSTR("]}}"));
  MqttPublishPrefixTopic_P(RESULT_OR_TELE, PSTR(D_JSON_ZIGBEEZCLRECEIVED));
  XdrvRulesProcess();
  return -1;
}

int32_t Z_ReceiveEndDeviceAnnonce(int32_t res, const class SBuffer &buf) {
  Z_ShortAddress    srcAddr = buf.get16(2);
  Z_ShortAddress    nwkAddr = buf.get16(4);
  Z_IEEEAddress     ieeeAddr = buf.get64(6);
  uint8_t           capabilities = buf.get8(14);

  Z_AddDeviceLongAddr(nwkAddr, ieeeAddr);
//   String dump = Z_DumpDevices();
// Serial.printf(">>> Devices dump = %s\n", dump.c_str());

  char hex[20];
  Uint64toHex(ieeeAddr, hex, 64);
  Response_P(PSTR("{\"" D_JSON_ZIGBEE_STATUS "\":{"
                  "\"Status\":%d,\"IEEEAddr\":\"%s\",\"ShortAddr\":\"0x%04X\""
                  ",\"PowerSource\":%s,\"ReceiveWhenIdle\":%s,\"Security\":%s}}"),
                  ZIGBEE_STATUS_DEVICE_ANNOUNCE, hex, nwkAddr,
                  (capabilities & 0x04) ? "true" : "false",
                  (capabilities & 0x08) ? "true" : "false",
                  (capabilities & 0x40) ? "true" : "false"
                  );

  MqttPublishPrefixTopic_P(RESULT_OR_TELE, PSTR(D_JSON_ZIGBEEZCLRECEIVED));
  XdrvRulesProcess();
  Z_SendActiveEpReq(nwkAddr);
  return -1;
}

int32_t Z_ReceiveAfIncomingMessage(int32_t res, const class SBuffer &buf) {
  uint16_t        groupid = buf.get16(2);
  uint16_t        clusterid = buf.get16(4);
  Z_ShortAddress  srcaddr = buf.get16(6);
  uint8_t         srcendpoint = buf.get8(8);
  uint8_t         dstendpoint = buf.get8(9);
  uint8_t         wasbroadcast = buf.get8(10);
  uint8_t         linkquality = buf.get8(11);
  uint8_t         securityuse = buf.get8(12);
  uint32_t        timestamp = buf.get32(13);
  uint8_t         seqnumber = buf.get8(17);

  ZCLFrame zcl_received = ZCLFrame::parseRawFrame(buf, 19, buf.get8(18), clusterid, groupid);

  zcl_received.publishMQTTReceived(groupid, clusterid, srcaddr,
                                  srcendpoint, dstendpoint, wasbroadcast,
                                  linkquality, securityuse, seqnumber,
                                  timestamp);

  char shortaddr[8];
  snprintf_P(shortaddr, sizeof(shortaddr), PSTR("0x%04X"), srcaddr);

  DynamicJsonBuffer jsonBuffer;
  JsonObject& json_root = jsonBuffer.createObject();
  JsonObject& json = json_root.createNestedObject(shortaddr);
  if ( (!zcl_received.isClusterSpecificCommand()) && (ZCL_REPORT_ATTRIBUTES == zcl_received.getCmdId())) {
   zcl_received.parseRawAttributes(json);
  } else if (zcl_received.isClusterSpecificCommand()) {
   zcl_received.parseClusterSpecificCommand(json);
  }
  zcl_received.postProcessAttributes(json);

  String msg("");
  msg.reserve(100);
  json_root.printTo(msg);

  Response_P(PSTR("%s"), msg.c_str());
  MqttPublishPrefixTopic_P(RESULT_OR_TELE, PSTR(D_JSON_ZIGBEEZCLRECEIVED));
  XdrvRulesProcess();
  return -1;
}

int32_t Z_Recv_Default(int32_t res, const class SBuffer &buf) {
  // Default message handler for new messages
  AddLog_P2(LOG_LEVEL_DEBUG, PSTR("ZIG: Z_Recv_Default"));
  if (zigbee.init_phase) {
    // if still during initialization phase, ignore any unexpected message
  	return -1;	// ignore message
  } else {
    if (Z_ReceiveMatchPrefix(buf, ZBR_AF_INCOMING_MESSAGE)) {
      return Z_ReceiveAfIncomingMessage(res, buf);
    } else if (Z_ReceiveMatchPrefix(buf, ZBR_END_DEVICE_ANNCE_IND)) {
      return Z_ReceiveEndDeviceAnnonce(res, buf);
    } else if (Z_ReceiveMatchPrefix(buf, ZBR_PERMITJOIN_AREQ_OPEN_XX)) {
      return Z_ReceivePermitJoinStatus(res, buf);
    } else if (Z_ReceiveMatchPrefix(buf, AREQ_ZDO_NODEDESCRSP)) {
      return Z_ReceiveNodeDesc(res, buf);
    } else if (Z_ReceiveMatchPrefix(buf, AREQ_ZDO_ACTIVEEPRSP)) {
      return Z_ReceiveActiveEp(res, buf);
    }
    return -1;
  }
}

int32_t Z_State_Ready(uint8_t value) {
  zigbee.init_phase = false;             // initialization phase complete
  return 0;                              // continue
}

int32_t ZigbeeProcessInput(class SBuffer &buf) {
  if (!zigbee.state_machine) { return -1; }     // if state machine is stopped, send 'ignore' message

  // apply the receive filter, acts as 'startsWith()'
  bool recv_filter_match = true;
  bool recv_prefix_match = false;      // do the first 2 bytes match the response
  if ((zigbee.recv_filter) && (zigbee.recv_filter_len > 0)) {
    if (zigbee.recv_filter_len >= 2) {
      recv_prefix_match = false;
      if ( (pgm_read_byte(&zigbee.recv_filter[0]) == buf.get8(0)) &&
           (pgm_read_byte(&zigbee.recv_filter[1]) == buf.get8(1)) ) {
        recv_prefix_match = true;
      }
    }

    for (uint32_t i = 0; i < zigbee.recv_filter_len; i++) {
      if (pgm_read_byte(&zigbee.recv_filter[i]) != buf.get8(i)) {
        recv_filter_match = false;
        break;
      }
    }

    AddLog_P2(LOG_LEVEL_DEBUG, PSTR("ZIG: ZigbeeProcessInput: recv_prefix_match = %d, recv_filter_match = %d"), recv_prefix_match, recv_filter_match);
  }

  // if there is a recv_callback, call it now
  int32_t res = -1;         // default to ok
                            // res  =  0   - proceed to next state
                            // res  >  0   - proceed to the specified state
                            // res  = -1  - silently ignore the message
                            // res <= -2 - move to error state
  // pre-compute the suggested value
  if ((zigbee.recv_filter) && (zigbee.recv_filter_len > 0)) {
    if (!recv_prefix_match) {
      res = -1;    // ignore
    } else {  // recv_prefix_match
      if (recv_filter_match) {
        res = 0;     // ok
      } else {
        if (zigbee.recv_until) {
          res = -1;  // ignore until full match
        } else {
          res = -2;  // error, because message is expected but wrong value
        }
      }
    }
  } else {    // we don't have any filter, ignore message by default
    res = -1;
  }

  if (recv_prefix_match) {
    if (zigbee.recv_func) {
      res = (*zigbee.recv_func)(res, buf);
    }
  }
  if (-1 == res) {
    // if frame was ignored up to now
    if (zigbee.recv_unexpected) {
      res = (*zigbee.recv_unexpected)(res, buf);
    }
  }
  AddLog_P2(LOG_LEVEL_DEBUG, PSTR("ZIG: ZigbeeProcessInput: res = %d"), res);

  // change state accordingly
  if (0 == res) {
    // if ok, continue execution
    zigbee.state_waiting = false;
  } else if (res > 0) {
    ZigbeeGotoLabel(res);     // if >0 then go to specified label
  } else if (-1 == res) {
    // -1 means ignore message
    // just do nothing
  } else {
    // any other negative value means error
    ZigbeeGotoLabel(zigbee.on_error_goto);
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
      AddLog_P2(LOG_LEVEL_INFO, PSTR("ZigbeeInput discarding byte %02X"), zigbee_in_byte);
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

#ifndef Z_USE_SOFTWARE_SERIAL
    AddLog_P2(LOG_LEVEL_DEBUG, PSTR("ZIG: Bytes follor_read_metric = %0d"), ZigbeeSerial->getLoopReadMetric());
#endif
		// buffer received, now check integrity
		if (zigbee_buffer->len() != zigbee_frame_len) {
			// Len is not correct, log and reject frame
      AddLog_P2(LOG_LEVEL_INFO, PSTR(D_JSON_ZIGBEEZNPRECEIVED ": received frame of wrong size %s, len %d, expected %d"), hex_char, zigbee_buffer->len(), zigbee_frame_len);
		} else if (0x00 != fcs) {
			// FCS is wrong, packet is corrupt, log and reject frame
      AddLog_P2(LOG_LEVEL_INFO, PSTR(D_JSON_ZIGBEEZNPRECEIVED ": received bad FCS frame %s, %d"), hex_char, fcs);
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
#ifdef Z_USE_SOFTWARE_SERIAL
    ZigbeeSerial = new SoftwareSerial();
    ZigbeeSerial->begin(115200, pin[GPIO_ZIGBEE_RX], pin[GPIO_ZIGBEE_TX], SWSERIAL_8N1, false, 256);    // ZNP is 115200, RTS/CTS (ignored), 8N1
    ZigbeeSerial->enableIntTx(false);
    zigbee_buffer = new SBuffer(ZIGBEE_BUFFER_SIZE);
#else
    ZigbeeSerial = new TasmotaSerial(pin[GPIO_ZIGBEE_RX], pin[GPIO_ZIGBEE_TX], 0, 0, 256);   // set a receive buffer of 256 bytes
    ZigbeeSerial->begin(115200);
    if (ZigbeeSerial->hardwareSerial()) {
      ClaimSerial();
			zigbee_buffer = new PreAllocatedSBuffer(sizeof(serial_in_buffer), serial_in_buffer);
		} else {
			zigbee_buffer = new SBuffer(ZIGBEE_BUFFER_SIZE);
		}
#endif
    zigbee.active = true;
		zigbee.init_phase = true;			// start the state machine
    zigbee.state_machine = true;      // start the state machine
    ZigbeeSerial->flush();
  }
}

/*********************************************************************************************\
 * Commands
\*********************************************************************************************/

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

// Allow or Deny pairing of new Zigbee devices
void CmndZigbeePermitJoin(void)
{
  uint32_t payload = XdrvMailbox.payload;
  if (payload < 0) { payload = 0; }
  if ((99 != payload) && (payload > 1)) { payload = 1; }

  if (1 == payload) {
    ZigbeeGotoLabel(ZIGBEE_LABEL_PERMIT_JOIN_OPEN_60);
  } else if (99 == payload){
    ZigbeeGotoLabel(ZIGBEE_LABEL_PERMIT_JOIN_OPEN_XX);
  } else {
    ZigbeeGotoLabel(ZIGBEE_LABEL_PERMIT_JOIN_CLOSE);
  }
  ResponseCmndDone();
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
					//ZigbeeStateMachine();
          ZigbeeStateMachine_Run();
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
