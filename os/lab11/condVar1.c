#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int done = 0;
int maxThreads = 10;

void* f(void *p) {
	int i = *(int*)p;
	printf("Thread %i started\n", i);


	int maxStep = 10;
	for (int j = 0; j < maxStep; ++j) {
		printf("Thread #%d | Loop (%d/%d) \n", i, j, maxStep);
		usleep((rand() % 3 + 1) * 2050);
	}

	pthread_mutex_lock(&mtx);
	++done;
	printf("Thread %d signal the main thread\n", i);
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mtx);

	free(p);
	return NULL;
}

int main(int argc, char* argv[]) {
	int n = maxThreads;
	srand(time(0));

	pthread_t t[n];
	for (int i = 0; i < n; ++i) {
		int *p = (int*)malloc(sizeof(int));
		*p = i;

		pthread_create(&t[i], NULL, f, p);
	}

	pthread_mutex_lock(&mtx);
	while (done < maxThreads) {
		printf("Finished threads: %d. Not all threads are finished!\n", done);
		pthread_cond_wait(&cond, &mtx);
	}
	printf("All threads finished!\n");
	pthread_mutex_unlock(&mtx);

	for (int i = 0; i < n; ++i) {
		pthread_join(t[i], NULL);
	}
	return 0;
}

