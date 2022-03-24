#include "modules.h"

void *print_ips_handler(void *args)
{
    (void *)args;
    ipv6_addr_t *iter = *(global_ipv6_state.ip_buf);
    for (int i = 0; i < global_ipv6_state.numof_ips; i++)
    {
        char ipv6_addr[IPV6_ADDR_MAX_STR_LEN];
        ipv6_addr_to_str(ipv6_addr, (iter + i), IPV6_ADDR_MAX_STR_LEN);
        printf("ip: %s\n", ipv6_addr);
    }
    return;
}

void *print_pkt_q_handler(void *args)
{
    (void *)args;
    print_pkt_q(&(global_ipv6_state.incoming_pkt_q));
    return NULL;
}