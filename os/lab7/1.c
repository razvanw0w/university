#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

int main()  {
	int forkResult;
	int p2c[2], c2p[2];

	if (pipe(p2c) < 0) {
		perror("Error on p2c pipe");
		exit(1);
	}
	if (pipe(c2p) < 0) {
		perror("Error on c2p pipe");
		exit(2);
	}

	forkResult = fork();
	if (forkResult < 0) {
		perror("Error on fork");
		exit(3);
	}
	if (forkResult == 0) {
		printf("We are in the child process!\n");
		close(p2c[1]); // closing the writing end from parent to child
		close(c2p[0]); // closing the reading end from child to parent

		int length;
		char *receivedString;
		if (read(p2c[0], &length, sizeof(int)) < 0) {
			perror("Error reading the length from the parent");
			exit(7);
		}
		receivedString = (char*)malloc(length * sizeof(char));
		if (read(p2c[0], receivedString, length * sizeof(char)) < 0) {
			perror("Error reading the string from the parent");
			exit(8);
		}
		close(p2c[0]);

		int r = rand() % 10 + 10;
		printf("Random: %d generated in child\n", r);
		if (write(c2p[1], &r, sizeof(int)) < 0) {
			perror("Error sending the random number to the parent");
			exit(9);
		}
		close(c2p[1]);
		free(receivedString);
		exit(0);
	}
	printf("We are in the parent process!\n");
	close(p2c[0]);
	close(c2p[1]);

	printf("Please enter a string: ");
	char *buffer = (char*)malloc(100 * sizeof(char));
	scanf("%s", buffer);
	int stringSize = strlen(buffer);

	if (write(p2c[1], &stringSize, sizeof(int)) < 0) {
		perror("Error sending the string length");
		exit(4);
	}
	if (write(p2c[1], buffer, stringSize * sizeof(char)) < 0) {
		perror("Error sending the string");
		exit(5);
	}
	close(p2c[1]);
	if (read(c2p[0], &stringSize, sizeof(int)) < 0) {
		perror("Error on reading the number of letters from the child");
		exit(6);
	}
	close(c2p[0]);
	free(buffer);
	return 0;
}
