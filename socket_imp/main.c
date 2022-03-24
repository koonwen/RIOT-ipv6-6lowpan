#include "collection.h"
#include "net/sock.h"

char udp_thread_stack[THREAD_STACKSIZE_DEFAULT];
char tcp_thread_stack[THREAD_STACKSIZE_DEFAULT];
char ip_raw_thread_stack[THREAD_STACKSIZE_DEFAULT];
#define SOCK_PRIO THREAD_PRIORITY_MAIN

#define MAIN_QUEUE_SIZE (8)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

static const shell_command_t shell_commands[] = {
    {"pl", "Print local udp endpoint", print_local_dets},
    {"pr", "Print remote udp endpoint", print_remote_dets},
    {NULL, NULL, NULL}};

// Write a RIOT program to send network packets.
int main(void)
{
    print_and_set_addr();

    // Raw IP socket thread
    thread_create(ip_raw_thread_stack, THREAD_STACKSIZE_DEFAULT,
                  SOCK_PRIO - 1, THREAD_CREATE_STACKTEST,
                  ip_raw_sock_thread, NULL, "raw ip sock thread");

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
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
