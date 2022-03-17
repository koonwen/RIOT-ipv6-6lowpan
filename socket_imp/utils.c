#include "collection.h"

void print_and_set_addr(void)
{
    unsigned n = gnrc_netif_numof();
    DEBUG("Number of interfaces allocated %u\n", n);

    // Dynamically allocate space and put ipv6_addr_t into the buffer
    ipv6_addr_t **addrs = (ipv6_addr_t **)malloc(sizeof(ipv6_addr_t *) * n);

    // Return pointer to the first device found
    gnrc_netif_t *last = NULL;
    ipv6_addr_t **addr_ptr = addrs;
    for (int i = 0; i < n; i++)
    {
        last = gnrc_netif_iter(last);
        ipv6_addr_t *one_addrs = (ipv6_addr_t *)malloc(sizeof(ipv6_addr_t));
        addr_ptr = one_addrs;
        addr_ptr++;
        ipv6_addr_print(one_addrs);
        puts("\n");
        char addr_str[IPV6_ADDR_MAX_STR_LEN];
        ipv6_addr_to_str(*addr_ptr, last, sizeof(addr_str));
    }
    ipv6_addr_t **address_buf = addrs;
    return NULL;
}