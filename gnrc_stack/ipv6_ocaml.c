#include "modules.h"

#define Q_SZ (GNRC_IPV6_MSG_QUEUE_SIZE)

typedef struct
{
    int *ip_addr;
    char *ip_buf;
} ipv6_t;

ipv6_t NET_EVENT_QUEUE[Q_SZ];

void *ipv6_event_loop(void *arg)
{
    // Obligatory message queue required to register a thread
    static msg_t _msg_q[Q_SZ];
    msg_init_queue(_msg_q, Q_SZ);

    gnrc_pktsnip_t *pkt = NULL;

    // Register the thread to the registry
    gnrc_netreg_init();
    struct gnrc_netreg_entry me_reg =
        GNRC_NETREG_ENTRY_INIT_PID(GNRC_NETREG_DEMUX_CTX_ALL, thread_getpid());

    gnrc_netreg_register(GNRC_NETTYPE_IPV6, &me_reg);

    // This entire interface is what we want to expose in our ocaml program
    // What we can do is have a global state somewhere here that stores packets and get's them ready to be pulled in by the C_stubs

    // To store messages
    msg_t msg;

    while (1)
    {
        msg_receive(&msg);
        switch (msg.type)
        {
        case GNRC_NETAPI_MSG_TYPE_RCV:
            pkt = msg.content.ptr;
            DEBUG("myipv6: GNRC_NETAPI_MSG_TYPE_RCV\n");
            _recieve(pkt);
            break;
        case GNRC_NETAPI_MSG_TYPE_SND:
            pkt = msg.content.ptr;
            DEBUG("myipv6: GNRC_NETAPI_MSG_TYPE_SND\n");
            break;
        default:
            exit(1);
        }
    }

    return NULL;
}

void _recieve(gnrc_pktsnip_t *pkt)
{
    ipv6_hdr_t *hdr = gnrc_ipv6_get_header(pkt);
    ipv6_hdr_print(hdr);
    gnrc_netif_t *netif = gnrc_netif_iter(NULL);
    // gnrc_icmpv6_demux(netif, pkt);
}
// int *get_ip(void)
// {
//     return 0;
// }

// void *tcp_listen(void *args)
// {
// }

// #include "modules.h"
// #define Q_SZ (8)

// void *udp_event_loop(void *arg)
// {
//     (void)arg;
//     msg_t msg, reply;
//     msg_t msg_queue[GNRC_UDP_MSG_QUEUE_SIZE];

//     reply.type = GNRC_NETAPI_MSG_TYPE_ACK;
//     reply.content.value = -ENOTSUP;
//     msg_init_queue(msg_queue, Q_SZ);
//     gnrc_pktsnip_t *pkt = NULL;
//     // DEMUX_ctx is the port number!
//     struct gnrc_netreg_entry me_reg =
//         GNRC_NETREG_ENTRY_INIT_PID(.demux_ctx = 80, thread_getpid());
//     gnrc_netreg_register(GNRC_NETTYPE_UDP, &me_reg);

//     while (1)
//     {
//         msg_receive(&msg);
//         switch (msg.type)
//         {
//         case GNRC_NETAPI_MSG_TYPE_RCV:
//             DEBUG("Received!\n");
//             pkt = msg.content.ptr;
//             break;
//         case GNRC_NETAPI_MSG_TYPE_SND:
//             DEBUG("Sending!\n");
//             pkt = msg.content.ptr;
//             break;
//         case GNRC_NETAPI_MSG_TYPE_SET:
//         case GNRC_NETAPI_MSG_TYPE_GET:
//             msg_reply(&msg, &reply);
//             break;
//         default:
//             break;
//         }
//     }

//     return NULL;
// }