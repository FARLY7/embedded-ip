#include "nano_device.h"

#include <string.h>

int nano_device_init(struct nano_device *dev, const char *name, const uint8_t *mac)
{
    strncpy(dev->name, name, MAX_DEVICE_NAME);
    memcpy(dev->mac.addr, mac, sizeof(eth_mac));
}

void nano_device_destroy(struct nano_device *dev)
{
    dev->destroy(dev);
}
