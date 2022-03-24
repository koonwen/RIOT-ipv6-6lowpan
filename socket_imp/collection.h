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

#define ENABLE_DEBUG (1)
#define TCP_EVENTLOOP_PRIO (THREAD_PRIORITY_MAIN - 2)
#define MIN_MTU (IPV6_MIN_MTU)

extern sock_udp_ep_t udp_remote;
extern sock_udp_ep_t udp_local;
int get_mtu(int protocol);
uint16_t getport(sock_udp_ep_t *endpoint);

void print_and_set_addr(void);
void *tcp_sock_thread(void *args);
void *udp_sock_thread(void *args);
void *ip_raw_sock_thread(void *args);

int udp_cmd(int argc, char *argv[]);
int print_local_dets(int argc, char *argv[]);
int print_remote_dets(int argc, char *argv[]);

#endif