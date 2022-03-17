#include "collection.h"

char udp_thread_stack[THREAD_STACKSIZE_DEFAULT];
char tcp_thread_stack[THREAD_STACKSIZE_DEFAULT];
char ip_raw_thread_stack[THREAD_STACKSIZE_DEFAULT];
#define SOCK_PRIO THREAD_PRIORITY_MAIN

#define MAIN_QUEUE_SIZE (8)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

int main(void)
{
    // print_and_set_addr();

    // uint8_t buf[128];
    // sock_ip_ep_t local = SOCK_IPV6_EP_ANY;
    // sock_ip_t sock;

    // if (sock_ip_create(&sock, &local, NULL, PROTNUM_IPV6, 0) < 0)
    // {
    //     puts("Error creating raw IP sock");
    //     return 1;
    // }

    // while (1)
    // {
    //     sock_ip_ep_t remote;
    //     ssize_t res;

    //     if ((res = sock_ip_recv(&sock, buf, sizeof(buf), SOCK_NO_TIMEOUT,
    //                             &remote)) >= 0)
    //     {
    //         puts("Received a message");
    //         if (sock_ip_send(&sock, buf, res, 0, &remote) < 0)
    //         {
    //             puts("Error sending reply");
    //         }
    //     }
    // }

    // Raw IP socket thread
    // thread_create(ip_raw_sock_thread, THREAD_STACKSIZE_DEFAULT,
    //               SOCK_PRIO - 1, THREAD_CREATE_STACKTEST,
    //               ip_raw_sock_thread, NULL, "raw ip sock thread");

    // // UDP socket thread
    // thread_create(udp_thread_stack, THREAD_STACKSIZE_DEFAULT,
    //               SOCK_PRIO - 1, THREAD_CREATE_STACKTEST,
    //               udp_sock_thread, NULL, "udp sock thread");

    // // TCP socket thread
    // thread_create(tcp_thread_stack, THREAD_STACKSIZE_DEFAULT,
    //               SOCK_PRIO - 1, THREAD_CREATE_STACKTEST,
    //               tcp_sock_thread, NULL, "tcp sock thread");

    // Shell init
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    puts("All up, running the shell now");
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
