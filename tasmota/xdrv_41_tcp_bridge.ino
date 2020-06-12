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
WiFiServer   server_tcp(tcp_port);   // port 8880
WiFiClient   client_tcp1, client_tcp2;
uint8_t      client_next = 1;
uint8_t     *tcp_buf = nullptr;     // data transfer buffer
const size_t tcp_buf_size = 256;     // size of the buffer, above 132 required for efficient XMODEM

#include <TasmotaSerial.h>
TasmotaSerial *TCPSerial = nullptr;
bool TCP_active = false;

const char kTCPCommands[] PROGMEM = "TCP" "|"    // prefix
  "Start" 
  ;

void (* const TCPCommand[])(void) PROGMEM = {
  &CmndTCPStart,
  };

//
// Called at event loop, checks for incoming data from the CC2530
//
void TCPLoop(void)
{
  uint8_t c;
  bool busy;    // did we transfer some data?
  int32_t buf_len;

  if (!TCP_active) return;

  // check for a client

  if (server_tcp.hasClient()) {
    if (!client_tcp1) {
      client_tcp1 = server_tcp.available();
    } else if (!client_tcp2) {
      client_tcp2 = server_tcp.available();
    } else {
      if (client_next++ & 1) {      // if both tcp client are busy, remove alternatively one
        client_tcp1.stop();
        client_tcp1 = server_tcp.available();
      } else {
        client_tcp2.stop();
        client_tcp2 = server_tcp.available();
      }
    }
  }
  if ((!client_tcp1) && (!client_tcp2)) { return; }

  do {
    busy = false;       // exit loop if no data was transferred

    // start reading the UART, this buffer can quickly overflow
    buf_len = 0;
    while ((buf_len < tcp_buf_size) && (TCPSerial->available())) {
      c = TCPSerial->read();
      tcp_buf[buf_len++] = c;
      busy = true;
    }
    if (buf_len > 0) {
      if (client_tcp1) { client_tcp1.write(tcp_buf, buf_len); }
      if (client_tcp2) { client_tcp2.write(tcp_buf, buf_len); }
    }

    // handle data received from TCP
    buf_len = 0;
    while (client_tcp1.available()) {
      c = client_tcp1.read();
      tcp_buf[buf_len++] = c;
      busy = true;
    }
    if (buf_len > 0) {
      TCPSerial->write(tcp_buf, buf_len);
    }
    buf_len = 0;
    while (client_tcp2.available()) {
      c = client_tcp2.read();
      tcp_buf[buf_len++] = c;
      busy = true;
    }
    if (buf_len > 0) {
      TCPSerial->write(tcp_buf, buf_len);
    }

    yield();    // avoid WDT if heavy traffic
  } while (busy);
}

/********************************************************************************************/

/*********************************************************************************************\
 * Commands
\*********************************************************************************************/

//
// Command `ZbConfig`
//
void CmndTCPStart(void) {

  if (PinUsed(GPIO_TCP_RX) && PinUsed(GPIO_TCP_TX)) {
		AddLog_P2(LOG_LEVEL_DEBUG_MORE, PSTR(D_LOG_TCP "GPIOs Rx:%d Tx:%d"), Pin(GPIO_TCP_RX), Pin(GPIO_TCP_TX));
    // if seriallog_level is 0, we allow GPIO 13/15 to switch to Hardware Serial
    tcp_buf = (uint8_t*) malloc(tcp_buf_size);
    if (!tcp_buf) { AddLog_P2(LOG_LEVEL_ERROR, PSTR(D_LOG_TCP "could not allocate buffer")); return; }

    TCPSerial = new TasmotaSerial(Pin(GPIO_TCP_RX), Pin(GPIO_TCP_TX), seriallog_level ? 1 : 2, 0, 256);   // set a receive buffer of 256 bytes
    TCPSerial->begin(115200);
    if (TCPSerial->hardwareSerial()) {
      ClaimSerial();
		}
    TCP_active = true;

    AddLog_P2(LOG_LEVEL_INFO, PSTR(D_LOG_TCP "Starting TCP server on port %d"), tcp_port);
    server_tcp.begin(); // start TCP server
    server_tcp.setNoDelay(true);
    ResponseCmndDone();
  }
  
}

/*********************************************************************************************\
 * Interface
\*********************************************************************************************/

bool Xdrv41(uint8_t function)
{
  bool result = false;

  switch (function) {
    case FUNC_LOOP:
      TCPLoop();
      break;
    // case FUNC_PRE_INIT:
    //   TCPInit();
    //   break;
    case FUNC_COMMAND:
      result = DecodeCommand(kTCPCommands, TCPCommand);
      break;
  }
  return result;
}

#endif // USE_TCP_BRIDGE
