#include <stdio.h>
#include <string.h>

#include "net/gnrc/ipv6/hdr.h"
#include "net/gnrc/pktdump.h"
#include "net/gnrc.h"
#include "net/gnrc/udp.h"
#include "net/gnrc/tcp.h"
#include "net/ipv6.h"
#include "net/gnrc/pktqueue.h"

#include "debug.h"

#include "shell.h"
#include "msg.h"
#include "thread.h"

#define ENABLE_DEBUG (1)

typedef struct ipv6_mirage
{
    int numof_ips;
    const ipv6_addr_t **ip_buf;
    // Need to add a mutex on these queues!!
    gnrc_pktqueue_t *incoming_pkt_q;
    gnrc_pktqueue_t *outgoing_pkt_q;
} ipv6_mirage_t;

extern ipv6_mirage_t global_ipv6_state;

// Event loops
void *udp_event_loop(void *args);
void *tcp_event_loop(void *args);

// General utils
void print_pkt(gnrc_pktsnip_t *pkt);
void *init_and_print_addr(void);

// Shell command handlers
void *print_pkt_q_handler(void *args);
void *print_ips_handler(void *args);

// For bindings
// Implemented
ipv6_addr_t src(ipv6_mirage_t *state, ipv6_addr_t dst);
ipv6_addr_t **get_ip(ipv6_mirage_t *state);
int mtu(ipv6_mirage_t *state, ipv6_addr_t dst);

// TODO
// Implement the C-bindings (TCP)
// Work on event-loop (TCP)

// TODO
// int diconnect(ipv6_mirage_t global_state);
// void input(void(*tcp_cb(void *args)), void(*udp_cb(void *args)));
// void write(void *payload);
// void pseudoheader(ipv6_mirage_t global_state,
//                   ipv6_addr_t ipaddr,
//                   int protocol, int length);
