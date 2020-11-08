#ifndef DEVICE_H
#define DEVICE_H

#include <stdint.h>
#include <stddef.h>

#include "eth.h"

#define MAX_DEVICE_NAME 16

struct device {
    char name[MAX_DEVICE_NAME];

    struct eth_hdr mac; 

    int (*send)(struct device *self, void *buf, size_t len);

    int (*recv)(struct device *self);

    void (*destroy)(struct device *self);
};

int device_init(struct device *dev, const char *name, const uint8_t *mac);

void device_destroy(struct device *dev);

#endif /* DEVICE_H */