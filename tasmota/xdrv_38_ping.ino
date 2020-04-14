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



// std::vector<Ping_t*>    pings = {};


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
    struct raw_pcb *pcb;            // pcb structure for network API
    uint16_t    count;              //
    // ping_recv_function recv_function;
    // ping_sent_function sent_function;
    //ping_option opt;                // extend the ping_option structure with internal values
    uint16_t    total_count;        // total count if packets sent
    uint16_t    timeout_count;      // time-outs (no responses)
    uint32_t    min_time;           // minimum time in ms for a successful response
    uint32_t    max_time;           // maximum time in ms for a successful response
    uint32_t    sum_time;           // cumulated time in ms for all successful responses (used to compute the average)
    uint32_t    ping_sent;
    uint32_t    ping_start;
    uint16_t    sent_count;
    uint16_t    seq_num = 0;
    uint16_t    max_count;
    bool        done;               // indicates the ping campaign is finished
  } Ping_t;

  Ping_t    *ping_head = nullptr;

  // find the ping structure corresponding to the specified IP, or nullptr if not found
  Ping_t ICACHE_FLASH_ATTR * find_ping(uint32_t ip) {
    Ping_t *ping = ping_head;
    while (ping != nullptr) {
      if (ping->ip == ip) {
        return ping;
      }
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
      t_ping_send(ping->pcb, ping);

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
      raw_remove(ping->pcb);
      os_free(ping);

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
    static u16_t seqno = 0;
    Ping_t *ping = (Ping_t*) arg;
    //struct ping_msg *pingmsg = (struct ping_msg*)arg;

Serial.printf("t_ping_recv, %d.%d.%d.%d\n", 
                      addr->addr & 0xFF, (addr->addr >> 8) & 0xFF, (addr->addr >> 16) & 0xFF, addr->addr >> 24);

    if (pbuf_header( p, -PBUF_IP_HLEN)==0) {
      iecho = (struct icmp_echo_hdr *)p->payload;

      //if ((iecho->id == Ping_ID) && (iecho->seqno == htons(tping_seq_num)) && iecho->type == ICMP_ER) {  // TODO
      if ((iecho->id == Ping_ID) && (iecho->type == ICMP_ER)) {
      // LWIP_DEBUGF( PING_DEBUG, ("ping: recv "));
      // ip_addr_debug_print(PING_DEBUG, addr);
      // LWIP_DEBUGF( PING_DEBUG, (" %"U32_F" ms\n", (sys_now()-ping_time)));
      if (iecho->seqno != seqno){
        /* do some ping result processing */
        struct ip_hdr *iphdr = NULL;
        char ipaddrstr[16];
        ip_addr_t source_ip;
        sys_untimeout(t_ping_timeout, ping);
        // memset(&source_ip, 0, sizeof(ip_addr_t));
        // memset((ipaddrstr, 0, sizeof(ipaddrstr)));
        os_bzero(&source_ip, sizeof(ip_addr_t));
        os_bzero(ipaddrstr, sizeof(ipaddrstr));
        uint32_t delay = system_relative_time(ping->ping_sent);
        delay /= Ping_coarse;
        iphdr = (struct ip_hdr*)((u8*)iecho - PBUF_IP_HLEN);
        source_ip.addr = iphdr->src.addr;
        ipaddr_ntoa_r(&source_ip,ipaddrstr, sizeof(ipaddrstr));

        // TODO New

        ping->sum_time += delay;
        if (delay < ping->min_time) { ping->min_time = delay; }
        if (delay > ping->max_time) { ping->max_time = delay; }
        // if (p_resp->ping_err >= 0) {
        //   uint32_t resp_time = p_resp->resp_time;
        //   ping->sum_time += resp_time;
        //   if (resp_time < ping->min_time) { ping->min_time = resp_time; }
        //   if (resp_time > ping->max_time) { ping->max_time = resp_time; }
        // }

        // if (pingmsg->ping_opt->recv_function == NULL){
        //   os_printf("recv %s: byte = %d, time = %d ms, seq = %d\n",ipaddrstr, PING_DATA_SIZE, delay, ntohs(iecho->seqno));
        // } else {
        //   struct ping_resp pingresp;
        //   os_bzero(&pingresp, sizeof(struct ping_resp));
        //   pingresp.bytes = PING_DATA_SIZE;
        //   pingresp.resp_time = delay;
        //   pingresp.seqno = ntohs(iecho->seqno);
        //   pingresp.ping_err = 0;
        //   pingmsg->ping_opt->recv_function(pingmsg->ping_opt,(void*) &pingresp);
        // }
        seqno = iecho->seqno;
      }

        //PING_RESULT(1);
        pbuf_free(p);
        return 1; /* eat the packet */
      }
  //    } else if(iecho->type == ICMP_ECHO){
  //        struct pbuf *q = NULL;
  //        os_printf("receive ping request:seq=%d\n", ntohs(iecho->seqno));
  //        q = pbuf_alloc(PBUF_IP, (u16_t)p->tot_len, PBUF_RAM);
  //        if (q!=NULL) {
  //            pbuf_copy(q, p);
  //            iecho = (struct icmp_echo_hdr *)q->payload;
  //            ping_prepare_er(iecho, q->tot_len);
  //            raw_sendto(pcb, q, addr);
  //            pbuf_free(q);
  //        }
  //        pbuf_free(p);
  //        return 1;
  //    }
    }

    return 0; /* don't eat the packet */
  }

  bool t_ping_start(Ping_t *ping) {
    ping->ping_start = system_get_time();
    ping->sent_count = ping->max_count;

    ping->pcb = raw_new(IP_PROTO_ICMP);
    //LWIP_ASSERT("ping_pcb != NULL", pingmsg->ping_pcb != NULL);

    raw_recv(ping->pcb, t_ping_recv, ping);
    raw_bind(ping->pcb, IP_ADDR_ANY);

    ping->ping_sent = system_get_time();
    t_ping_send(ping->pcb, ping);

    sys_timeout(Ping_timeout_ms, t_ping_timeout, ping);
    sys_timeout(Ping_coarse, ping_coarse_tmr2, ping);
  }

  // callbacks for ping

  // called after a ping response is received or time-out
  // void ICACHE_RAM_ATTR ping_recv_cb(Ping_t *ping, struct ping_resp *p_resp) {
  //   // If successful
  //   if (p_resp->ping_err >= 0) {
  //     uint32_t resp_time = p_resp->resp_time;
  //     ping->sum_time += resp_time;
  //     if (resp_time < ping->min_time) { ping->min_time = resp_time; }
  //     if (resp_time > ping->max_time) { ping->max_time = resp_time; }
  //   }
  // }

  // // called after the ping campaign is finished
  // void ICACHE_RAM_ATTR ping_sent_cb(Ping_t *ping, struct ping_resp *p_resp) {
  //   // copy counters to build the MQTT response
  //   ping->total_count = p_resp->total_count;
  //   ping->timeout_count = p_resp->timeout_count;
  //   ping->done = true;
  // }
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
    Ping_t *ping = new Ping_t();
    memset(ping, 0, sizeof(Ping_t ));
    ping->min_time = UINT32_MAX;
    ping->max_count = count;
    ping->ip = ip;

    ping->next = ping_head;
    ping_head = ping;         // insert at head

    t_ping_start(ping);
    ResponseCmndDone();
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
    PingResponsePoll();
    break;
    case FUNC_COMMAND:
    result = DecodeCommand(kPingCommands, PingCommand);
    break;
  }
  return result;
}

#endif // USE_PING