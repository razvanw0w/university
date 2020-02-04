#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t t1, t2;
int n;
pthread_mutex_t mtx;

void* f1(void* a) {
	int n;
	while (1) {
		pthread_mutex_lock(&mtx);
		n = 1 + rand() % 10;
		printf("Created %d\n", n);
		pthread_mutex_unlock(&mtx);
		sleep(1);
	}
	return NULL;
}

void* f2(void* a) {
	while (1) {
		pthread_mutex_lock(&mtx);
		printf("Read %d first time\n", n);
		printf("Read %d second time\n", n);
		pthread_mutex_unlock(&mtx);
		sleep(1);
	}
	return NULL;
}

int main(int argc, char* argv[]) {
	srand(time(0));
	pthread_mutex_init(&mtx, NULL);
	pthread_create(&t1, NULL, f1, NULL);
	pthread_create(&t2, NULL, f2, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_mutex_destroy(&mtx);
	return 0;
}
