#ifndef NANO_DEVICE_H
#define NANO_DEVICE_H

#include <stdint.h>
#include <stddef.h>

#define MAX_DEVICE_NAME 16

struct eth_mac {
    uint8_t addr[6];
};

struct nano_device {

    char name[MAX_DEVICE_NAME];

    struct eth_mac mac; 

    int (*send)(struct nano_device *self, void *buf, size_t len);

    int (*recv)(struct nano_device *self);

    void (*destroy)(struct nano_device *self);
};

int nano_device_init(struct nano_device *dev, const char *name, const uint8_t *mac);

void nano_device_destroy(struct nano_device *dev);

#endif /* DEVICE_H */