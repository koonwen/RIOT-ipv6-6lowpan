#include "collection.h"

void print_and_set_addr(void)
{
    unsigned n = gnrc_netif_numof();
    DEBUG("Number of interfaces allocated %u\n", n);

    // Return pointer to the first device found
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
            printf("My address is %s\n", ipv6_addr);
        }
    }
    return NULL;
}