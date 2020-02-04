#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int n, i;
	int *a;

	printf("Please give a number: ");
	scanf("%d", &n);
	a = (int*)malloc(n * sizeof(int))	

	printf("N: %d\n", n);

	for (i = 0; i < n; ++i) {
		printf("a[%d] = ", i);
		scanf("%d", &a[i]);
	}
	printf("\n");
	for (i = 0; i < n; ++i) {
		printf("%d ", a[i]);
	}
	free(a);
	return 0;
}
