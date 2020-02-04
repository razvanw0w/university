#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_rwlock_t rwLock = PTHREAD_RWLOCK_INITIALIZER;
int done = 0;
int maxThreads = 10;
int g = 0;


void* funcProducer(void *p) {
	int i = *(int*)p;

	for (int j = 0; j < 10; ++j) {
		pthread_rwlock_wrlock(&rwLock);
		++g;
		printf("Producer thread id: %d g: %d\n", i, g);
		pthread_rwlock_unlock(&rwLock);
	}

	free(p);
	return NULL;
}

void* funcConsumer(void *p) {
	int i = *(int*)p;
	printf("Thread %i started\n", i);

	for (int j = 0; j < 10; ++j) {
		pthread_rwlock_rdlock(&rwLock);
		printf("Consumer thread id: %d g: %d\n", i, g);
		pthread_rwlock_unlock(&rwLock);
	}

	free(p);
	return NULL;
}


int main(int argc, char* argv[]) {
	int n = maxThreads;
	srand(time(0));

	pthread_t tProducers[n];
	pthread_t tConsumers[n];
	for (int i = 0; i < n; ++i) {
		int *p = (int*)malloc(sizeof(int));
		*p = i;

		pthread_create(&tConsumers[i], NULL, funcConsumer, p);
	}

	for (int i = 0; i < n; ++i) {
		int *p = (int*)malloc(sizeof(int));
		*p = i;
		pthread_create(&tProducers[i], NULL, funcProducer, p); 
	}  

	for (int i = 0; i < n; ++i) {
		pthread_join(tProducers[i], NULL);
	}

	for (int i = 0; i < n; ++i) {
		pthread_join(tConsumers[i], NULL);
	}
	return 0;
}

