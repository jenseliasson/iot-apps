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
 *      OMA LWM2M (3 - Device) Contiki implementation
 * \author
 *      Jens Eliasson <jens.eliasson@ltu.se>
 */

#include <stdlib.h>
#include <string.h>
#include "rest-engine.h"

#include "oma_lwm2m.h"


static uint8_t error_code = 0;

/* this set the current time zone */
//#include "ntpd.h"
static int tz = 1;

static void res_3_0_0_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_3_0_1_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_3_0_2_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_3_0_3_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_3_0_4_post_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_3_0_5_post_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_3_0_6_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_3_0_9_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_3_0_10_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_3_0_11_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_3_0_13_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_3_0_14_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);


/*
 * A handler function named [resource name]_handler must be implemented for each RESOURCE.
 * A buffer for the response payload is provided through the buffer pointer. Simple resources can ignore
 * preferred_size and offset, but must respect the REST_MAX_CHUNK_SIZE limit for the buffer.
 * If a smaller block size is requested for CoAP, the REST framework automatically splits the data.
 */

///////////////////////////////////////////////////////////////////////////////

RESOURCE(res_omalwm2m_3_0Manufacturer,
         "title=\"Device\";rt=\"Text\"",
         res_3_0_0_get_handler,
         NULL,
         NULL,
         NULL);

static void
res_3_0_0_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const char *len = NULL;
  char message[80]; 
  int length = 12; 

  memset(message, '\0', sizeof(message));
  sprintf(message, "{\"e\":\n {\"n\":\"0\",\"sv\":\"Eistec AB\"}\n}");
  length = strlen(message);
  memcpy(buffer, message, length);

  REST.set_header_content_type(response, REST.type.APPLICATION_JSON);
  REST.set_header_etag(response, (uint8_t *)&length, 1);
  REST.set_response_payload(response, buffer, length);
}

///////////////////////////////////////////////////////////////////////////////

//Model Number 
RESOURCE(res_omalwm2m_3_1ModelNumber,
         "title=\"Device\";rt=\"Text\"",
         res_3_0_1_get_handler,
         NULL,
         NULL,
         NULL);

static void
res_3_0_1_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const char *len = NULL;
  char message[80]; 
  int length = 12; 

  memset(message, '\0', sizeof(message));
  sprintf(message, "{\"e\":\n {\"n\":\"1\",\"sv\":\"Mulle mk4\"}\n}");
  length = strlen(message);
  memcpy(buffer, message, length);

  REST.set_header_content_type(response, REST.type.APPLICATION_JSON);
  REST.set_header_etag(response, (uint8_t *)&length, 1);
  REST.set_response_payload(response, buffer, length);
}

///////////////////////////////////////////////////////////////////////////////

//Serial Number 
RESOURCE(res_omalwm2m_3_2SerialNumber,
         "title=\"Device\";rt=\"Text\"",
         res_3_0_2_get_handler,
         NULL,
         NULL,
         NULL);

static void
res_3_0_2_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const char *len = NULL;
  char message[80]; 
  int length; 

  memset(message, '\0', sizeof(message));
  sprintf(message, "{\"e\":\n {\"n\":\"2\",\"sv\":\"74625-4645\"}\n}");
  length = strlen(message);
  memcpy(buffer, message, length);

  REST.set_header_content_type(response, REST.type.APPLICATION_JSON);
  REST.set_header_etag(response, (uint8_t *)&length, 1);
  REST.set_response_payload(response, buffer, length);
}

///////////////////////////////////////////////////////////////////////////////

//Firmware Version 
RESOURCE(res_omalwm2m_3_3FirmwareVersion,
         "title=\"Device\";rt=\"Text\"",
         res_3_0_3_get_handler,
         NULL,
         NULL,
         NULL);

static void
res_3_0_3_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const char *len = NULL;
  char message[80]; 
  int length; 

  memset(message, '\0', sizeof(message));
  sprintf(message, "{\"e\":\n {\"n\":\"3\",\"sv\":\"1.1\"}\n}");
  length = strlen(message);
  memcpy(buffer, message, length);

  REST.set_header_content_type(response, REST.type.APPLICATION_JSON);
  REST.set_header_etag(response, (uint8_t *)&length, 1);
  REST.set_response_payload(response, buffer, length);
}

///////////////////////////////////////////////////////////////////////////////

//Reboot
RESOURCE(res_omalwm2m_3_4Reboot,
         "title=\"Device\";rt=\"Text\"",
         NULL,
         res_3_0_4_post_handler,
         NULL,
         NULL);

static void
res_3_0_4_post_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const char *len = NULL;
  char message[80]; 
  int length = 12; 

  memset(message, '\0', sizeof(message));
  sprintf(message, "Reboot");
  length = strlen(message);
  memcpy(buffer, message, length);

  //REST.set_header_content_type(response, REST.type.APPLICATION_JSON);
  REST.set_header_etag(response, (uint8_t *)&length, 1);
  //REST.set_response_payload(response, buffer, length);
  REST.set_response_status(response, REST.status.CHANGED);
}

///////////////////////////////////////////////////////////////////////////////

//Factory Reset
RESOURCE(res_omalwm2m_3_5FactoryReset,
         "title=\"Device\";rt=\"Text\"",
         NULL,
         res_3_0_5_post_handler,
         NULL,
         NULL);

static void
res_3_0_5_post_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const char *len = NULL;
  char message[80]; 
  int length = 12; 

  /* do a system-dependant factiry reset here */
  //SystemFactoryReset();

  memset(message, '\0', sizeof(message));
  sprintf(message, "FactoryReset");
  length = strlen(message);
  memcpy(buffer, message, length);

  //REST.set_header_content_type(response, REST.type.APPLICATION_JSON);
  REST.set_header_etag(response, (uint8_t *)&length, 1);
  //REST.set_response_payload(response, buffer, length);
  REST.set_response_status(response, REST.status.CHANGED);
}

///////////////////////////////////////////////////////////////////////////////

//Available Power Sources
RESOURCE(res_omalwm2m_3_6AvailablePowerSources,
         "title=\"Battery Level\";",
         res_3_0_6_get_handler,
         NULL,
         NULL,
         NULL);

static void
res_3_0_6_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const char *len = NULL;
  char tlvmessage[8]; 
  int length = 8; 

  memset(tlvmessage, '\0', sizeof(tlvmessage));

  tlvmessage[0] = 0x86;
  tlvmessage[1] = 6;

  tlvmessage[2] = 0x41; // 100%
  tlvmessage[3] = 0x00;
  tlvmessage[4] = 1;    // internal battery

  tlvmessage[5] = 0x41;
  tlvmessage[6] = 0x01;
  tlvmessage[7] = 5;   // USB powered
 
  memcpy(buffer, tlvmessage, length);
  REST.set_header_etag(response, (uint8_t *)&length, 1);
  REST.set_response_payload(response, buffer, length);
}

///////////////////////////////////////////////////////////////////////////////

//Battery level
RESOURCE(res_omalwm2m_3_9BatteryLevel,
         "title=\"Battery Level\";",
         res_3_0_9_get_handler,
         NULL,
         NULL,
         NULL);

static void
res_3_0_9_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const char *len = NULL;
  char tlvmessage[5]; 
  int length = 3; 

  memset(tlvmessage, '\0', sizeof(tlvmessage));
#if 1
  //sprintf(message, "{\"e\":\n {\"n\":\"11/0\",\"v\":\"%u\"}\n}", error_code);
  sprintf(tlvmessage, "%u", 4200);
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

///////////////////////////////////////////////////////////////////////////////

//Memory Free
RESOURCE(res_omalwm2m_3_10MemoryFree,
         "title=\"Battery Level\";",
         res_3_0_10_get_handler,
         NULL,
         NULL,
         NULL);

static void
res_3_0_10_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const char *len = NULL;
  char tlvmessage[5]; 
  int length = 3; 

  memset(tlvmessage, '\0', sizeof(tlvmessage));
#if 1
  //sprintf(message, "{\"e\":\n {\"n\":\"11/0\",\"v\":\"%u\"}\n}", error_code);
  sprintf(tlvmessage, "%u", 64);
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

///////////////////////////////////////////////////////////////////////////////

//Error Code 
RESOURCE(res_omalwm2m_3_11ErrorCode,
         "title=\"Device\";rt=\"Text\"",
         res_3_0_11_get_handler,
         NULL,
         NULL,
         NULL);

static void
res_3_0_11_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const char *len = NULL;
  char tlvmessage[3]; 
  int length = 3; 

  memset(tlvmessage, '\0', sizeof(tlvmessage));

  tlvmessage[0] = 0xC1;
  tlvmessage[1] = 11; // resource id
  tlvmessage[2] = error_code;

  /*tlvmessage[0] = 0x83;
  tlvmessage[1] = 11; // resource id

  tlvmessage[2] = 41;  doesn't work
  tlvmessage[3] = 0x00;
  tlvmessage[4] = error_code;*/
  
  memcpy(buffer, tlvmessage, length);

  REST.set_header_etag(response, (uint8_t *)&length, 1);
  REST.set_response_payload(response, buffer, length);
}

///////////////////////////////////////////////////////////////////////////////

//Current Time
RESOURCE(res_omalwm2m_3_13CurrentTime,
         "title=\"Current time:\";rt=\"\"",
         res_3_0_13_get_handler,
         NULL,
         NULL,
         NULL);

static void
res_3_0_13_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
#if 0
 const char *len = NULL;
  char tlvmessage[6]; 
  int length = 6; 

  memset(tlvmessage, '\0', sizeof(tlvmessage));

  tlvmessage[0] = 0xC4;
  tlvmessage[1] = 13; // resource id

  tlvmessage[2] = 0x00; //0x51;
  tlvmessage[3] = 0x82;
  tlvmessage[4] = 0x42;
  tlvmessage[5] = 0x8F;
  
  memcpy(buffer, tlvmessage, length);
#else
  const char *len = NULL;
  char message[80]; 
  int length; 

  memset(message, '\0', sizeof(message));
  //sprintf(message, "%lu", getCurrTime());
  sprintf(message, "%lu", 0);

  length = strlen(message);
  memcpy(buffer, message, length);

  REST.set_header_etag(response, (uint8_t *)&length, 1);
  REST.set_response_payload(response, buffer, length);
#endif

//  REST.set_header_content_type(response, REST.type.APPLICATION_JSON); //application/vnd.oma.lwm2m+tlv
  REST.set_header_etag(response, (uint8_t *)&length, 1);
  REST.set_response_payload(response, buffer, length);
}

///////////////////////////////////////////////////////////////////////////////

//Time Zone
RESOURCE(res_omalwm2m_3_15TimeZone,
         "title=\"Time Zone:\";rt=\"\"",
         res_3_0_14_get_handler,
         NULL,
         NULL,
         NULL);

static void
res_3_0_14_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const char *len = NULL;
  char message[18]; 
  int length; 

  memset(message, '\0', sizeof(message));
  sprintf(message, "%c%u:00", tz<0?'-':'+', tz<0?-tz:tz);
  length = strlen(message);
  memcpy(buffer, message, length);

  REST.set_header_etag(response, (uint8_t *)&length, 1);
  REST.set_response_payload(response, buffer, length);

  REST.set_header_etag(response, (uint8_t *)&length, 1);
  REST.set_response_payload(response, buffer, length);
}
///////////////////////////////////////////////////////////////////////////////

