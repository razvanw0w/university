#include <stdio.h>

int main(int argc, char **argv) {
	int n;
	int *a;
	printf("Give n:");
	scanf("%d", &n);	
	printf("N: %d", n);

	a = (int*)malloc(n * sizeof(int));
	free(a);
	return 0;
}
