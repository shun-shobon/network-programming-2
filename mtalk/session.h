#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>

#define PORT (in_port_t)50002
#define HOSTNAME_LENGTH 64

extern void session_init(int soc);
extern void session_loop();
