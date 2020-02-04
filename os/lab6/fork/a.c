#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char **argv) {
	int pid;
	printf("b's PID?: ");
	scanf("%d", &pid);
	kill(pid, SIGINT);
	return 0;
}
