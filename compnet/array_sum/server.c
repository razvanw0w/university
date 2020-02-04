#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

typedef int SOCKET;

int main() {
	SOCKET local, outerConnection;
	struct sockaddr_in server, client;
	int clientLength;

	local = socket(AF_INET, SOCK_STREAM, 0);
	if (local < 0) {
		printf("Error socket\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1337);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	if (bind(local, (struct sockaddr*) &server, sizeof(server)) < 0) {
		printf("Bind error\n");
		return 1;
	}

	listen(local, 5);
	clientLength = sizeof(client);
	memset(&client, 0, sizeof(client));
	
	while (1) {
		uint16_t n, sum = 0;
		printf("Listening...\n");
		outerConnection = accept(local, (struct sockaddr*) &client, &clientLength);
		if (outerConnection < 0) {
			printf("Error on accept\n");
			continue;
		}
		printf("Connected from %s\n", inet_ntoa(client.sin_addr));
		recv(outerConnection, &n, sizeof(n), MSG_WAITALL);
		n = ntohs(n);
		printf("n = %hu\n", n);
		
		int i;

		uint16_t *array = (uint16_t*)malloc(sizeof(uint16_t) * n);
		printf("Vector: ");
		for (i = 0; i < n; ++i) {
			recv(outerConnection, array + i, sizeof(array[i]), MSG_WAITALL);
			array[i] = ntohs(array[i]);
			sum += array[i];
			printf("%hu ", array[i]);
		}

		printf("\nSending sum = %d\n", sum);

		sum = htons(sum);
		send(outerConnection, &sum, sizeof(sum), 0);
		free(array);
		close(outerConnection);
	}

	return 0;
}
