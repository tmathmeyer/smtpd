
#ifndef DAEMON
#define DAEMON

void run_as_daemon(void (*post_fork)(int));

#endif