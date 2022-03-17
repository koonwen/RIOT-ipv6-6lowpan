// #include "net/af.h"
// #include "net/protnum.h"
// #include "net/sock/ip.h"
// #include "collection.h"

// uint8_t buf[128];

// void *ip_raw_sock_thread(void *args)
// {
//     sock_ip_ep_t local = SOCK_IPV6_EP_ANY;
//     sock_ip_t sock;

//     if (sock_ip_create(&sock, &local, NULL, PROTNUM_IPV6_NONXT, 0) < 0)
//     {
//         puts("Error creating raw IP sock");
//         return 1;
//     }

//     while (1)
//     {
//         sock_ip_ep_t remote;
//         ssize_t res;

//         if ((res = sock_ip_recv(&sock, buf, sizeof(buf), SOCK_NO_TIMEOUT,
//                                 &remote)) >= 0)
//         {
//             puts("Received a message");
//             if (sock_ip_send(&sock, buf, res, 0, &remote) < 0)
//             {
//                 puts("Error sending reply");
//             }
//         }
//     }

//     return NULL;
// }