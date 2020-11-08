#include "dev_tun.h"

#include <stdio.h>

#include "linux/if_ether.h"
#include <fcntl.h>      /* open() */
#include <sys/ioctl.h>  /* ioctl() */
#include <unistd.h>     /* close() */
#include <stdlib.h>     /* free() */

#define TUN_MTU 2048

struct device_tun {
    /* Parent */
    struct device dev;
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

static int tun_send(struct device *dev, void *buf, size_t len) {
    struct device_tun *tun = (struct device_tun *) dev;

    return write(tun->fd, buf, len);
}

static int tun_recv(struct device *dev) {
    struct device_tun *tun = (struct device_tun *) dev;

    uint8_t buf[TUN_MTU];
    int len;

    /* Note that 'buffer' should be at least the MTU size of the interface,
        * e.g. 1514 bytes */
    len = read(tun->fd, buf, sizeof(buf));

    if(len > 0) {
        stack_recv(dev, buf, (size_t) len);
    }

    if(len < 0) {
        printf("Tun read failed\n");
        tun_destroy((struct device *) tun);
        return 1;
    }

    return 0;
}

/* ====================================================== */
/* ====================    PUBLIC    ==================== */
/* ====================================================== */

void tun_destroy(struct device *dev) {
    struct device_tun *tun = (struct device_tun *) dev;

    if(tun->fd > 0) {
        close(fd);
    }
}

struct device* tun_create(const char *name)
{
    struct device_tun *tun = malloc(sizeof(struct device_tun));

    if(!tun) {
        return NULL;
    }

    if(device_init((struct device *) tun, name, NULL) != 0) {
        printf("Tun init failed\n");
        tun_destroy((struct device *) tun);
        return NULL;
    }

    tun->fd = tun_open(name);
    if(tun->fd < 0) {
        printf("Tun creation failed\n");
        tun_destroy((struct device *) tun);
        return NULL;
    }

    tun->dev.send    = tun_send;
    tun->dev.recv    = tun_recv;
    tun->dev.destroy = tun_destroy;
    printf("Device %s created\n", tun->dev.name);
    return tun;
}