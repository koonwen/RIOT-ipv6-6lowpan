#include "collection.h"
#include "net/gnrc/pkt.h"
#include "net/udp.h"

uint8_t buf[128];

void *ip_raw_sock_thread(void *args)
{
    sock_ip_ep_t local = SOCK_IPV6_EP_ANY;
    sock_ip_t sock;

    if (sock_ip_create(&sock, &local, NULL, PROTNUM_UDP, 0) < 0)
    {
        puts("Error creating raw IP sock");
        return 1;
    }

    printf("value in buffer = %s\n", buf);
    while (1)
    {
        sock_ip_ep_t remote;
        ssize_t res;

        if ((res = sock_ip_recv(&sock, buf, sizeof(buf), SOCK_NO_TIMEOUT,
                                &remote)) >= 0)
        {
            puts("Received a message");
            uint8_t *ptr = buf;
            printf("\nres = %d\n", res);
            for (int i = 0; i < 128; i++)
                printf("%x  ", *(ptr++));
            printf("\n\n");
            udp_hdr_t *msg = buf;
            udp_hdr_print(msg);
        }
    }

    return 0;
}