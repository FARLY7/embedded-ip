#ifndef FRAME_H
#define FRAME_H

#include <stdint.h>
#include <stddef.h>

struct nano_frame {
    /* Start of the whole buffer, total frame length */
    uint8_t *buffer;
    size_t   buffer_len;

    /* Pointer to protocol headers */
    uint8_t *datalink_hdr;
    size_t   datalink_len;
    
    uint8_t *net_hdr;
    size_t   net_len;

    /* Pointer to the payload */
    uint8_t *payload;
    size_t   payload_len;

    /* Pointer to the physical device this packet belongs to */
    struct nano_device *dev;

    uint32_t usage_count;
};

struct nano_frame *nano_frame_alloc(size_t size);

void nano_frame_discard(struct nano_frame *frame);

#endif