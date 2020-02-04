#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int g = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* func(void *p) {
	int i = *(int*)p;

	for (int j = 0; j < 10; ++j) {
		pthread_mutex_lock(&mtx);
		++g;
		printf("Thread id: %d g: %d\n", i, g);
		pthread_mutex_unlock(&mtx);
	}

	free(p);
	return NULL;
}

int main(int argc, char* argv[]) {
	int n = 5;
	pthread_t th[n];

	int i;
	for (i = 0; i < n; ++i) {
		int *p = (int*)malloc(sizeof(int));
		*p = i;
		pthread_create(&th[i], NULL, func, p);
	}

	for (i = 0; i < n; ++i) {
		pthread_join(th[i], NULL);
	}
	return 0;
}
