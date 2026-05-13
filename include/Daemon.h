#ifndef DAEMON_H
#define DAEMON_H

#include <signal.h>
void daemonize(void);

extern volatile sig_atomic_t terminate_received;

#endif