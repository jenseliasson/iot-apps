#ifndef __NTPD_H__
#define __NTPD_H__

#include "contiki.h"
#include "contiki-lib.h"
#include "contiki-net.h"

#include <string.h>


#define NTP_EPOCH            (86400U * (365U * 70U + 17U))
#define NTPD_PORT             123

#define UDP_IP_BUF   ((struct uip_udpip_hdr *)&uip_buf[UIP_LLH_LEN])

//NTP Timestamp Format, 64 bits
typedef struct ntp_ts {
  uint32_t seconds;
  uint32_t fractions;
} ntp_ts;

struct ntppacket {
  uint8_t livnmode;
  uint8_t stratum;
  uint8_t poll;
  uint8_t precision;

  uint32_t rootdelay;
  uint32_t rootdispersion;
  uint32_t referenceID;
  //uint8_t padding[12];
  //unsigned long seconds;
  //unsigned long fractions;
  ntp_ts reference;
  ntp_ts origin;
  ntp_ts receive;
  ntp_ts transmit;
};

struct tm {
  int tm_sec;         /* seconds */
  int tm_min;         /* minutes */
  int tm_hour;        /* hours */
  int tm_mday;        /* day of the month */
  int tm_mon;         /* month */
  int tm_year;        /* year */
  int tm_wday;        /* day of the week */
  int tm_yday;        /* day in the year, not used in this implementation yet */
  int tm_isdst;       /* daylight saving time, not used in this implementation yet */
};

struct Date {
  unsigned int year;		// 
  unsigned char month;	        //
  unsigned char day;		//
  unsigned char hour;		//
  unsigned char min;		//
  unsigned char sec;		//
  unsigned char ssec;		//
};

PROCESS_NAME(ntpd_process);

void systime2date(uint32_t n, struct tm *p);

#endif /* __NTPD_H__ */
