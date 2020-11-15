# micro-ip

An (ongoing) simple implementation of a TCP/IP stack.

This TCP/IP stack will be used for educational purposes only.
Therefore, the feature set offered will be minimal.

tup.c/.h is used to create a virtual TAP Ethernet interface in linux.

# Notes

Generate Ethernet frames:
```c
$> sudo ip link set tap1 up
$> sudo ip addr add 10.0.0.1/24 dev tap1
$> ping 10.0.0.2 
```
