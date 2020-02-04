#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>

const int port = 1337;


int main() {
	int sock, connection;
	struct sockaddr_in server, client;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		printf("Socket create error\n");
		return 1;
	}
	memset(&server, 0, sizeof server);
	server.sin_port = htons(port);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	if (bind(sock, (struct sockaddr*) &server, sizeof(server)) < 0) {
		printf("Bind error\n");
		return 1;
	}

	listen(sock, 5);
	int clientLength = sizeof(client);
	memset(&client, 0, clientLength);


	printf("Server is on!\n");
	while (1) {
		uint32_t a, b, sum;
		connection = accept(sock, (struct sockaddr*) &client, &clientLength);
		if (connection < 0) {
			printf("accept conn error\n");
			continue;
		}
		printf("Client connected from %s\n", inet_ntoa(client.sin_addr));
		int result = recv(connection, &a, sizeof(a), MSG_WAITALL);
		if (result != sizeof(a)) {
			printf("Bad transmission a\n");
		}
		result = recv(connection, &b, sizeof(b), MSG_WAITALL);
		if (result != sizeof(b)) {
			printf("Bad transmission b\n");
		}

		a = ntohl(a);
		b = ntohl(b);
		printf("Received a = %d b = %d\n", a, b);
		sum = a + b;
		printf("Sending a + b = %d\n", sum);
		sum = htonl(sum);
		result = send(connection, &sum, sizeof(sum), 0);
		if (result != sizeof(sum)) {
			printf("Bad transmission sum\n");
		}
		close(connection);
	}

	return 0;
}
