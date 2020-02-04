#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	int numberOfElements;
	printf("Number of elements: ");
	int isValid = scanf("%d", &numberOfElements);
	if (isValid != 1) {
		perror("Invalid number of elements");
		exit(1);
	}

	int p2c[2], c2p[2];
	if (pipe(p2c) < 0) {
		perror("Error pipe parent2child");
		exit(2);
	}
	if (pipe(c2p) < 0) {
		perror("Error pipe child2parent");
		exit(3);
	}

	int forkValue = fork();
	if (forkValue < 0) {
		perror("Error on fork");
		exit(4);
	}
	else if (forkValue == 0) {
		// child
		int n, i;
		close(p2c[1]);
		close(c2p[0]);
		if (read(p2c[0], &n, sizeof(int)) < 0) {
			perror("Error on reading nr of elems");
			exit(5);
		}
		printf("Read number of elements in child: %d\n", n);
		int *number = (int*)malloc(sizeof(int) * n);
		for (i = 0; i < n; ++i) {
			if (read(p2c[0], &number[i], sizeof(int)) < 0) {
				perror("Error on reading elems");
				exit(6);
			}
			printf("Read number %d on position %d in child\n", number[i], i);
		}
		close(p2c[0]);
		for (i = n - 1; i >= 0; --i) {
			if (write(c2p[1], &number[i], sizeof(int)) < 0) {
				perror("Error on writing elems");
				exit(7);
			}
			printf("Wrote number %d in child\n", number[i]);
		}
		close(c2p[1]);
		free(number);
		exit(0);
	}
	else {
		close(c2p[1]);
		close(p2c[0]);
		if (write(p2c[1], &numberOfElements, sizeof(int)) < 0) {
			perror("Error on writing nr of elems");
			exit(8);
		}
		printf("Wrote number of elements in parent: %d\n", numberOfElements);
		srand(time(0));
		for (int i = 0; i < numberOfElements; ++i) {
			int r = rand() % 1000000;
			if (write(p2c[1], &r, sizeof(int)) < 0) {
				perror("Error on writing elements");
				exit(9);
			}
			printf("Wrote number %d on position %d in parent\n", r, i);
		}
		close(p2c[1]);
		for (int i = 0; i < numberOfElements; ++i) {
			int r;
			if (read(c2p[0], &r, sizeof(int)) < 0) {
				perror("Error on receiving elements");
				exit(10);
			}
			printf("Read number %d in parent\n", r);
		}
		close(c2p[0]);
	}
	return 0;
}
