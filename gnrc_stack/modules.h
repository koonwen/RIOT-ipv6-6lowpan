#include <stdio.h>

#include "net/gnrc/pktdump.h"
#include "net/gnrc.h"
#include "net/gnrc/ipv6.h"
#include "net/gnrc/udp.h"

#include "debug.h"

#include "shell.h"
#include "msg.h"
#include "thread.h"

#define ENABLE_DEBUG (1)

void *ipv6_event_loop(void *args);
void print_addr(void);