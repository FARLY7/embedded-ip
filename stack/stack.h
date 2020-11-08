#ifndef STACK_H
#define STACK_H

#include <stdint.h>

/*******************************************************************************
 *  DATALINK LAYER
 ******************************************************************************/

/* From dev up to socket */
int datalink_receive(struct frame *f);

/* From socket down to dev */
int datalink_send(struct frame *f);

/*******************************************************************************
 *  PHYSICAL LAYER
 ******************************************************************************/

/* Enqueues the frame in the device-queue. From socket down to dev */
int sendto_dev(struct frame *f);

int stack_recv(struct device *dev, uint8_t *buffer, uint32_t len);


/* -------- Initialization --------- */
int stack_init(void);

/* -------- Loop Function ---------- */
void stack_loop(void);
void stack_tick(void);

#endif