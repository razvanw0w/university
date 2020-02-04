#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_barrier_t barrier;

void* fth(void* arg) {
	int id = *(int*)arg;
	free(arg);

	printf("Thread %d started!\n", id);
	sleep(rand() % 5 + 1);
	printf("Thread %d waiting!\n", id);
	pthread_barrier_wait(&barrier);
	printf("Thread %d working!\n", id);
	sleep(rand() % 2 + 1);
	printf("Thread %d is done!\n", id);
	return NULL;
}

int main() {
	srand(time(0));

	int n;
	printf("N = ");
	scanf("%d", &n);

	pthread_t th[n];
	pthread_barrier_init(&barrier, NULL, n + 1);

	int i;
	for (i = 0; i < n; ++i) {
		int *p = (int*)malloc(sizeof(int));
		*p = i;
		pthread_create(&th[i], NULL, fth, p);
	}

	pthread_barrier_wait(&barrier);
	printf("All threads are ready now!\n");
	for (i = 0; i < n; ++i) {
		pthread_join(th[i], NULL);
	}
	pthread_barrier_destroy(&barrier);
	return 0;
}

