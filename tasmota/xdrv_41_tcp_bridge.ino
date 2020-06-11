/*
  xdrv_41_tcp_bridge.ino - TCP to serial bridge

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

#ifdef USE_TCP_BRIDGE

#define XDRV_41                    41

const uint16_t tcp_port = 8880;
WiFiServer server_tcp(tcp_port);   // port 8880
WiFiClient client_tcp;

#include <TasmotaSerial.h>
TasmotaSerial *TCPSerial = nullptr;
bool TCP_active = false;

const char kZbCommands[] PROGMEM = "TCP" "|"    // prefix
  "Start" 
  ;

void (* const ZigbeeCommand[])(void) PROGMEM = {
  &CmndTCPStart,
  };

//
// Called at event loop, checks for incoming data from the CC2530
//
void TCPLoop(void)
{
  uint8_t c;

  if (!TCP_active) return;
  // check for a client

  if (server_tcp.hasClient()) {
    if (client_tcp) {
      client_tcp.stop();
    }
    client_tcp = server_tcp.available();
  }

  if (client_tcp) {
    while (client_tcp.available()) {
      c = client_tcp.read();
      TCPSerial->write(c);
    }
  }

  while (TCPSerial->available()) {
    c = TCPSerial->read();
    if (client_tcp) {
      client_tcp.write(c);
    }
  }
}

/********************************************************************************************/

// Initialize internal structures
void TCPInit(void)
{
  if (PinUsed(GPIO_TCP_RX) && PinUsed(GPIO_TCP_TX)) {
		AddLog_P2(LOG_LEVEL_DEBUG_MORE, PSTR(D_LOG_TCP "GPIOs Rx:%d Tx:%d"), Pin(GPIO_TCP_RX), Pin(GPIO_TCP_TX));
    // if seriallog_level is 0, we allow GPIO 13/15 to switch to Hardware Serial
    TCPSerial = new TasmotaSerial(Pin(GPIO_TCP_RX), Pin(GPIO_TCP_TX), seriallog_level ? 1 : 2, 0, 256);   // set a receive buffer of 256 bytes
    TCPSerial->begin(115200);
    if (TCPSerial->hardwareSerial()) {
      ClaimSerial();
      // uint32_t aligned_buffer = ((uint32_t)serial_in_buffer + 3) & ~3;
			// zigbee_buffer = new PreAllocatedSBuffer(sizeof(serial_in_buffer) - 3, (char*) aligned_buffer);
		} else {
// AddLog_P2(LOG_LEVEL_INFO, PSTR("ZigbeeInit Mem2 = %d"), ESP_getFreeHeap());
			// zigbee_buffer = new SBuffer(ZIGBEE_BUFFER_SIZE);
// AddLog_P2(LOG_LEVEL_INFO, PSTR("ZigbeeInit Mem3 = %d"), ESP_getFreeHeap());
		}
    TCP_active = true;
  }
}

/*********************************************************************************************\
 * Commands
\*********************************************************************************************/

//
// Command `ZbConfig`
//
void CmndTCPStart(void) {
  AddLog_P2(LOG_LEVEL_INFO, PSTR(D_LOG_TCP "Starting TCP server on port %d"), tcp_port);
  server_tcp.begin(); // start TCP server
  server_tcp.setNoDelay(true);
  ResponseCmndDone();
}

/*********************************************************************************************\
 * Interface
\*********************************************************************************************/

bool Xdrv41(uint8_t function)
{
  bool result = false;

  switch (function) {
    case FUNC_LOOP:
      if (TCPSerial) { TCPLoop(); }
      break;
    case FUNC_PRE_INIT:
      TCPInit();
      break;
    case FUNC_COMMAND:
      result = DecodeCommand(kZbCommands, ZigbeeCommand);
      break;
  }
  return result;
}

#endif // USE_TCP_BRIDGE
