#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {	
	printf("forked\n");
	fork();
	wait(0);
	printf("forked\n");
	fork();
	wait(0);
	printf("forked\n");
	fork();
	return 0;
}
