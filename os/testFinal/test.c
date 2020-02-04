#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void f(int n) {
	if (n > 0 && fork() == 0) {
		printf("forked\n");
		f(n - 1);
		exit(0);
	}
	wait(0);
}


int main() {
	f(3);

	return 0;
}
