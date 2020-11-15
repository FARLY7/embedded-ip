#include "nano_stack.h"
#include "nano_frame.h"

/*******************************************************************************
 *  DATALINK LAYER
 ******************************************************************************/

/* From dev up to socket */
int nano_datalink_receive(struct nano_frame *f) {

	/* Ethernet =================================== */
	/* Ethernet header is beginning of frame */
	f->datalink_hdr = f->buffer;
	return eth_receive(f);
	/* ============================================ */
}

/* From socket down to dev */
int nano_datalink_send(struct nano_frame *f) {

}


/*******************************************************************************
 *  PHYSICAL LAYER
 ******************************************************************************/

/* Enqueues the frame in the device-queue. From socket down to dev */
int nano_sendto_dev(struct nano_frame *f) {

}

static struct nano_frame *nano_stack_recv_new_frame(struct device *dev, uint8_t *buffer, uint32_t len)
{
    struct nano_frame *f;

    if(len == 0)
        return NULL;

    f = nano_frame_alloc(len);

    if(!f) {
        printf("Failed to alloc incoming frame!\n");
        return NULL;
    }

    /* Associate to the device that just received the frame. */
    f->dev = dev;

    /* Copy frame contents into allocated buffer */
    memcpy(f->buffer, buffer, len);
    return f;
}

/**
 * @brief  Frame is received from a device into the stack.
 */
int nano_stack_recv(struct nano_device *dev, uint8_t *buffer, uint32_t len)
{
    struct nano_frame *f = nano_stack_recv_new_frame(dev, buffer, len);

    if(!f)
        return 1;

    return nano_datalink_receive(f);
}

void nano_stack_tick() {

}

void nano_stack_loop() {

}

int nano_stack_init() {

#ifdef SUPPORT_ETH
    protocol_init(&proto_ethernet);
#endif

}
