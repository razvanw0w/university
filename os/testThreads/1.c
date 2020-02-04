#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int nrVocale, nrConsoane;
pthread_mutex_t mtxVocale = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtxConsoane = PTHREAD_MUTEX_INITIALIZER;

void* f(void* a) {
	char *s = (char*)a;
	char vowels[] = "aeiou";
	char consonants[] = "qwrtypsdfghjklzxcvbnm";

	int len = strlen(s), i;
	int v = 0, c = 0;
	for (i = 0; i < len; ++i) {
		if (strchr(vowels, s[i])) {
			++v;
		}
		else if (strchr(consonants, s[i])) {
			++c;
		}
	}
	pthread_mutex_lock(&mtxVocale);
	nrVocale += v;
	pthread_mutex_unlock(&mtxVocale);
	pthread_mutex_lock(&mtxConsoane);
	nrConsoane += c;
	pthread_mutex_unlock(&mtxConsoane);
	return NULL;
}

int main(int argc, char* argv[]) {
	pthread_t *th = (pthread_t*)malloc((argc - 1) * sizeof(pthread_t));

	int i;
	for (i = 1; i < argc; ++i) {
		pthread_create(&th[i - 1], NULL, f, (void*)argv[i]);
	}

	for (i = 0; i < argc - 1; ++i) {
		pthread_join(th[i], NULL);
	}

	printf("Vowels: %d\nConsonants: %d\n", nrVocale, nrConsoane);

	free(th);
	pthread_mutex_destroy(&mtxVocale);
	pthread_mutex_destroy(&mtxConsoane);
	return 0;
}
