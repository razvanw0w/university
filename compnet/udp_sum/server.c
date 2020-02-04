#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
	int serverSocket;
	struct sockaddr_in server, client;
	
	serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (serverSocket < 0) {
		printf("Error socket\n");
		return 1;
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(1337);
	server.sin_addr.s_addr = INADDR_ANY;

	int clientLength = sizeof(client);

	int res = bind(serverSocket, (struct sockaddr*) &server, sizeof(server));
	if (res < 0) {
		printf("Bind error\n");
		return 1;
	}
	int a, b;
	
	while (1) {	
		printf("Listen...\n");
		recvfrom(serverSocket, &a, sizeof(a), 0, (struct sockaddr*) &client, &clientLength);
		printf("Got a = %d!\n", htonl(a));
		recvfrom(serverSocket, &b, sizeof(b), 0, (struct sockaddr*) &client, &clientLength);
		printf("Got b = %d!\n", htonl(b));

		a = ntohl(a);
		b = ntohl(b);
		printf("ip = %s, a = %d, b = %d\n", inet_ntoa(client.sin_addr), a, b);
		int sum = a + b;
		sum = htonl(sum);
		sendto(serverSocket, &sum, sizeof(sum), 0, (struct sockaddr*) &client, sizeof(client));
	}
	return 0;
}
