// 1 global variable
// 5 threads - increment 10 times
// before incrementing it will print the current value and the new value

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

pthread_t t[5];
pthread_mutex_t mtx;
int n = 0;

void* f(void *a) {
	pthread_mutex_lock(&mtx);
	printf("Before incrementing: %d\n", n);
	int i;
	for (i = 0; i < 10; ++i)
		++n;
	printf("After incrementing: %d\n", n);
	pthread_mutex_unlock(&mtx);

	return NULL;
}

int main(int argc, char* argv[]) {
	int i;

	if (pthread_mutex_init(&mtx, NULL) != 0) {
		perror("Mutex init failed");
		exit(1);
	}

	for (i = 0; i < 5; ++i) {
		if (pthread_create(&t[i], NULL, f, NULL) != 0) {
			perror("Thread create failed");
			exit(2);
		}
	}

	for (i = 0; i < 5; ++i) {
		if (pthread_join(t[i], NULL) != 0) {
			perror("Thread joining failed");
			exit(3);
		}
	}

	pthread_mutex_destroy(&mtx);
	return 0;
}
