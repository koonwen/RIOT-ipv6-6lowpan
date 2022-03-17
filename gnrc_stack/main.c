#include "modules.h"

char ipv6_thread_stack[GNRC_IPV6_STACK_SIZE];

#define MAIN_QUEUE_SIZE (8)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

int main(void)
{
    thread_create(ipv6_thread_stack, sizeof(ipv6_thread_stack),
                  GNRC_IPV6_PRIO, THREAD_CREATE_STACKTEST,
                  ipv6_event_loop, NULL, "my_ipv6_thread");

    /* we need a message queue for the thread running the shell in order to
     * receive potentially fast incoming networking packets */
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);
    puts("RIOT network stack example application");
    print_addr();
    // DEBUG("Num of entries %d\n", gnrc_netreg_num(gnrc_nettype_from_protnum(PROTNUM_UDP), 80));
    gnrc_ipv6_init();

    /* start shell */
    puts("All up, running the shell now");
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

    /* should be never reached */
    return 0;
}