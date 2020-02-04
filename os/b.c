#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	execlp("x", "x", NULL);
	printf("pula\n");

	return 0;
}
