#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "eth.h"


static char tap_name[IFNAMSIZ];



int main(int argc, char *argv[])
{
    int tapfd;
    int nread;
    uint8_t buffer[ETH_FRAME_LEN];
    struct eth_hdr eth;

    struct device *tun_dev = tun_create("Linux TUN");
    if(!tun_dev) {
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

        /* Parsed Ethernet frame */
        printf("\nRead %d bytes from device %s\n", nread, tap_name);

        struct pbuf *p = pbuf_alloc(nread);
        memcpy(p->data, buffer, nread);

        if(eth_parse(p) == -1) {
            printf("Failed to parse Ethernet frame\n");
            continue;
        }
    }

    return 0;
}