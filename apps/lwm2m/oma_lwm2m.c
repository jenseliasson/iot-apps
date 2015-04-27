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
 *      OMA LWM2M Contiki implementation
 * \author
 *      Jens Eliasson <jens.eliasson@ltu.se>
 */

#include <stdlib.h>
#include <string.h>
#include "rest-engine.h"

#include "oma_lwm2m.h"

extern resource_t res_omalwm2m_0_0LWM2MServerURI;

extern resource_t
  res_omalwm2m_root,
  res_omalwm2m_3_0Manufacturer, res_omalwm2m_3_1ModelNumber,  res_omalwm2m_3_11ErrorCode, res_time, 
  res_omalwm2m_3_2SerialNumber, res_omalwm2m_3_3FirmwareVersion, res_omalwm2m_3_4Reboot, res_omalwm2m_3_5FactoryReset, 
  res_omalwm2m_3_6AvailablePowerSources, res_omalwm2m_3_9BatteryLevel, res_omalwm2m_3_10MemoryFree, res_omalwm2m_3_13CurrentTime,
  res_omalwm2m_3_15TimeZone;

extern resource_t res_omalwm2m_4_0NetworkBearer, res_omalwm2m_4_1AvailableNetworkBearer, res_omalwm2m_4_2RadioSignalStrength,
                res_omalwm2m_4_3LinkQuality, res_omalwm2m_4_4IPAddresses, res_omalwm2m_4_5RouterIPAddresse, res_omalwm2m_4_6LinkUtilization;
extern resource_t res_omalwm2m_5_3State, res_omalwm2m_5_5UpdateResult;

extern resource_t res_omalwm2m_7_6StartOrReset;

extern uint32_t lwm2m_706tx_counter, lwm2m_706rx_counter;

char lwm2m_server[64];

/**
 * \fn int oma_l2m2m_init(void)
 */
int oma_lwm2m_init(void)
{

//  sprintf(lwm2m_server, "%s", )

  //rest_activate_resource(&res_omalwm2m_root, "root");

  /* initialize Security */
  //rest_activate_resource(&res_omalwm2m_0_0LWM2MServerURI, "0/0/0");

  /* initialize */
  rest_activate_resource(&res_omalwm2m_3_0Manufacturer, "3/0/0");
  rest_activate_resource(&res_omalwm2m_3_1ModelNumber, "3/0/1");
  rest_activate_resource(&res_omalwm2m_3_2SerialNumber, "3/0/2");
  rest_activate_resource(&res_omalwm2m_3_3FirmwareVersion, "3/0/3");
  rest_activate_resource(&res_omalwm2m_3_4Reboot, "3/0/4");
  rest_activate_resource(&res_omalwm2m_3_5FactoryReset, "3/0/5");
  rest_activate_resource(&res_omalwm2m_3_6AvailablePowerSources, "3/0/6");
  rest_activate_resource(&res_omalwm2m_3_9BatteryLevel, "3/0/9");
  rest_activate_resource(&res_omalwm2m_3_10MemoryFree, "3/0/10");
  rest_activate_resource(&res_omalwm2m_3_11ErrorCode, "3/0/11");
  rest_activate_resource(&res_omalwm2m_3_13CurrentTime, "3/0/13");
  rest_activate_resource(&res_omalwm2m_3_15TimeZone, "3/0/15");
  
  /* initialize */
  rest_activate_resource(&res_omalwm2m_4_0NetworkBearer, "4/0/0");
  rest_activate_resource(&res_omalwm2m_4_1AvailableNetworkBearer, "4/0/1");
  rest_activate_resource(&res_omalwm2m_4_2RadioSignalStrength, "4/0/2");
  rest_activate_resource(&res_omalwm2m_4_3LinkQuality, "4/0/3");
  rest_activate_resource(&res_omalwm2m_4_4IPAddresses, "4/0/4");
  rest_activate_resource(&res_omalwm2m_4_5RouterIPAddresse, "4/0/5");
  rest_activate_resource(&res_omalwm2m_4_6LinkUtilization, "4/0/6");

  /* initialize */
  rest_activate_resource(&res_omalwm2m_5_3State, "5/0/3");
  rest_activate_resource(&res_omalwm2m_5_5UpdateResult, "5/0/5");

  /* initialize */
  rest_activate_resource(&res_omalwm2m_7_6StartOrReset, "7/0/6");
}

