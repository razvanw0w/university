#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

#define FIFO "ch1"

int main() {
	int fileDescriptor, n;
	printf("Opening the fifo IN READING PAIR\n");
	fileDescriptor = open(FIFO, O_RDONLY);
	if (fileDescriptor < 0) {
		perror("Error opening the fifo channel (READ PART)");
		exit(1);
	}
	printf("Channel is open! (READ PART)\n");
	if (read(fileDescriptor, &n, sizeof(int)) < 0) {
		perror("Error receiving n\n");
		exit(2);
	}
	printf("I received n = %d\n", n);

	close(fileDescriptor);
	return 0;
}
