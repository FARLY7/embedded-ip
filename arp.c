#include "arp.h"

/**
 * @todo Add ARP table.
 * 
 * IP Adress, HW type, HW Address, Flags Mask, IFace.
 */


int arp_parse(uint8_t *buf, size_t len, struct arp_hdr *arp)
{
    uint8_t *p = buf;
    memset(arp, 0, sizeof(*arp));

    /* HW Type */
    memcpy(arp->hwtype, p, sizeof(arp->hwtype));
    p += sizeof(arp->hwtype);
    arp->hwtype = ntohs(arp->hwtype);

    /* Protocol Type */
    memcpy(arp->protype, p, sizeof(arp->protype));
    p += sizeof(arp->protype);
    arp->protype = ntohs(arp->protype);

    /* HW Size */
    arp->hwsize = *p++;

    /* HW Size */
    arp->prosize = *p++;
    
    /* Opcode */
    memcpy(arp->opcode, p, sizeof(arp->opcode));
    p += sizeof(arp->opcode);
    arp->opcode = ntohs(arp->opcode);

    /* Data */
    size_t data_len = len-(p-buf); 
    arp->data = malloc(data_len);
    if(arp->data == NULL) {
        return -1;
    }

    return 0;
}

int arp_serialize(struct arp_hdr *arp, uint8_t *buf, size_t len)
{
    /** @todo */
    return 0;
}

void arp_print(struct arp_hdr *eth)
{
    /** @todo */
}
