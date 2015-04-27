/*
 * Copyright (c) 2015, Jens Eliasson, Lulea University of Technology
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is an extension of the Contiki operating system.
 */

/**
 * \file
 *         Resource Directory client
 * \author
 *         Jens Eliasson <jens.eliasson@ltu.se>
 */

#include "contiki.h"
#include "contiki-lib.h"
#include "contiki-net.h"
#include "net/ip/uip.h"
#include "net/ipv6/uip-ds6.h"
#include "net/rpl/rpl.h"

#define DEBUG DEBUG_PRINT
#include "net/ip/uip-debug.h"

#include "rest-engine.h"

#include "rd_client.h"


PROCESS(rd_client, "OMA LWM2M /rd Client");

/* FIXME: The /rd server address is hard-coded for now. Should be obtained from the /bs server or similar */
#define SERVER_NODE(ipaddr)   uip_ip6addr(ipaddr, 0xfdfd, 0, 0, 0, 0, 0, 0, 0xff)

uip_ipaddr_t server_ipaddr;
static struct etimer et;
static int rdstate = 1;

char *service_urls[2] = { "/bs", "/rd"};

char endp[64];

/* This function is will be passed to COAP_BLOCKING_REQUEST() to handle responses. */
void
client_chunk_handler(void *response)
{
  const uint8_t *chunk;
  const char *str=NULL;

  int len = coap_get_header_location_path(response, &str);
  endp[0] = '/';
  memcpy(endp+1, str, len);
  endp[len] = '\0';
  printf("Location-path: %s\n", endp);
  
  len = coap_get_payload(response, &chunk);
  printf("|%.*s", len, (char *)chunk);
}

PROCESS_THREAD(rd_client, ev, data)
{
  PROCESS_BEGIN();

  static coap_packet_t request[1];      /* This way the packet can be treated as pointer as usual. */

  SERVER_NODE(&server_ipaddr);

  printf("/rd-/sd client\n");

  etimer_set(&et, TOGGLE_INTERVAL * CLOCK_SECOND);

  while(1) {
    PROCESS_YIELD();

    if(etimer_expired(&et)) {
      if (rdstate == 0) {
        printf("\nInitiate Bootstrap mechanism\n");
      
        /* prepare request, TID is set by COAP_BLOCKING_REQUEST() */
        coap_init_message(request, COAP_TYPE_CON, COAP_POST, 0);
        coap_set_header_uri_path(request, service_urls[0]);
        coap_set_header_uri_query(request, "?ep=mulle-201");

        PRINT6ADDR(&server_ipaddr);
        PRINTF(" : %u\n", UIP_HTONS(REMOTE_PORT));

        COAP_BLOCKING_REQUEST(&server_ipaddr, REMOTE_PORT, request, client_chunk_handler);
        printf("\n--Done--\n");
        rdstate = 1;
      } else if (rdstate == 1) {
        printf("\nRegister at RD\n");

        /* prepare request, TID is set by COAP_BLOCKING_REQUEST() */
        coap_init_message(request, COAP_TYPE_CON, COAP_POST, 0);
        coap_set_header_uri_path(request, service_urls[1]);

        const char msg[] = "</1/1>,</1/2>,</2/0>,</3/0>,</4/0>"; // get this from oma_lwm2m.c registry
        coap_set_payload(request, (uint8_t *) msg, sizeof(msg) - 1);

        coap_set_header_uri_query(request, "?ep=mulle-201"); //FIXME: the name should come from system config

        PRINT6ADDR(&server_ipaddr);
        //PRINTF(" : %u\n", UIP_HTONS(REMOTE_PORT));

        COAP_BLOCKING_REQUEST(&server_ipaddr, REMOTE_PORT, request, client_chunk_handler);
        printf("\n--Done--\n");
        rdstate = 2;
      } else {
	//printf("Updating RD using %s\n", endp);
	//coap_set_header_uri_path(request, endp);
	//FIXME: updates is to be added
     }
     etimer_reset(&et);

    }
  }

  PROCESS_END();
}
