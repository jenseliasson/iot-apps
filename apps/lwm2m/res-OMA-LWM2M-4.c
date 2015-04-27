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
 *      OMA LWM2M (4 - xx) Contiki implementation
 * \author
 *      Jens Eliasson <jens.eliasson@ltu.se>
 */

#include <stdlib.h>
#include <string.h>
#include "rest-engine.h"

static uint8_t error_code = 0, UpdateResult = 0;

static void res_4_0_0_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_4_0_1_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_4_0_2_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_4_0_3_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_4_0_4_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_4_0_5_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_4_0_6_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);


/*
 * A handler function named [resource name]_handler must be implemented for each RESOURCE.
 * A buffer for the response payload is provided through the buffer pointer. Simple resources can ignore
 * preferred_size and offset, but must respect the REST_MAX_CHUNK_SIZE limit for the buffer.
 * If a smaller block size is requested for CoAP, the REST framework automatically splits the data.
 */
RESOURCE(res_omalwm2m_4_0NetworkBearer,
         "title=\"Device\";rt=\"Text\"",
         res_4_0_0_get_handler,
         NULL,
         NULL,
         NULL);


/**
 * \fn
 * \brief /4/0/0 NetworkBearer
 */

static void
res_4_0_0_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const char *len = NULL;
  char tlvmessage[5]; 
  int length = 3; 

  memset(tlvmessage, '\0', sizeof(tlvmessage));
#if 1
  //sprintf(message, "{\"e\":\n {\"n\":\"11/0\",\"v\":\"%u\"}\n}", error_code);
  sprintf(tlvmessage, "%u", 23);
  length = strlen(tlvmessage);
#else
  tlvmessage[0] = 0xC1;
  tlvmessage[1] = 0x00; // resource id
//  tlvmessage[2] = 0x41; 
//  tlvmessage[3] = 0x00;
  tlvmessage[2] = 23; // IEEE 802.15.4
#endif
  memcpy(buffer, tlvmessage, length);

//  REST.set_header_content_type(response, REST.type.APPLICATION_JSON); //application/vnd.oma.lwm2m+tlv
  REST.set_header_etag(response, (uint8_t *)&length, 1);
  REST.set_response_payload(response, buffer, length);
}


//AvailableNetworkBearer
RESOURCE(res_omalwm2m_4_1AvailableNetworkBearer,
         "title=\"UpdateResult\";rt=\"Text\"",
         res_4_0_1_get_handler,
         NULL,
         NULL,
         NULL);

static void
res_4_0_1_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const char *len = NULL;
  char tlvmessage[3]; 
  int length = 3; 

  memset(tlvmessage, '\0', sizeof(tlvmessage));

  tlvmessage[0] = 0xC1;
  tlvmessage[1] = 1; // resource id
  tlvmessage[2] = 23; // 802.15.4

  /*tlvmessage[0] = 0x83;
  tlvmessage[1] = 11; // resource id

  tlvmessage[2] = 41;  doesn't work
  tlvmessage[3] = 0x00;
  tlvmessage[4] = error_code;*/
  
  memcpy(buffer, tlvmessage, length);

  REST.set_header_etag(response, (uint8_t *)&length, 1);
  REST.set_response_payload(response, buffer, length);
}

//RadioSignalStrength
RESOURCE(res_omalwm2m_4_2RadioSignalStrength,
         "title=\"UpdateResult\";rt=\"Text\"",
         res_4_0_2_get_handler,
         NULL,
         NULL,
         NULL);

static void
res_4_0_2_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const char *len = NULL;
  char tlvmessage[5]; 
  int length = 3; 

  memset(tlvmessage, '\0', sizeof(tlvmessage));
#if 1
  //sprintf(message, "{\"e\":\n {\"n\":\"11/0\",\"v\":\"%u\"}\n}", error_code);
  sprintf(tlvmessage, "%u", 0);
  length = strlen(tlvmessage);
#else
  tlvmessage[0] = 0xC1;
  tlvmessage[1] = 0x00; // resource id
//  tlvmessage[2] = 0x41; 
//  tlvmessage[3] = 0x00;
  tlvmessage[2] = 23; // IEEE 802.15.4
#endif
  memcpy(buffer, tlvmessage, length);

//  REST.set_header_content_type(response, REST.type.APPLICATION_JSON); //application/vnd.oma.lwm2m+tlv
  REST.set_header_etag(response, (uint8_t *)&length, 1);
  REST.set_response_payload(response, buffer, length);
}


//LinkQuality
RESOURCE(res_omalwm2m_4_3LinkQuality,
         "title=\"UpdateResult\";rt=\"Text\"",
         res_4_0_3_get_handler,
         NULL,
         NULL,
         NULL);

static void
res_4_0_3_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const char *len = NULL;
  char tlvmessage[5]; 
  int length = 3; 

  memset(tlvmessage, '\0', sizeof(tlvmessage));
#if 1
  //sprintf(message, "{\"e\":\n {\"n\":\"11/0\",\"v\":\"%u\"}\n}", error_code);
  sprintf(tlvmessage, "%u", 255);
  length = strlen(tlvmessage);
#else
  tlvmessage[0] = 0xC1;
  tlvmessage[1] = 0x00; // resource id
//  tlvmessage[2] = 0x41; 
//  tlvmessage[3] = 0x00;
  tlvmessage[2] = 23; // IEEE 802.15.4
#endif
  memcpy(buffer, tlvmessage, length);

//  REST.set_header_content_type(response, REST.type.APPLICATION_JSON); //application/vnd.oma.lwm2m+tlv
  REST.set_header_etag(response, (uint8_t *)&length, 1);
  REST.set_response_payload(response, buffer, length);
}

//IPAddresses
RESOURCE(res_omalwm2m_4_4IPAddresses,
         "title=\"UpdateResult\";rt=\"\"",
         res_4_0_4_get_handler,
         NULL,
         NULL,
         NULL);

static void
res_4_0_4_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const char *len = NULL;
  char tlvmessage[23]; 
  int length = 23; 

  memset(tlvmessage, '\0', sizeof(tlvmessage));

  tlvmessage[0] = 0x88;
  tlvmessage[1] = 4;
  tlvmessage[2] = 20;

  tlvmessage[3]  = 0x48;
  tlvmessage[4]  = 0;
  tlvmessage[5]  = 7; 

  tlvmessage[6]  = 'f'; 
  tlvmessage[7]  = 'd';
  tlvmessage[8]  = 'f';
  tlvmessage[9]  = 'd';
  tlvmessage[10] = ':'; 
  tlvmessage[11] = ':';
  tlvmessage[12] = '1';

  tlvmessage[13]  = 0x48;
  tlvmessage[14]  = 0;
  tlvmessage[15]  = 7; 

  tlvmessage[16]  = 'f'; 
  tlvmessage[17]  = 'e';
  tlvmessage[18]  = '8';
  tlvmessage[19]  = '0';
  tlvmessage[20] = ':'; 
  tlvmessage[21] = ':';
  tlvmessage[22] = '1';
 
  memcpy(buffer, tlvmessage, length);
  REST.set_header_etag(response, (uint8_t *)&length, 1);
  REST.set_response_payload(response, buffer, length);
}

//RouterIPAddresse
RESOURCE(res_omalwm2m_4_5RouterIPAddresse,
         "title=\"RouterIPAddresse\";rt=\"\"",
         res_4_0_5_get_handler,
         NULL,
         NULL,
         NULL);

static void
res_4_0_5_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const char *len = NULL;
  char tlvmessage[14]; 
  int length = 14; 

  memset(tlvmessage, '\0', sizeof(tlvmessage));

  tlvmessage[0] = 0x88;
  tlvmessage[1] = 5;
  tlvmessage[2] = 11;

  tlvmessage[3]  = 0x48;
  tlvmessage[4]  = 0;
  tlvmessage[5]  = 8; 

  tlvmessage[6]  = 'f'; 
  tlvmessage[7]  = 'd';
  tlvmessage[8]  = 'f';
  tlvmessage[9]  = 'd';
  tlvmessage[10] = ':'; 
  tlvmessage[11] = ':';
  tlvmessage[12] = 'f';
  tlvmessage[13] = 'f';

  memcpy(buffer, tlvmessage, length);
  REST.set_header_etag(response, (uint8_t *)&length, 1);
  REST.set_response_payload(response, buffer, length);
}

//LinkUtilization
RESOURCE(res_omalwm2m_4_6LinkUtilization,
         "title=\"UpdateResult\";rt=\"Text\"",
         res_4_0_6_get_handler,
         NULL,
         NULL,
         NULL);

static void
res_4_0_6_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const char *len = NULL;
  char tlvmessage[5]; 
  int length = 3; 

  memset(tlvmessage, '\0', sizeof(tlvmessage));
#if 1
  //sprintf(message, "{\"e\":\n {\"n\":\"11/0\",\"v\":\"%u\"}\n}", error_code);
  sprintf(tlvmessage, "%u", 10);
  length = strlen(tlvmessage);
#else
  tlvmessage[0] = 0xC1;
  tlvmessage[1] = 0x00; // resource id
//  tlvmessage[2] = 0x41; 
//  tlvmessage[3] = 0x00;
  tlvmessage[2] = 23; // IEEE 802.15.4
#endif
  memcpy(buffer, tlvmessage, length);

//  REST.set_header_content_type(response, REST.type.APPLICATION_JSON); //application/vnd.oma.lwm2m+tlv
  REST.set_header_etag(response, (uint8_t *)&length, 1);
  REST.set_response_payload(response, buffer, length);
}


