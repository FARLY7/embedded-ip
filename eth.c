#include "eth.h"
#include <string.h>

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

int eth_serialize(struct eth_hdr *eth, uint8_t *buf, size_t len)
{
    uint8_t *p = buf;

    /* DMAC */
    memcpy(p, eth->dmac, sizeof(eth->dmac));
    p += sizeof(eth->dmac);

    /* SMAC */
    memcpy(p, eth->smac, sizeof(eth->smac));
    p += sizeof(eth->smac);

    /* Type */
    uint16_t type = htons(eth->type);
    memcpy(p, &type, sizeof(type));
    p += sizeof(type);

    /* Data */
    //if(eth->data < 43)
    memcpy(p, eth->data, 50);
    p += 100;

    /* FCS */
    uint32_t fcs = htonl(eth->fcs);
    memcpy(p, &fcs, sizeof(fcs));
    p += sizeof(type);

    return (p - buf);
}

int eth_parse(uint8_t *buf, size_t len, struct eth_hdr *eth)
{
    uint8_t *p = buf;

    memset(eth, 0, sizeof(*eth));

    /* DMAC */
    memcpy(eth->dmac, p, sizeof(eth->dmac));
    p += sizeof(eth->dmac);

    /* SMAC */
    memcpy(eth->smac, p, sizeof(eth->smac));
    p += sizeof(eth->smac);

    /* Type */
    memcpy(&eth->type, p, sizeof(eth->type));
    p += sizeof(eth->type);
    eth->type = ntohs(eth->type);

    /* Data */
    //size_t data_len = (p-buf)-4;
    size_t data_len = len - (p-buf-4);
    eth->data = malloc(data_len);
    if(eth->data == NULL) {
        return -1;
    }
    memcpy(eth->data, p, data_len);
    p += data_len;

    /* FCS */
    memcpy(&eth->fcs, buf, sizeof(eth->fcs));
    p += sizeof(eth->fcs);
    eth->fcs = ntohl(eth->fcs);

    //return (p - buf);
    return data_len;
}

void eth_print(struct eth_hdr *eth)
{
    char type[16];

    switch(eth->type)
    {
        case ETHTYPE_IPV4:  snprintf(type, 16, "IPv4"); break;
        case ETHTYPE_ARP:   snprintf(type, 16, "ARP");  break;
        case ETHTYPE_IPV6:  snprintf(type, 16, "IPv6"); break;
        default: snprintf(type, 16, "N/A");
    }

    printf( "DMAC: %02X:%02X:%02X:%02X:%02X:%02X\n"     \
            "SMAC: %02X:%02X:%02X:%02X:%02X:%02X\n"     \
            "Type: %04X (%s)\n"                         \
            " FCS: %08X (%d)\n",                        \
            eth->dmac[0], eth->dmac[1], eth->dmac[2],   \
            eth->dmac[3], eth->dmac[4], eth->dmac[5],   \
            eth->smac[0], eth->smac[1], eth->smac[2],   \
            eth->smac[3], eth->smac[4], eth->smac[5],   \
            eth->type, type, eth->fcs, eth->fcs);
}