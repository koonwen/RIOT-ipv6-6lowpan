#include "modules.h"

// Init the ip_buf constant and print address
void *init_and_print_addr(void)
{
    // Number of interfaces
    unsigned n = gnrc_netif_numof();
    DEBUG("Number of interfaces allocated %u\n", n);
    if (n != 1)
    {
        DEBUG("CANNOT HANDLE MORE THAN 1 INTERFACE YET!\n");
        exit(1);
    }

    // Dynamically allocate space for the buffer of ipv6_addr_t pointers
    ipv6_addr_t **ip_addr_set_buf;
    global_ipv6_state.ip_buf = ip_addr_set_buf = (ipv6_addr_t **)
        malloc(sizeof(ipv6_addr_t *) * n);

    gnrc_netif_t *netif = NULL;
    while ((netif = gnrc_netif_iter(netif)))
    {
        ipv6_addr_t *addr_set = (ipv6_addr_t *)malloc(sizeof(ipv6_addr_t) * CONFIG_GNRC_NETIF_IPV6_ADDRS_NUMOF);
        int res = gnrc_netapi_get(netif->pid, NETOPT_IPV6_ADDR, 0, addr_set,
                                  (sizeof(ipv6_addr_t) * CONFIG_GNRC_NETIF_IPV6_ADDRS_NUMOF));
        *ip_addr_set_buf = addr_set;
        ip_addr_set_buf++;
        global_ipv6_state.numof_ips += res / sizeof(ipv6_addr_t);

        if (res < 0)
        {
            continue;
        }
        for (unsigned i = 0; i < (unsigned)(res / sizeof(ipv6_addr_t)); i++)
        {
            char ipv6_addr[IPV6_ADDR_MAX_STR_LEN];

            ipv6_addr_to_str(ipv6_addr, &addr_set[i], IPV6_ADDR_MAX_STR_LEN);
            printf("My address is %s\n", ipv6_addr);
        }
    }
    return;
}

// Pretty print packet header
void print_pkt(gnrc_pktsnip_t *pkt)
{
    ipv6_hdr_t *hdr = gnrc_ipv6_get_header(pkt);
    ipv6_hdr_print(hdr);
    puts("\n");
}

// Pretty print packet queue
void print_pkt_q(gnrc_pktqueue_t **queue)
{
    int counter = 1;
    gnrc_pktqueue_t *curr;
    puts("\n");
    while (curr = gnrc_pktqueue_remove_head(queue))
    {
        printf("Queue service number (%d)\n", counter++);
        print_pkt(curr->pkt);
        gnrc_pktbuf_release(curr->pkt);
    }
}

ipv6_addr_t src(ipv6_mirage_t *state, ipv6_addr_t dst)
{
    return **(state->ip_buf);
}

// Return a buffer of ip addresses
ipv6_addr_t **get_ip(ipv6_mirage_t *state)
{
    return state->ip_buf;
}

int mtu(ipv6_mirage_t *state, ipv6_addr_t dst)
{
    return IPV6_MIN_MTU;
}
