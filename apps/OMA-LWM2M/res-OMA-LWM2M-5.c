/*
 * Copyright (c) 2015, Jens Eliasson
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
 *      OMA LWM2M (5 - xx) Contiki implementation
 * \author
 *      Jens Eliasson <jens.eliasson@ltu.se>
 */

#include <stdlib.h>
#include <string.h>
#include "rest-engine.h"

static uint8_t error_code = 0, UpdateResult = 0;

static void res_5_0_3_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_5_0_5_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
//static void res_5_0_11_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);

/*
 * A handler function named [resource name]_handler must be implemented for each RESOURCE.
 * A buffer for the response payload is provided through the buffer pointer. Simple resources can ignore
 * preferred_size and offset, but must respect the REST_MAX_CHUNK_SIZE limit for the buffer.
 * If a smaller block size is requested for CoAP, the REST framework automatically splits the data.
 */
RESOURCE(res_omalwm2m_5_3State,
         "title=\"Device\";rt=\"Text\"",
         res_5_0_3_get_handler,
         NULL,
         NULL,
         NULL);

static void
res_5_0_3_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const char *len = NULL;
  char message[80]; 
  int length = 12; 

  memset(message, '\0', sizeof(message));
  sprintf(message, "{\"e\":\n {\"n\":\"3\",\"sv\":\"0\"}\n}");
  length = strlen(message);
  memcpy(buffer, message, length);

  REST.set_header_content_type(response, REST.type.APPLICATION_JSON);
  REST.set_header_etag(response, (uint8_t *)&length, 1);
  REST.set_response_payload(response, buffer, length);
}


//Update Result
RESOURCE(res_omalwm2m_5_5UpdateResult,
         "title=\"UpdateResult\";rt=\"Text\"",
         res_5_0_5_get_handler,
         NULL,
         NULL,
         NULL);

static void
res_5_0_5_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const char *len = NULL;
  char message[80]; 
  int length = 12; 

  memset(message, '\0', sizeof(message));
  sprintf(message, "{\"e\":\n {\"n\":\"5\",\"sv\":\"%u\"}\n}", UpdateResult);
  length = strlen(message);
  memcpy(buffer, message, length);

  REST.set_header_content_type(response, REST.type.APPLICATION_JSON);
  REST.set_header_etag(response, (uint8_t *)&length, 1);
  REST.set_response_payload(response, buffer, length);
}

