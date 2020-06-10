#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "tun.h"
#include "eth.h"

#include "linux/if_ether.h"

#include <fcntl.h>      /* open() */
#include <sys/ioctl.h>  /* ioctl() */
#include <unistd.h>     /* close() */
#include <stdlib.h>     /* free() */

static char tap_name[IFNAMSIZ];




static int handle_frame(struct eth_hdr *eth)
{
    switch(eth->type)
    {
        case ETHTYPE_IPV4:  ipv4_parse(eth->data); break;
        case ETHTYPE_ARP:   arp_parse(eth->data);  break;
        case ETHTYPE_IPV6:  ipv6_parse(eth->data); break;   
    }
    return 0;
}


int main(int argc, char *argv[])
{
    int tapfd;
    int nread;
    uint8_t buffer[ETH_FRAME_LEN];
    struct eth_hdr eth;

    /* Flags: IFF_TUN   - TUN device (no Ethernet headers)
     *        IFF_TAP   - TAP device
     *
     *        IFF_NO_PI - Do not provide packet information
     */
    strcpy(tap_name, "tap1");
    tapfd = tun_alloc(tap_name, IFF_TAP | IFF_NO_PI);

    if(tapfd < 0) {
        printf("Failed to allocate TAP interface\n");
        return 1;
    }

    /* Read data coming from the kernel */
    while(1)
    {
        /* Note that 'buffer' should be at least the MTU size of the interface,
         * e.g. 1514 bytes */
        nread = read(tapfd, buffer, sizeof(buffer));

        if(nread < 0) {
            printf("Failed to read from interface\n");
            close(tapfd);
            return 1;
        }

        if(eth_parse(buffer, nread, &eth) == -1) {
            printf("Failed to parse Ethernet frame\n");
            continue;
        }

        /* Parsed Ethernet frame */
        printf("\nRead %d bytes from device %s\n", nread, tap_name);
        eth_print(&eth);

        handle_frame(&eth);

        free(eth.data);    
    }

    return 0;
}