#include "nano_dev_tun.h"

#include <stdio.h>
#include <stdlib.h>

#define TUN_MTU 2048

struct nano_device_tun {
    /* Parent */
    struct nano_device dev;
    /* Child */
    int fd;
};


/* ====================================================== */
/* ===================    PRIVATE    ==================== */
/* ====================================================== */

static int tun_open(char *name) {
    int tapfd;

    /* Flags: IFF_TUN   - TUN device (no Ethernet headers)
     *        IFF_TAP   - TAP device
     *
     *        IFF_NO_PI - Do not provide packet information
     */
    strcpy(tap_name, "tap1");
    tapfd = tun_alloc(tap_name, IFF_TAP | IFF_NO_PI);

    if(tapfd < 0) {
        printf("Failed to allocate TAP interface\n");
        return (-1);
    }

    return tapfd;
}

static int tun_send(struct nano_device *dev, void *buf, size_t len) {
    struct nano_device_tun *tun = (struct nano_device_tun *) dev;

    return write(tun->fd, buf, len);
}

static int tun_recv(struct nano_device *dev) {
    struct nano_device_tun *tun = (struct nano_device_tun *) dev;

    uint8_t buf[TUN_MTU];
    int len;

    /* Note that 'buffer' should be at least the MTU size of the interface,
        * e.g. 1514 bytes */
    len = read(tun->fd, buf, sizeof(buf));

    if(len > 0) {
        printf("Tun read %d bytes\n", len);
        nano_stack_recv(dev, buf, (size_t) len);
    }

    if(len < 0) {
        printf("Tun read failed\n");
        tun_destroy((struct nano_device *) tun);
        return 1;
    }

    return 0;
}

/* ====================================================== */
/* ====================    PUBLIC    ==================== */
/* ====================================================== */

void nano_tun_destroy(struct nano_device *dev) {
    struct device_tun *tun = (struct device_tun *) dev;

    if(tun->fd > 0) {
        close(fd);
    }
}

struct device* nano_tun_create(const char *name)
{
    struct nano_device_tun *tun = malloc(sizeof(struct nano_device_tun));

    if(!tun) {
        return NULL;
    }

    if(nano_device_init((struct nano_device *) tun, name, NULL) != 0) {
        printf("Tun init failed\n");
        tun_destroy((struct nano_device *) tun);
        return NULL;
    }

    tun->fd = tun_open(name);
    if(tun->fd < 0) {
        printf("Tun creation failed\n");
        tun_destroy((struct nano_device *) tun);
        return NULL;
    }

    tun->dev.send = tun_send;
    tun->dev.recv = tun_recv;
    tun->dev.destroy = tun_destroy;
    printf("Device %s created\n", tun->dev.name);
    return tun;
}