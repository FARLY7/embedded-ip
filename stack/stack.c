#include "stack.h"

#include "frame.h"



/*******************************************************************************
 *  DATALINK LAYER
 ******************************************************************************/

/* From dev up to socket */
int datalink_receive(struct frame *f) {

}

/* From socket down to dev */
int datalink_send(struct frame *f) {

}


/*******************************************************************************
 *  PHYSICAL LAYER
 ******************************************************************************/

/* Enqueues the frame in the device-queue. From socket down to dev */
int sendto_dev(struct frame *f) {

}

static struct frame *stack_recv_new_frame(struct device *dev, uint8_t *buffer, uint32_t len) {

}

int stack_recv(struct device *dev, uint8_t *buffer, uint32_t len) {


}



void stack_tick() {

}

void stack_loop() {

}

int stack_init() {

#ifdef SUPPORT_ETH
    protocol_init(&proto_ethernet);
#endif


}