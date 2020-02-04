#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <time.h>

int main() {
	key_t key;
	key = ftok("a.c", 0);
	
	int shmID = shmget(key, 10, IPC_PRIVATE|IPC_CREAT|0600);
	if (shmID < 0) {
		perror("Error on shmget");
		exit(1);
	}
	int *p = (int*)malloc(sizeof(int));	
	p = shmat(shmID, NULL, 0);

	srand(time(0));
	int randomNumber = rand() % 101 + 100;
	printf("Sending random number = %d\n", randomNumber);
	*p = randomNumber;
	printf("Before detach\n");

	shmdt(p);
	return 0;
}
