#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

#define FIFO "ch1"

int main() {
	int fileDescriptor, n;
	printf("Opening the fifo IN WRITING PAIR\n");
	fileDescriptor = open(FIFO, O_WRONLY);
	if (fileDescriptor < 0) {
		perror("Error opening the fifo channel (WRITE PART)");
		exit(1);
	}
	printf("Channel is open! (WRITE PART)\n");
	printf("Enter number: ");
	scanf("%d", &n);

	if (write(fileDescriptor, &n, sizeof(int)) < 0) {
		perror("Error sending n\n");
		exit(2);
	}

	close(fileDescriptor);
	return 0;
}
