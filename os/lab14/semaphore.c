#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semaphore;

void* fth(void* arg) {
	int id = *(int*)arg;
	free(arg);
	printf("Thread %d started!\n", id);

	printf("Thread %d is waiting!\n", id);
	sem_wait(&semaphore);
	// secure only M threads
	printf("Thread %d is working!\n", id);
	sleep(rand() % 3 + 1);
	sem_post(&semaphore);
	printf("Thread %d has finished!\n", id);
	return NULL;
}

int main() {
	srand(time(0));

	int n, m;
	
	printf("N = ");
	scanf("%d", &n);

	printf("M = ");
	scanf("%d", &m);

	sem_init(&semaphore, 0, m);
	pthread_t *th = (pthread_t*)malloc(sizeof(pthread_t) * n);

	int i;
	for (i = 0; i < n; ++i) {
		int *p = (int*)malloc(sizeof(int));
		*p = i;
		pthread_create(th + i, NULL, fth, p);
	}

	for (i = 0; i < n; ++i) {
		pthread_join(th[i], NULL);
	}

	free(th);
	return 0;
}
