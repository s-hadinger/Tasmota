/*
  xdrv_23_zigbee_constants.ino - zigbee serial support for Sonoff-Tasmota

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




enum class ZnpStatus : uint8_t {
  Success = 0x00,
  Failure = 0x01,
  InvalidParameter = 0x02,
  MemError = 0x03,
  BufferFull = 0x11
};

typedef uint64_t IEEEAddress;
typedef uint16_t ShortAddress;

enum class AddrMode : uint8_t {
  NotPresent = 0,
  Group = 1,
  ShortAddress = 2,
  IEEEAddress = 3,
  Broadcast = 0xFF
};



// Commands in the AF subsystem
enum class AfCommand : uint8_t {
  REGISTER = 0x00,
  DATA_REQUEST = 0x01,
  DATA_REQUEST_EXT = 0x02,
  DATA_REQUEST_SRC_RTG = 0x03,
  INTER_PAN_CTL = 0x10,
  DATA_STORE = 0x11,
  DATA_RETRIEVE = 0x12,
  APSF_CONFIG_SET = 0x13,
  DATA_CONFIRM = 0x80,
  REFLECT_ERROR = 0x83,
  INCOMING_MSG = 0x81,
  INCOMING_MSG_EXT = 0x82
};

// Commands in the ZDO subsystem
enum class ZdoCommand : uint8_t {
  NWK_ADDR_REQ = 0x00,
  IEEE_ADDR_REQ = 0x01,
  NODE_DESC_REQ = 0x02,
  POWER_DESC_REQ = 0x03,
  SIMPLE_DESC_REQ = 0x04,
  ACTIVE_EP_REQ = 0x05,
  MATCH_DESC_REQ = 0x06,
  COMPLEX_DESC_REQ = 0x07,
  USER_DESC_REQ = 0x08,
  DEVICE_ANNCE = 0x0A,
  USER_DESC_SET = 0x0B,
  SERVER_DISC_REQ = 0x0C,
  END_DEVICE_BIND_REQ = 0x20,
  BIND_REQ = 0x21,
  UNBIND_REQ = 0x22,
  SET_LINK_KEY = 0x23,
  REMOVE_LINK_KEY = 0x24,
  GET_LINK_KEY = 0x25,
  MGMT_NWK_DISC_REQ = 0x30,
  MGMT_LQI_REQ = 0x31,
  MGMT_RTQ_REQ = 0x32,
  MGMT_BIND_REQ = 0x33,
  MGMT_LEAVE_REQ = 0x34,
  MGMT_DIRECT_JOIN_REQ = 0x35,
  MGMT_PERMIT_JOIN_REQ = 0x36,
  MGMT_NWK_UPDATE_REQ = 0x37,
  MSG_CB_REGISTER = 0x3E,
  MGS_CB_REMOVE = 0x3F,
  STARTUP_FROM_APP = 0x40,
  AUTO_FIND_DESTINATION = 0x41,
  EXT_REMOVE_GROUP = 0x47,
  EXT_REMOVE_ALL_GROUP = 0x48,
  EXT_FIND_ALL_GROUPS_ENDPOINT = 0x49,
  EXT_FIND_GROUP = 0x4A,
  EXT_ADD_GROUP = 0x4B,
  EXT_COUNT_ALL_GROUPS = 0x4C,
  NWK_ADDR_RSP = 0x80,
  IEEE_ADDR_RSP = 0x81,
  NODE_DESC_RSP = 0x82,
  POWER_DESC_RSP = 0x83,
  SIMPLE_DESC_RSP = 0x84,
  ACTIVE_EP_RSP = 0x85,
  MATCH_DESC_RSP = 0x86,
  COMPLEX_DESC_RSP = 0x87,
  USER_DESC_RSP = 0x88,
  USER_DESC_CONF = 0x89,
  SERVER_DISC_RSP = 0x8A,
  END_DEVICE_BIND_RSP = 0xA0,
  BIND_RSP = 0xA1,
  UNBIND_RSP = 0xA2,
  MGMT_NWK_DISC_RSP = 0xB0,
  MGMT_LQI_RSP = 0xB1,
  MGMT_RTG_RSP = 0xB2,
  MGMT_BIND_RSP = 0xB3,
  MGMT_LEAVE_RSP = 0xB4,
  MGMT_DIRECT_JOIN_RSP = 0xB5,
  MGMT_PERMIT_JOIN_RSP = 0xB6,
  STATE_CHANGE_IND = 0xC0,
  END_DEVICE_ANNCE_IND = 0xC1,
  MATCH_DESC_RSP_SENT = 0xC2,
  STATUS_ERROR_RSP = 0xC3,
  SRC_RTG_IND = 0xC4,
  LEAVE_IND = 0xC9,
  TC_DEV_IND = 0xCA,
  PERMIT_JOIN_IND = 0xCB,
  MSG_CB_INCOMING = 0xFF
};

// Commands in the SAPI subsystem
enum class SapiCommand : uint8_t {
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

// Commands in the UTIL subsystem
enum class UtilCommand : uint8_t {
  GET_DEVICE_INFO = 0x00,
  GET_NV_INFO = 0x01,
  SET_PANID = 0x02,
  SET_CHANNELS = 0x03,
  SET_SECLEVEL = 0x04,
  SET_PRECFGKEY = 0x05,
  CALLBACK_SUB_CMD = 0x06,
  KEY_EVENT = 0x07,
  TIME_ALIVE = 0x09,
  LED_CONTROL = 0x0A,
  TEST_LOOPBACK = 0x10,
  DATA_REQ = 0x11,
  SRC_MATCH_ENABLE = 0x20,
  SRC_MATCH_ADD_ENTRY = 0x21,
  SRC_MATCH_DEL_ENTRY = 0x22,
  SRC_MATCH_CHECK_SRC_ADDR = 0x23,
  SRC_MATCH_ACK_ALL_PENDING = 0x24,
  SRC_MATCH_CHECK_ALL_PENDING = 0x25,
  ADDRMGR_EXT_ADDR_LOOKUP = 0x40,
  ADDRMGR_NWK_ADDR_LOOKUP = 0x41,
  APSME_LINK_KEY_DATA_GET = 0x44,
  APSME_LINK_KEY_NV_ID_GET = 0x45,
  ASSOC_COUNT = 0x48,
  ASSOC_FIND_DEVICE = 0x49,
  ASSOC_GET_WITH_ADDRESS = 0x4A,
  APSME_REQUEST_KEY_CMD = 0x4B,
  ZCL_KEY_EST_INIT_EST = 0x80,
  ZCL_KEY_EST_SIGN = 0x81,
  UTIL_SYNC_REQ = 0xE0,
  ZCL_KEY_ESTABLISH_IND = 0xE1
};

enum class Capability : uint16_t {
  SYS = 0x0001,
  MAC = 0x0002,
  NWK = 0x0004,
  AF = 0x0008,
  ZDO = 0x0010,
  SAPI = 0x0020,
  UTIL = 0x0040,
  DEBUG = 0x0080,
  APP = 0x0100,
  ZOAD = 0x1000
};

enum : uint8_t {
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

#endif // USE_ZIGBEE
