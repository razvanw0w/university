#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int forkA, forkB;

	forkA = fork();
	if (forkA < 0) {
		perror("Fork A failed\n");
		exit(1);
	}
	if (forkA == 0) {
		printf("PID A: %d PID PARENT: %d\n", getpid(), getppid());
		forkB = fork();
		if (forkB < 0) {
			perror("Fork B failed\n");
			exit(2);
		}
		if (forkB == 0) {
			printf("PID B: %d PID PARENT: %d\n", getpid(), getppid());
			exit(0);
		}
		wait(0);
		exit(0);
	}
	else {
		printf("PID MAIN: %d PID PARENT: %d\n", getpid(), getppid());
	}
	wait(0);
	return 0;
}
