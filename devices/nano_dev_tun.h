#ifndef NANO_DEV_TUN
#define NANO_DEV_TUN

#include "nano_device.h"


/**
 * @brief   Destroy a Linux TUN device.
 *
 * @param   tun[in] Pointer to Linux TUN device.
 */
void tun_destroy(struct nano_device *dev);

/**
 * @brief   Create a Linux TUN device.
 * 
 * @param   name[in] Pointer to device name
 * 
 * @return  Pointer to stack device struct.
 */
struct nano_device* tun_create(const char *name);


#endif