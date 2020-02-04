#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
	int forkStatus = fork();
	if (forkStatus < 0) {
		perror("Can't create child");
		exit(1);
	}
	if (forkStatus == 0) {
		if (execl("/bin/ls", "ls", "-la", NULL) < 0) {
		       perror("Error in executing the command");
	       	   exit(2);
		}
	}
	wait(0);
	return 0;
}
