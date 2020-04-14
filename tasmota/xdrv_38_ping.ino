/*
  xdrv_38_ping.ino - support for ICMP Ping

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

#ifdef USE_PING

#define XDRV_38                    38

#include "lwip/icmp.h"
#include "lwip/inet_chksum.h"
#include "lwip/raw.h"
#include "lwip/timeouts.h"
#include "os_type.h"
#include "osapi.h"

const char kPingCommands[] PROGMEM =  "|"    // no prefix
  D_CMND_PING
  ;

void (* const PingCommand[])(void) PROGMEM = {
  &CmndPing,
  };

extern "C" {
  
  extern uint32 system_relative_time(uint32 time);
  extern void ets_bzero(void *s, size_t n);

  const uint16_t Ping_ID = 0xAFAF;
  const size_t   Ping_data_size = 32;
  const uint32_t Ping_timeout_ms = 1000;
  const uint32_t Ping_coarse = 1000;

  typedef struct Ping_t {
    uint32      ip;                 // important, the IP must be the first parameter
    Ping_t      *next = nullptr;    // next object in linked list
    uint16_t    count;              //
    uint16_t    total_count;        // total count if packets sent
    uint16_t    timeout_count;      // time-outs (no responses)
    uint32_t    min_time;           // minimum time in ms for a successful response
    uint32_t    max_time;           // maximum time in ms for a successful response
    uint32_t    sum_time;           // cumulated time in ms for all successful responses (used to compute the average)
    uint32_t    ping_sent;
    uint32_t    ping_start;
    uint16_t    sent_count;
    uint16_t    seq_num = 0;
    uint16_t    seqno = 0;          // reject a packet already received
    uint16_t    max_count;
    bool        done;               // indicates the ping campaign is finished
  } Ping_t;

  Ping_t    *ping_head = nullptr;
  struct raw_pcb *t_ping_pcb = nullptr;    // registered with first ping, deregistered after last ping, the same pcb is used for all packets

  // find the ping structure corresponding to the specified IP, or nullptr if not found
  Ping_t ICACHE_FLASH_ATTR * t_ping_find(uint32_t ip) {
    Ping_t *ping = ping_head;
    while (ping != nullptr) {
      if (ping->ip == ip) {
        return ping;
      }
      ping = ping->next;
    }
    return nullptr;
  }

  // we never received the packet, increase the timeout count
  void ICACHE_FLASH_ATTR t_ping_timeout(void* arg) {
    Ping_t *ping = (Ping_t*) arg;
    ping->timeout_count++;
    Serial.printf("t_ping_timeout, %d.%d.%d.%d\n", 
                      ping->ip & 0xFF, (ping->ip >> 8) & 0xFF, (ping->ip >> 16) & 0xFF, ping->ip >> 24);
  }

  /** Prepare a echo ICMP request */
  void ICACHE_FLASH_ATTR t_ping_prepare_echo(struct icmp_echo_hdr *iecho, u16_t len, Ping_t *ping) {
    size_t data_len = len - sizeof(struct icmp_echo_hdr);

    ICMPH_TYPE_SET(iecho, ICMP_ECHO);
    ICMPH_CODE_SET(iecho, 0);
    iecho->chksum = 0;
    iecho->id     = Ping_ID;
    ping->seq_num++;
    if (ping->seq_num == 0x7fff) { ping->seq_num = 0; }

    iecho->seqno  = htons(ping->seq_num);      // TODO

    /* fill the additional data buffer with some data */
    for (uint32_t i = 0; i < data_len; i++) {
      ((char*)iecho)[sizeof(struct icmp_echo_hdr) + i] = (char)i;
    }

    iecho->chksum = inet_chksum(iecho, len);
  }

  void ICACHE_FLASH_ATTR t_ping_send(struct raw_pcb *raw, Ping_t *ping) {
    struct pbuf *p;
    uint16_t ping_size = sizeof(struct icmp_echo_hdr) + Ping_data_size;

    p = pbuf_alloc(PBUF_IP, ping_size, PBUF_RAM);
    if (!p) { return; }
    if ((p->len == p->tot_len) && (p->next == nullptr)) {
      ip_addr_t ping_target;
      struct icmp_echo_hdr *iecho;
      
      ping_target.addr = ping->ip;
      iecho = (struct icmp_echo_hdr *) p->payload;

      t_ping_prepare_echo(iecho, ping_size, ping);
      raw_sendto(raw, p, &ping_target);
      ping->ping_sent = sys_now();    // TODO
    }
    pbuf_free(p);
  }

  // this timer is called every x seconds to send a new packet, whatever happened to the previous packet
  static void ICACHE_FLASH_ATTR ping_coarse_tmr2(void *arg) {
  return;
    Ping_t *ping = (Ping_t*) arg;
    // struct ping_option *ping_opt= NULL;
    // struct ping_resp pingresp;
    ip_addr_t ping_target;

    // LWIP_ASSERT("ping_timeout: no pcb given!", pingmsg != NULL);
    ping_target.addr = ping->ip;
    // ping_opt = ping->ping_opt;
    if (--ping->sent_count != 0){
      ping ->ping_sent = system_get_time();
      t_ping_send(t_ping_pcb, ping);

      sys_timeout(Ping_timeout_ms, t_ping_timeout, ping);
      sys_timeout(Ping_coarse, ping_coarse_tmr2, ping);
    } else {
      uint32 delay = system_relative_time(ping->ping_start);
      delay /= Ping_coarse;
  //		ping_seq_num = 0;
      // if (ping_opt->sent_function == NULL){
      //   os_printf("ping %d, timeout %d, total payload %d bytes, %d ms\n",
      //       pingmsg->max_count, pingmsg->timeout_count, PING_DATA_SIZE*(pingmsg->max_count - pingmsg->timeout_count),delay);
      // } else {
        // os_bzero(&pingresp, sizeof(struct ping_resp));
        // pingresp.total_count = pingmsg->max_count;
        // pingresp.timeout_count = pingmsg->timeout_count;
        // pingresp.total_bytes = PING_DATA_SIZE*(pingmsg->max_count - pingmsg->timeout_count);
        // pingresp.total_time = delay;
        // pingresp.ping_err = 0;
      // }
      sys_untimeout(ping_coarse_tmr2, ping);
      //os_free(ping);

      // TODO
      // sent_function
      ping->total_count = ping->max_count;
      ping->done = true;
      // if (ping_opt->sent_function != NULL)
      //   ping_opt->sent_function(ping_opt,(uint8*)&pingresp);
    }
  }

  /* Ping using the raw ip */
  static uint8_t ICACHE_FLASH_ATTR t_ping_recv(void *arg, struct raw_pcb *pcb, struct pbuf *p, const ip_addr_t *addr) {
    struct icmp_echo_hdr *iecho = NULL;
Serial.printf("t_ping_recv 0\n"); Serial.flush();
    Ping_t *ping = t_ping_find(addr->addr);

    Serial.printf("t_ping_recv, %d.%d.%d.%d\n", 
                      addr->addr & 0xFF, (addr->addr >> 8) & 0xFF, (addr->addr >> 16) & 0xFF, addr->addr >> 24);

    if (nullptr == ping) {
      return 0;   // don't eat the packet and ignore it
      Serial.printf("t_ping_recv ignore\n");
    }

    if (pbuf_header( p, -PBUF_IP_HLEN)==0) {
      iecho = (struct icmp_echo_hdr *)p->payload;

      if ((iecho->id == Ping_ID) && (iecho->seqno == htons(ping->seq_num)) && iecho->type == ICMP_ER) {
        Serial.printf("t_ping_recv hit\n");
        
        if (iecho->seqno != ping->seqno){
          /* do some ping result processing */
          sys_untimeout(t_ping_timeout, ping);
          uint32_t delay = system_relative_time(ping->ping_sent);
          delay /= Ping_coarse;

          ping->sum_time += delay;
          if (delay < ping->min_time) { ping->min_time = delay; }
          if (delay > ping->max_time) { ping->max_time = delay; }

          ping->seqno = iecho->seqno;
        }

        pbuf_free(p);
        return 1; /* eat the packet */
      }
    }

    return 0; /* don't eat the packet */
  }

  // we are going to send a packet, make sure pcb is initialized
  void t_ping_register_pcb(void) {
    if (nullptr == t_ping_pcb) {
      t_ping_pcb = raw_new(IP_PROTO_ICMP);

      raw_recv(t_ping_pcb, t_ping_recv, nullptr);    // we cannot register data structure here as we can only register one
      raw_bind(t_ping_pcb, IP_ADDR_ANY);
    }
  }

  // we have finsihed a ping series, deallocated if no more ongoing
  void t_ping_deregister_pcb(void) {
    if (nullptr == ping_head) {         // deregister only if no ping is flying
      raw_remove(t_ping_pcb);
      t_ping_pcb = nullptr;
    }
  }

  bool t_ping_start(Ping_t *ping) {
    ping->ping_start = system_get_time();
    ping->sent_count = ping->max_count;

    t_ping_register_pcb();
    ping->ping_sent = system_get_time();
    t_ping_send(t_ping_pcb, ping);

    sys_timeout(Ping_timeout_ms, t_ping_timeout, ping);
    sys_timeout(Ping_coarse, ping_coarse_tmr2, ping);
  }

}

// Check if any ping requests is completed, and publish the results
void PingResponsePoll(void) {
  Ping_t *ping = ping_head;
  Ping_t **prev_link = &ping_head;      // previous link pointer (used to remove en entry)

  while (ping != nullptr) {
    if (ping->done) {
      uint32_t success = ping->total_count - ping->timeout_count;
      uint32_t ip = ping->ip;

      // Serial.printf(
      //         "DEBUG ping_sent_cb: ping reply\n"
      //         "\tsuccess_count = %d \n"
      //         "\ttimeout_count = %d \n"
      //         "\tmin_time = %d \n"
      //         "\tmax_time = %d \n"
      //         "\tavg_time = %d \n",
      //         success, ping->timeout_count,
      //         ping->min_time, ping->max_time,
      //         success ? ping->sum_time / success : 0
      // );

      Response_P(PSTR("{\"" D_JSON_PING "\":{\"%d.%d.%d.%d\":{"
                      "\"Reachable\":%s"
                      ",\"Success\":%d"
                      ",\"Timeout\":%d"
                      ",\"MinTime\":%d"
                      ",\"MaxTime\":%d"
                      ",\"AvgTime\":%d"
                      "}}}"),
                      ip & 0xFF, (ip >> 8) & 0xFF, (ip >> 16) & 0xFF, ip >> 24,
                      success ? "true" : "false",
                      success, ping->timeout_count,
                      ping->min_time, ping->max_time,
                      success ? ping->sum_time / success : 0
                      );
      MqttPublishPrefixTopic_P(RESULT_OR_TELE, PSTR(D_JSON_PING));
      XdrvRulesProcess();
      
      *prev_link = ping->next;
      // don't increment prev_link
      ping = ping->next;
      delete ping;          // free memory allocated
    } else {
      prev_link = &ping->next;
      ping = ping->next;
    }
  }
}

void CmndPing(void) {
  uint32_t count = XdrvMailbox.index;
  IPAddress ip;

  RemoveSpace(XdrvMailbox.data);
  if (count > 60) { count = 60; }

  if (WiFi.hostByName(XdrvMailbox.data, ip)) {
    if (t_ping_find(ip)) {
      ResponseCmndChar_P(PSTR("Ping already ongoing for this IP"));
    } else {

      Ping_t *ping = new Ping_t();
      memset(ping, 0, sizeof(Ping_t ));
      ping->min_time = UINT32_MAX;
      ping->max_count = count;
      ping->ip = ip;

      ping->next = ping_head;
      ping_head = ping;         // insert at head

      t_ping_start(ping);
      ResponseCmndDone();
    }
  } else {
    ResponseCmndChar_P(PSTR("Unable to resolve IP address"));
  }
}


/*********************************************************************************************\
 * Interface
\*********************************************************************************************/

bool Xdrv38(uint8_t function)
{
  bool result = false;

  switch (function) {
    case FUNC_EVERY_250_MSECOND:
    PingResponsePoll();   // TODO
    break;
    case FUNC_COMMAND:
    result = DecodeCommand(kPingCommands, PingCommand);
    break;
  }
  return result;
}

#endif // USE_PING