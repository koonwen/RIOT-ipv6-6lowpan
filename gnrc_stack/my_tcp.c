#include "modules.h"

#define TCP_EVENTLOOP_MSG_QUEUE_SIZE (1 << CONFIG_GNRC_TCP_EVENTLOOP_MSG_QUEUE_SIZE_EXP)

static msg_t _eventloop_msg_queue[TCP_EVENTLOOP_MSG_QUEUE_SIZE];

void *tcp_event_loop(__attribute__((unused)) void *arg)
{
    msg_t msg;
    msg_t reply;

    /* Setup reply message */
    reply.type = GNRC_NETAPI_MSG_TYPE_ACK;
    reply.content.value = (uint32_t)-ENOTSUP;

    /* Init message queue */
    msg_init_queue(_eventloop_msg_queue, TCP_EVENTLOOP_MSG_QUEUE_SIZE);

    /* Register GNRC TCPs handling thread in netreg */
    gnrc_netreg_entry_t entry;
    gnrc_netreg_entry_init_pid(&entry, GNRC_NETREG_DEMUX_CTX_ALL, thread_getpid());
    gnrc_netreg_register(GNRC_NETTYPE_TCP, &entry);

    /* dispatch NETAPI messages */
    while (1)
    {
        msg_receive(&msg);
        gnrc_pktsnip_t *pkt = (gnrc_pktsnip_t *)msg.content.ptr;
        switch (msg.type)
        {
        /* Pass message up the network stack */
        case GNRC_NETAPI_MSG_TYPE_RCV:
            DEBUG("tcp: Received GNRC_NETAPI_MSG_TYPE_RCV.\n");
            print_pkt(pkt);
            gnrc_pktqueue_t *node = (gnrc_pktqueue_t *)malloc(sizeof(gnrc_pktqueue_t));
            node->pkt = pkt;
            gnrc_pktqueue_add(&(global_ipv6_state.incoming_pkt_q), node);
            break;
        /* Pass message down the network stack */
        case GNRC_NETAPI_MSG_TYPE_SND:
            DEBUG("tcp: Received GNRC_NETAPI_MSG_TYPE_SND.\n");
            // _send((gnrc_pktsnip_t *)msg.content.ptr);
            break;

        /* Reply to option set and set messages*/
        case GNRC_NETAPI_MSG_TYPE_SET:
        case GNRC_NETAPI_MSG_TYPE_GET:
            msg_reply(&msg, &reply);
            break;

            // /* Retransmission timer expired: Call FSM with retransmission event */
            // case MSG_TYPE_RETRANSMISSION:
            //     DEBUG("Received MSG_TYPE_RETRANSMISSION.");
            //     // _gnrc_tcp_fsm((gnrc_tcp_tcb_t *)msg.content.ptr,
            //     //               FSM_EVENT_TIMEOUT_RETRANSMIT, NULL, NULL, 0);
            //     break;

            // /* Timewait timer expired: Call FSM with timewait event */
            // case MSG_TYPE_TIMEWAIT:
            //     DEBUG("Received MSG_TYPE_TIMEWAIT.");
            //     // _gnrc_tcp_fsm((gnrc_tcp_tcb_t *)msg.content.ptr,
            //     //               FSM_EVENT_TIMEOUT_TIMEWAIT, NULL, NULL, 0);
            //     break;

            //     /* A connection opening attempt from a TCB in listening mode failed.
            //      * Clear retransmission and re-open for next attempt */
            // case MSG_TYPE_CONNECTION_TIMEOUT:
            //     DEBUG("Received MSG_TYPE_CONNECTION_TIMEOUT.");
            //     // _gnrc_tcp_fsm((gnrc_tcp_tcb_t *)msg.content.ptr,
            //     //               FSM_EVENT_CLEAR_RETRANSMIT, NULL, NULL, 0);
            //     // _gnrc_tcp_fsm((gnrc_tcp_tcb_t *)msg.content.ptr,
            //     //               FSM_EVENT_CALL_OPEN, NULL, NULL, 0);
            //     break;

        default:
            DEBUG("Received unexpected message.");
        }
        // gnrc_pktbuf_release(pkt);
    }
    /* Never reached */
    return NULL;
}