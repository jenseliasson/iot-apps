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
 *      OMA LWM2M 7
 * \author
 *      Jens Eliasson <jens.eliasson@ltu.se>
 */

#include <stdlib.h>
#include <string.h>
#include "rest-engine.h"

#include "oma_lwm2m.h"

#ifdef WITH_OMA_LWM2M

uint32_t lwm2m_706tx_counter = 0, lwm2m_706rx_counter = 0;

static void res_7_0_6_post_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);


//StartOrReset
RESOURCE(res_omalwm2m_7_6StartOrReset,
         "title=\"StartOrReset\";rt=\"\"",
         NULL,
         res_7_0_6_post_handler,
         NULL,
         NULL);

static void
res_7_0_6_post_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  //const char *len = NULL;
  //char message[80]; 
  int length = 12; 

  //memset(message, '\0', sizeof(message));
  //sprintf(message, "StartOrReset");
  //length = strlen(message);
  //memcpy(buffer, message, length);

  /* reset counters */
  lwm2m_706tx_counter = 0;
  lwm2m_706rx_counter = 0;

  //REST.set_header_content_type(response, REST.type.APPLICATION_JSON);
  REST.set_header_etag(response, (uint8_t *)&length, 1); //XXX is this correct or should the etag be copied?
  //REST.set_response_payload(response, buffer, length);
  REST.set_response_status(response, REST.status.CHANGED);
}

#endif
