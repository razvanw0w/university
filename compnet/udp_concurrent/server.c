#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void killChild(int sig) {
	wait(0);
}

void serveClient(int port) {
	int s = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in server, client;

	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = INADDR_ANY;
	
	bind(s, (struct sockaddr*) &server, sizeof(server));
	int a = -1, b = -1;
	int len = sizeof(client);
	while (a + b != 0) {
		recvfrom(s, &a, sizeof(a), 0, (struct sockaddr*) &client, &len);
		printf("a = %d, ip = %s\n", ntohl(a), inet_ntoa(client.sin_addr));
		recvfrom(s, &b, sizeof(b), 0, (struct sockaddr*) &client, &len);
		printf("b = %d, ip = %s\n", ntohl(b), inet_ntoa(client.sin_addr));
	
		a = ntohl(a);
		b = ntohl(b);
		int sum = a + b;
		sum = htonl(sum);
		sendto(s, &sum, sizeof(sum), 0, (struct sockaddr*) &client, sizeof(client));
	}
	printf("Over with ip = %s\n", inet_ntoa(client.sin_addr));
}

int main() {
	signal(SIGCHLD, killChild);
	int gateKeeperPort = 1337;
	int realPort = 1337;

	struct sockaddr_in gateKeeperServer, gateKeeperClient;
	int s;

	gateKeeperServer.sin_family = AF_INET;
	gateKeeperServer.sin_port = htons(gateKeeperPort);
	gateKeeperServer.sin_addr.s_addr = INADDR_ANY;

	s = socket(AF_INET, SOCK_DGRAM, 0);
	
	bind(s, (struct sockaddr*) &gateKeeperServer, sizeof(gateKeeperServer));

	int req;
	int len = sizeof(gateKeeperClient);
	while (1) {
		recvfrom(s, &req, sizeof(req), 0, (struct sockaddr*) &gateKeeperClient,
				 &len);
		req = ntohl(req);
		if (req == 1) {
			++realPort;
			printf("Request to gatekeeper! IP = %s PORT = %d\n",
				   inet_ntoa(gateKeeperClient.sin_addr), realPort);
			if (fork() == 0) {
				int port = htonl(realPort);
				sendto(s, &port, sizeof(port), 0, (struct sockaddr*) &gateKeeperClient,
					   sizeof(gateKeeperClient));
				serveClient(realPort);
				exit(0);
			}
		}
	}

	return 0;
}
