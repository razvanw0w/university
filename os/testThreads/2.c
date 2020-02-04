#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

int n = 0, N;
pthread_mutex_t mtx;

void* f(void* a) {
	while (n < N) {
		pthread_mutex_lock(&mtx);
		++n;
		pthread_mutex_unlock(&mtx);
	}

	return NULL;
}


int main(int argc, char* argv[]) {
	if (argc != 2) {
		perror("Not enough arguments!");
		exit(1);
	}

	N = atoi(argv[1]);
	pthread_t t[50];
	int i;

	for (i = 0; i < 50; ++i) {
		pthread_create(&t[i], NULL, f, NULL);
	}

	for (i = 0; i < 50; ++i) {
		pthread_join(t[i], NULL);
	}

	printf("n = %d\n", n);
	pthread_mutex_destroy(&mtx);
	return 0;
}
