#ifndef ETH_H
#define ETH_H

#include <stdint.h>
#include <stddef.h>

/**
 * @brief Ethernet Frame Types.
 */
typedef enum {
    ETHTYPE_IPV4 = 0x0800,  /**< Internet Protocol version 4 (IPv4) */
    ETHTYPE_ARP  = 0x0806,  /**< Address Resolution Protocol (ARP) */
    ETHTYPE_RARP = 0x8035,  /**< Reverse Address Resolution Protocol (RARP) */
    ETHTYPE_IPV6 = 0x86DD,  /**< Internet Protocol version 6 (IPv6) */
    ETHTYPE_EFC  = 0x8808   /**< Ethernet Flow Control */
} ethertype_t;

/**
 * @brief Ethernet Frame Header.
 */
struct eth_hdr {
    uint8_t dmac[6];    /**< Destination MAC Address */
    uint8_t smac[6];    /**< Source MAC Address */
    uint16_t type;      /**< Ethernet Frame Type */
    uint8_t *data;      /**< Payload */
    uint32_t fcs;       /**< Frame Check Sequence */
};

int eth_serialize(struct eth_hdr *eth, uint8_t *buf, size_t len);

int eth_parse(uint8_t *buf, size_t len, struct eth_hdr *eth);

void eth_print(struct eth_hdr *eth);

#endif