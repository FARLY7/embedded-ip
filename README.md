# micro-ip

An (ongoing) simple implementation of a TCP/IP stack.

This TCP/IP stack will be used for educational purposes only.
Therefore, the feature set offered will be minimal.

| Layer       | Files  |
|-------------|--------|
| Application | To-do  |
| Transport   | To-do  |
| Network     | arp.h  |
| Data Link   | eth.h  |

tup.c/.h is used to create a virtual TAP Ethernet interface in linux.

# Notes

Compile and run:
```c
$> gcc main.c tun.c eth.c arp.c -o main
$> sudo ./main
```

Generate Ethernet frames:
```c
$> sudo ip link set tap1 up
$> sudo ip addr add 10.0.0.1/24 dev tap1
$> ping 10.0.0.2 
```