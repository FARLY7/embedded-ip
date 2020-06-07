#ifndef ETH_H
#define ETH_H

#include <stdint.h>
#include <stddef.h>

struct eth_hdr {
    uint8_t dmac[6];
    uint8_t smac[6];
    uint16_t type;
    uint8_t *data;
    uint32_t fcs;
};

int eth_serialize(struct eth_hdr *eth, uint8_t *buf, size_t len);

int eth_parse(uint8_t *buf, size_t len, struct eth_hdr *eth);

void eth_print(struct eth_hdr *eth);

#endif