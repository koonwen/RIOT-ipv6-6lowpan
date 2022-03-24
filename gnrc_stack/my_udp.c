#include "modules.h"

// UDP not implemented! packets are just logged and dropped
// To add UDP packets to the packet queue, we need to add a mutex on the packet queue

void *udp_event_loop(void *arg)
{
    (void)arg;
    msg_t msg, reply;
    msg_t msg_queue[GNRC_UDP_MSG_QUEUE_SIZE];
    gnrc_netreg_entry_t netreg = GNRC_NETREG_ENTRY_INIT_PID(GNRC_NETREG_DEMUX_CTX_ALL, thread_getpid());
    /* preset reply message */
    reply.type = GNRC_NETAPI_MSG_TYPE_ACK;
    reply.content.value = (uint32_t)-ENOTSUP;
    /* initialize message queue */
    msg_init_queue(msg_queue, GNRC_UDP_MSG_QUEUE_SIZE);
    /* register UPD at netreg */
    gnrc_netreg_register(GNRC_NETTYPE_UDP, &netreg);

    /* dispatch NETAPI messages */
    while (1)
    {
        msg_receive(&msg);
        gnrc_pktsnip_t *pkt = msg.content.ptr;
        switch (msg.type)
        {
        case GNRC_NETAPI_MSG_TYPE_RCV:
            DEBUG("udp: GNRC_NETAPI_MSG_TYPE_RCV\n");
            print_pkt(msg.content.ptr);
            break;
        case GNRC_NETAPI_MSG_TYPE_SND:
            DEBUG("udp: GNRC_NETAPI_MSG_TYPE_SND\n");
            // _send(msg.content.ptr);
            break;
        case GNRC_NETAPI_MSG_TYPE_SET:
        case GNRC_NETAPI_MSG_TYPE_GET:
            msg_reply(&msg, &reply);
            break;
        default:
            DEBUG("udp: received unidentified message\n");
            break;
        }
        gnrc_pktbuf_release(pkt);
    }

    /* never reached */
    return NULL;
}