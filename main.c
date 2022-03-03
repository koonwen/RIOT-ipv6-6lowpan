// #include "gnrc.h"
// #include "net/gnrc/sixlowpan.h"

// int main(void)
// {
//     // 6loWPAN thread
//     kernel_pid_t slowp_thread = gnrc_sixlowpan_init();
//     switch (slowp_thread)
//     {
//     case (EINVAL):
//         break;
//     }
//     printf("Kernel pid is %d", slowp_thread);
//     return 0;
// }

#include <stdio.h>

#include "msg.h"
#include "shell.h"
#include "net/ipv6/addr.h"
#include "net/gnrc.h"
#include "net/gnrc/netif.h"

#define MAIN_QUEUE_SIZE (8)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

static const shell_command_t shell_commands[] = {
    {NULL, NULL, NULL}};

int main(void)
{

    puts("RIOT network stack example application");

    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    /* get interfaces and print their addresses */
    gnrc_netif_t *netif = NULL;
    while ((netif = gnrc_netif_iter(netif)))
    {
        ipv6_addr_t ipv6_addrs[CONFIG_GNRC_NETIF_IPV6_ADDRS_NUMOF];
        int res = gnrc_netapi_get(netif->pid, NETOPT_IPV6_ADDR, 0, ipv6_addrs,
                                  sizeof(ipv6_addrs));

        if (res < 0)
        {
            continue;
        }
        for (unsigned i = 0; i < (unsigned)(res / sizeof(ipv6_addr_t)); i++)
        {
            char ipv6_addr[IPV6_ADDR_MAX_STR_LEN];

            ipv6_addr_to_str(ipv6_addr, &ipv6_addrs[i], IPV6_ADDR_MAX_STR_LEN);
            printf("My address is %s\n\n", ipv6_addr);
        }
    }

    /* main thread exits */
    return 0;
}