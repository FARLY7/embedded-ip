#ifndef ARP_H
#define ARP_H

#include <stdint.h>
#include <stddef.h>

struct arp_hdr {
    uint16_t hwtype;
    uint16_t protype;
    uint8_t hwsize;
    uint8_t prosize;
    uint16_t opcode;
    uint8_t *data;
};

int arp_parse(uint8_t *buf, size_t len, struct arp_hdr *arp);

int arp_serialize(struct arp_hdr *arp, uint8_t *buf, size_t len);

void arp_print(struct arp_hdr *eth);

#endif