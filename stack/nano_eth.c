#include "nano_eth.h"
#include <string.h>

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

void eth_print(struct eth_hdr *eth)
{
    char type[16];

    switch(eth->type)
    {
        case ETHTYPE_IP:    snprintf(type, 16, "IPv4"); break;
        case ETHTYPE_ARP:   snprintf(type, 16, "ARP");  break;
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


int eth_receive(struct nano_frame *f)
{
    struct eth_hdr *hdr = (struct eth_hdr *) f->hdr;
	
    switch(hdr->type)
	{	
		case ETHTYPE_ARP: return arp_recieve(f);
		case ETHTYPE_IP:  return ipv4_recieve(f);
		default: printf("ETHTYPE UNKNOWN");
	}

    frame_discard(f);
}
