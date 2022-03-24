#include "net/sock/udp.h"
#include "collection.h"

static uint8_t buf[128];
sock_udp_ep_t remote;
sock_udp_ep_t local = SOCK_IPV6_EP_ANY;

void *udp_sock_thread(void *arg)
{
    sock_udp_t sock;

    local.port = 12345;

    if (sock_udp_create(&sock, &local, NULL, 0) < 0)
    {
        puts("Error creating UDP sock");
        return 1;
    }
    puts("UDP Listening on port 12345");

    while (1)
    {
        ssize_t res;

        if ((res = sock_udp_recv(&sock, buf, sizeof(buf), SOCK_NO_TIMEOUT,
                                 &remote)) >= 0)
        {
            puts("\nReceived a message from: ");
            ipv6_addr_print(&(remote.addr));
            puts("\n\n");

            if (sock_udp_send(&sock, buf, res, &remote) < 0)
            {
                puts("Error sending reply");
            }
        }
    }

    return NULL;
}

int udp_cmd(int argc, char *argv[])
{
    puts("\n\n");
    ipv6_addr_print(&(remote.addr));
    puts("\n\n");
}

uint16_t getport(sock_udp_ep_t *endpoint)
{
    return endpoint->port;
}

int print_local_dets(int argc, char *argv[])
{
    printf("Local endpoint: \nfamily: %d\naddr: ", local.family);
    ipv6_addr_print(&(local.addr));
    printf("\nnetif: %d\nport: %d\n", local.netif, local.port);
    return 0;
}

int print_remote_dets(int argc, char *argv[])
{
    printf("Remote endpoint: \nfamily: %d\naddr: ", remote.family);
    ipv6_addr_print(&(remote.addr));
    printf("\nnetif: %d\nport: %d\n", remote.netif, remote.port);
    netif_t *mynetif = netif_get_by_id(remote.netif);
    printf("INTERFACES NUMOF = %d\n", gnrc_netif_numof());
    printf("IPV6_MIN_MTU = %d\n", MIN_MTU);
    return 0;
}