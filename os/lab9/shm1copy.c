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
	
	int *p = shmat(shmID, NULL, 0);

	printf("Reading %d\n", *p);

	shmdt(p);
	return 0;
}
