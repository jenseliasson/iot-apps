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
 *      OMA LWM2M (0 - Security) Contiki implementation
 * \author
 *      Jens Eliasson <jens.eliasson@ltu.se>
 */

#include <stdlib.h>
#include <string.h>
#include "rest-engine.h"

#include "oma_lwm2m.h"

static void res_root_delete_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);

static void res_0_0_0_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_0_0_0_post_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_0_0_1_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_0_0_2_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_0_0_3_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_0_0_4_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_0_0_5_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_0_0_11_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);

//LWM2MServerURI
RESOURCE(res_omalwm2m_root,
         "title=\"\";rt=\"\"",
         res_root_delete_handler,
         res_root_delete_handler,
         res_root_delete_handler,
         res_root_delete_handler);

static void
res_root_delete_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  printf(" DELETE /\n");
  REST.set_response_status(response, REST.status.DELETED);
}

//LWM2MServerURI
RESOURCE(res_omalwm2m_0_0LWM2MServerURI,
         "title=\"Device\";rt=\"\"",
         res_0_0_0_get_handler,
         res_0_0_0_post_handler,
         NULL,
         NULL);

static void
res_0_0_0_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const char *len = NULL;
  char message[80]; 
  int length; 

  memset(message, '\0', sizeof(message));
  sprintf(message, "coaps://[%s]:%u", "fdfd::ff", 5683);
  length = strlen(message);
  memcpy(buffer, message, length);

  //REST.set_header_content_type(response, REST.type.APPLICATION_JSON);
  REST.set_header_etag(response, (uint8_t *)&length, 1);
  REST.set_response_payload(response, buffer, length);
}

static void
res_0_0_0_post_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  char message[80]; 

  uint16_t payload_len = 0;
  uint8_t* payload = NULL;
  payload_len = REST.get_request_payload(request, &payload);
  
  if (payload) {
    memcpy(message, payload, payload_len);
    message[payload_len] = 0;
    printf(" payload: %s\n", message);

    if(strncmp(message, "coaps://", strlen("coaps://")) == 0)
    {
      printf("got DTLS target\n");
      REST.set_response_status(response, REST.status.CHANGED);
    } else if(strncmp(message, "coap://", strlen("coap://")) == 0)
    {
      printf("got CoAP target\n");
      REST.set_response_status(response, REST.status.CHANGED);
    } else {
      printf("got invalid target\n");
      REST.set_response_status(response, REST.status.BAD_REQUEST);
    }

  }
}

//BootstrapServer
RESOURCE(res_omalwm2m_0_1BootstrapServer,
         "title=\"Device\";rt=\"\"",
         res_0_0_1_get_handler,
         NULL,
         NULL,
         NULL);

static void
res_0_0_1_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const char *len = NULL;
  char message[80]; 
  int length; 

  memset(message, '\0', sizeof(message));
  sprintf(message, "false");
  length = strlen(message);
  memcpy(buffer, message, length);

  //REST.set_header_content_type(response, REST.type.APPLICATION_JSON);
  REST.set_header_etag(response, (uint8_t *)&length, 1);
  REST.set_response_payload(response, buffer, length);
}

//SecurityMode
RESOURCE(res_omalwm2m_0_2SecurityMode,
         "title=\"Device\";rt=\"\"",
         res_0_0_2_get_handler,
         NULL,
         NULL,
         NULL);

static void
res_0_0_2_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const char *len = NULL;
  char message[80]; 
  int length; 

  memset(message, '\0', sizeof(message));
  sprintf(message, "%d", LWM2M_NoSec);
  length = strlen(message);
  memcpy(buffer, message, length);

  //REST.set_header_content_type(response, REST.type.APPLICATION_JSON);
  REST.set_header_etag(response, (uint8_t *)&length, 1);
  REST.set_response_payload(response, buffer, length);
}

