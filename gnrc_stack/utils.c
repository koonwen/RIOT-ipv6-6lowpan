#include "modules.h"

void print_addr()
{
    unsigned n = gnrc_netif_numof();
    DEBUG("Number of interfaces allocated %u\n", n);

    // Return pointer to the first device found
    gnrc_netif_t *my_net_device = gnrc_netif_iter(NULL);

    // Dynamically allocate space and put ipv6_addr_t into the buffer
    ipv6_addr_t *addrs = (ipv6_addr_t *)malloc(sizeof(ipv6_addr_t) * n);
    if (gnrc_netif_ipv6_addrs_get(my_net_device, addrs, sizeof(ipv6_addr_t) * n))
        ipv6_addr_print(addrs);
    else
        printf("No addresses found:(");

    puts("\n");
}