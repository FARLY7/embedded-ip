#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "dev_tun.h"


int main(int argc, char *argv[])
{
    struct device *tun_dev = tun_create("Linux TUN");
    if(!tun_dev) {
        return 1;
    }

    /* Read data coming from the kernel */
    while(1)
    {
        tun_dev->recv(tun_dev);

        // struct pbuf *p = pbuf_alloc(nread);
        // memcpy(p->data, buffer, nread);

        // if(eth_parse(p) == -1) {
        //     printf("Failed to parse Ethernet frame\n");
        //     continue;
        // }
    }

    return 0;
}