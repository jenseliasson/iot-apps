#ifndef __RD_CLIENT_H__
#define __RD_CLIENT_H__

#include "er-coap-engine.h"

/* definitions */
#define LOCAL_PORT      UIP_HTONS(COAP_DEFAULT_PORT+1)
#define REMOTE_PORT     UIP_HTONS(COAP_DEFAULT_PORT)

#define TOGGLE_INTERVAL 10

PROCESS_NAME(rd_client);

#endif /* __RD_CLIENT_H__ */
