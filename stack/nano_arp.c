#include "nano_arp.h"

/**
 * @todo Add ARP table.
 * 
 * IP Adress, HW type, HW Address, Flags Mask, IFace.
 */

static struct nano_arp_hdr __packed__ {
    uint16_t hwtype;
    uint16_t protype;
    uint8_t hwsize;
    uint8_t prosize;
    uint16_t opcode;
    uint8_t smac[6];
    uint32_t sip;
    uint8_t dmac[6];
    uint32_t dip;
};

static void nano_arp_print(struct nano_arp_hdr *arp)
{
    /** @todo */
	printf( "ARP ==================================");
	printf(	"SMAC: %02X:%02X:%02X:%02X:%02X:%02X\n"		\
			"S_IP: %s\n"								\
			"DMAC: %02X:%02X:%02X:%02X:%02X:%02X\n"		\
			"D_IP: %s\n",								\
		    arp->smac[0], arp->smac[0], arp->smac[0], 	\ 		
			arp->smac[0], arp->smac[0], arp->smac[0], 	\
			arp->sip,									\
			arp->smac[0], arp->smac[0], arp->smac[0],	\
			arp->smac[0], arp->smac[0], arp->smac[0],	\
			arp->dip);
}

int nano_arp_receive(struct nano_frame *f)
{
	if(!f)
		return 1;
	
	struct nano_arp_hdr *arp = f->net_hdr;

	nano_arp_print(arp);
}

