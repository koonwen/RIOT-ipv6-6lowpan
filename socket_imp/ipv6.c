#include "msg.h"
#include "error.h"
#include "net/gnrc/ipv6.h"
#include "net/gnrc.h"

void *_event_loop(void *arg)
{
    static msg_t _msg_q[GNRC_IPV6_MSG_QUEUE_SIZE];
    msg_t msg, reply;
    reply.type = GNRC_NETAPI_MSG_TYPE_ACK;
    msg_init_queue(_msg_q, GNRC_IPV6_MSG_QUEUE_SIZE);
    gnrc_pktsnip_t *pkt = NULL;
    struct gnrc_netreg_entry me_reg = GNRC_NETREG_ENTRY_INIT_PID(
        GNRC_NETREG_DEMUX_CTX_ALL,
        thread_getpid());

    gnrc_netreg_register(GNRC_NETTYPE_IPV6, &me_reg);

    while (1)
    {
        msg_receive(&msg);
        switch (msg.type)
        {
        case GNRC_NETAPI_MSG_TYPE_RCV:
            pkt = msg.content.ptr;
            _handle_incoming_pkt(pkt);
            break;
        case GNRC_NETAPI_MSG_TYPE_SND:
            pkt = msg.content.ptr;
            _handle_outgoing_pkt(pkt);
            break;
        case GNRC_NETAPI_MSG_TYPE_SET:
        case GNRC_NETAPI_MSG_TYPE_GET:
            msg_reply(&msg, &reply);
            break;
        default:
            break;
        }
    }

    return NULL;
}