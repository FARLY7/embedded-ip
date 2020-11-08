#ifndef FRAME_H
#define FRAME_H

#include <stdint.h>
#include <stddef.h>

struct frame {
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
    //struct device *dev;
};

struct frame* frame_alloc(uint8_t *frame, size_t frame_len, uint8_t *hdr, size_t hdr_len, frame_type_t type);

void frame_free(struct frame *frame);

#endif