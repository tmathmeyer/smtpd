#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>



void run_as_daemon(void (*post_fork)(int)) {
	pid_t pid, sid;
	pid = fork();

	if (pid < 0) {
		exit(EXIT_FAULURE);
	}
	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}

	umask(0);
	if (sid < 0) {
		exit(EXIT_FAULURE);
	}

	if ((chdir("/")) < 0) {
		exit(EXIT_FAULURE);
	}

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	post_fork(pid);
}