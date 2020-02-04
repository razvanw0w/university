#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int myPipe[2];
	if (pipe(myPipe) < 0) {
		perror("Error creating the pipe channel!\n");
		exit(1);
	}
	int forkA, forkB;
	forkA = fork();
	if (forkA > 0) {
		forkB = fork();
		if (forkB == 0) {
			close(myPipe[1]);
			int n, number;
			read(myPipe[0], &n, sizeof(int));
			printf("Process B read n = %d\n", n);
			for (int i = 0; i < n; ++i) {
				read(myPipe[0], &number, sizeof(int));
				printf("Process B read number = %d on index %d\n", number, i);
			}
			close(myPipe[0]);
			printf("\n");
			exit(0);
		}
		else if (forkB < 0) {
			perror("Fork B failed\n");
			exit(3);
		}
	}
	else if (forkA == 0) {
		srand(time(0));
		int numberOfElements;
		printf("Number of elements: ");
		scanf("%d", &numberOfElements);
		write(myPipe[1], &numberOfElements, sizeof(int));
		printf("Process A wrote n = %d\n", numberOfElements);
		for (int i = 0; i < numberOfElements; ++i) {
			int randomNumber = rand() % 10 + 1;
			write(myPipe[1], &randomNumber, sizeof(int));
			printf("Process A generated and wrote number = %d on index %d\n", randomNumber, i);
		}
		exit(0);
	}
	else {
		perror("Fork A failed\n");
		exit(2);
	}
	wait(0);
	wait(0);
	return 0;
}
