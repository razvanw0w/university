#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <string.h>


int main() {
	int s, c, clientLength;
	struct sockaddr_in server, client;

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		printf("Socket error\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1337);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	if (bind(s, (struct sockaddr*) &server, sizeof(server)) < 0) {
		printf("Bind error\n");
		return 1;
	}

	listen(s, 5);
	clientLength = sizeof(client);
	memset(&client, 0, sizeof(client));

	char *message;
	while (1) {
		printf("Listening...\n");
		c = accept(s, (struct sockaddr*) &client, &clientLength);
		if (c < 0) {
			printf("Accept error\n");
			continue;
		}
		printf("Incoming connection: %s\n", inet_ntoa(client.sin_addr));
		uint16_t n;
		recv(c, &n, sizeof(n), MSG_WAITALL);
		n = ntohs(n);
		printf("n = %hu\n", n);
		message = (char*)malloc(sizeof(char) * n);
		recv(c, message, sizeof(message[0]) * n, MSG_WAITALL);
		message[n] = 0;
		printf("String: %s\n", message);

		int i, j;
		for (i = 0, j = n - 1; i < j; ++i, --j) {
			char aux = message[i];
			message[i] = message[j];
			message[j] = aux;
		}

		printf("Sending: %s\n", message);
		send(c, message, sizeof(message) * n, 0);
		free(message);
		close(c);
	}

	return 0;

}

