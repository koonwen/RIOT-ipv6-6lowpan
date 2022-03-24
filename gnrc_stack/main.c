#include "modules.h"

char udp_thread_stack[GNRC_UDP_STACK_SIZE];
char tcp_thread_stack[THREAD_STACKSIZE_DEFAULT];
#define GNRC_TCP_PRIO (GNRC_UDP_PRIO)

#define MAIN_QUEUE_SIZE (8)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

ipv6_mirage_t global_ipv6_state;
shell_command_t shell_commands[] =
    {{"print_q", "print the outgoing pkt queue, removing nodes and freeing space", print_pkt_q_handler},
     {"print_ips", "print all the ips related to this interface", print_ips_handler},
     {NULL, NULL, NULL}};

int main(void)
{
    thread_create(udp_thread_stack, sizeof(udp_thread_stack),
                  GNRC_UDP_PRIO, THREAD_CREATE_STACKTEST,
                  udp_event_loop, NULL, "my_udp_thread");

    thread_create(tcp_thread_stack, sizeof(tcp_thread_stack),
                  GNRC_TCP_PRIO, THREAD_CREATE_STACKTEST,
                  tcp_event_loop, NULL, "my_tcp_thread");

    /* we need a message queue for the thread running the shell in order to
     * receive potentially fast incoming networking packets */
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);
    puts("RIOT network stack example application");
    init_and_print_addr();

    /* start shell */
    puts("All up, running the shell now");
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    /* should be never reached */
    return 0;
}