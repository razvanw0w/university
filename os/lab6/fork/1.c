#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
	int f = fork();
	if (f < 0) {
		perror("Error on creating child process\n");
		exit(1);
	}
	if (f == 0) {
		printf("Child process: %d ", getpid());
		exit(0);
	}
	wait(0);
	printf("Parent process: %d\n", getpid());
	return 0;
}
