#ifndef COLLECTION_H
#define COLLECTION_H

#include <stdio.h>
#include <string.h>

#include "net/gnrc/ipv6.h"
#include "net/ipv6.h"
#include "net/sock/ip.h"

#include "msg.h"
#include "debug.h"
#include "shell.h"
#include "sched.h"

#define ENABLE_DEBUG 1
#define TCP_EVENTLOOP_PRIO (THREAD_PRIORITY_MAIN - 2U)
// ipv6_addr_t **address_buf;

void print_and_set_addr(void);
void *tcp_sock_thread(void *args);
void *udp_sock_thread(void *args);
void *ip_raw_sock_thread(void *args);

#endif