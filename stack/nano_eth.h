#ifndef NANO_ETH_H
#define NANO_ETH_H

#include <stdint.h>
#include <stddef.h>

#define ETH_MAX_FRAME_LEN   1600

#define ETH_HWADDR_LEN      6

#define ETH_HEADER_LEN      14

/** Initialize a struct eth_addr with its 6 bytes (takes care of correct braces) */
#define ETH_ADDR(b0, b1, b2, b3, b4, b5) {{b0, b1, b2, b3, b4, b5}}

/**
 * @brief Ethernet Frame Types.
 */
typedef enum {
    ETHTYPE_IP   = 0x0800,  /**< Internet Protocol version 4 (IPv4) */
    ETHTYPE_ARP  = 0x0806,  /**< Address Resolution Protocol (ARP) */
} ethertype_t;

/**
 * @brief An Ethernet MAC address.
 */
struct eth_addr {
    uint8_t addr[ETH_HWADDR_LEN];
};

/**
 * @brief Ethernet Frame Header.
 */
struct eth_hdr {
    struct eth_addr dest; /**< Destination MAC Address */
    struct eth_addr src;  /**< Source MAC Address */
    uint16_t type;        /**< Ethernet Frame Type */
};

int eth_input(struct pbuf *p);

int eth_output(struct pbuf *p, const struct eth_addr* src, const struct eth_addr* dst, u16_t eth_type);

#endif /* NANO_ETH_H */