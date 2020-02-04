#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	int forkA, forkB;	
	int a2b[2], b2a[2];
	if (pipe(a2b) < 0) {
		perror("Error on pipe a2b");
		exit(1);
	}
	if (pipe(b2a) < 0) {
		perror("Error on pipe b2a");
		exit(2);	
	}

	forkA = fork();
	if (forkA < 0) {
		perror("Error on fork A");
		exit(3);
	}
	else if (forkA == 0) {
		// we are in A
		if (close(b2a[1]) < 0) {
			perror("error on closing b2a write");
			exit(4);
		}
		if (close(a2b[0]) < 0) {
			perror("error on closing a2b read");
			exit(5);
		}
		srand(time(0));
		int r = 50 + rand() % (200 - 50 + 1);
		if (r % 2 == 1) {
			++r;
		}
		if (write(a2b[1], &r, sizeof(int)) < 0) {
			perror("Error on writing r from A to B outside");
			exit(6);
		}
		printf("Wrote %d from A to B\n", r);
		if (read(b2a[0], &r, sizeof(int)) < 0) {
			perror("Error on reading r from B to A outside");
			exit(8);
		}
		printf("Read %d from B to A\n", r);
		while (r >= 5) {
			if (r % 2 == 1) {
				++r;
			}
			if (write(a2b[1], &r, sizeof(int)) < 0) {
				perror("Error on writing r from A to B in loop");
				exit(7);
			}
			printf("Wrote %d from A to B\n", r);
			if (read(b2a[0], &r, sizeof(int)) < 0) {
				perror("Error on reading r from B to A in loop");
				exit(9);
			}
			printf("Read %d from B to A\n", r);
		}
		close(a2b[1]);
		close(b2a[0]);
		printf("Exited A\n");
		exit(0);
	}
	else {
		// in parent, must create B
		forkB = fork();
		if (forkB < 0) {
			perror("Error on fork B");
			exit(10);
		}
		if (forkB == 0) {
			int r;
			close(a2b[1]);
			close(b2a[0]);
			if (read(a2b[0], &r, sizeof(int)) < 0) {
				perror("Error on reading r from A to B outside");
				exit(11);
			}
			printf("Read %d from A to B\n", r);
			while (r >= 5) {
				r /= 2;
				if (write(b2a[1], &r, sizeof(int)) < 0) {
					perror("Error on writing r from B to A in loop");
					exit(12);
				}
				printf("Wrote %d from B to A\n", r);
				if (read(a2b[0], &r, sizeof(int)) < 0) {
					perror("Error on reading r from A to B in loop");
					exit(13);
				}
				printf("Read %d from A to B\n", r);
			}
			close(a2b[0]);
			close(b2a[1]);
			printf("Exited B\n");
			exit(0);
		}
	}
	close(a2b[0]);
	close(a2b[1]);
	close(b2a[0]);
	close(b2a[1]);
	return 0;
}
