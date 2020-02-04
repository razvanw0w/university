#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

void interruptionHandler(int sig) {
	printf("Bye bye! I have been interrupted!\n");
	exit(0);
}

int main(int argc, char **argv) {
	printf("Current PID in b: %d\n", getpid());
	signal(SIGINT, interruptionHandler);
	int x;
	scanf("%d", &x);
	return 0;
}
