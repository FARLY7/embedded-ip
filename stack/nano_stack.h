#ifndef NANO_STACK_H
#define NANO_STACK_H

#include <stdint.h>

/*******************************************************************************
 *  DATALINK LAYER
 ******************************************************************************/

/* From dev up to socket */
int nano_datalink_receive(struct nano_frame *f);

/* From socket down to dev */
int nano_datalink_send(struct nano_frame *f);

/*******************************************************************************
 *  PHYSICAL LAYER
 ******************************************************************************/

/* Enqueues the frame in the device-queue. From socket down to dev */
int nano_sendto_dev(struct nano_frame *f);

int nano_stack_recv(struct nano_device *dev, uint8_t *buffer, uint32_t len);


/* -------- Initialization --------- */
int nano_stack_init(void);

/* -------- Loop Function ---------- */
void nano_stack_loop(void);
void nano_stack_tick(void);

#endif