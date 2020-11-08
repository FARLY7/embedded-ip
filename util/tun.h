#ifndef TUN_H
#define TUN_H

#include <linux/if.h>
#include <linux/if_tun.h>

int tun_alloc(char *dev, int flags);

#endif