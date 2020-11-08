#ifndef DEV_TUN
#define DEV_TUN

#include "device.h"


/**
 * @brief   Destroy a Linux TUN device.
 *
 * @param   tun[in] Pointer to Linux TUN device.
 */
void tun_destroy(struct device *dev);

/**
 * @brief   Create a Linux TUN device.
 * 
 * @param   name[in] Pointer to device name
 * 
 * @return  Pointer to stack device struct.
 */
struct device* tun_create(const char *name);


#endif