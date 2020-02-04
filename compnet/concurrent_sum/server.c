#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>

void killChild(int sig) {
	wait(0);
}

void serveClient(int conn) {
	uint16_t a = 10, b = 10;
	recv(conn, &a, sizeof a, MSG_WAITALL);
	recv(conn, &b, sizeof b, MSG_WAITALL);
	a = ntohs(a);
	b = ntohs(b);
	while (a + b != 0) {
		printf("a = %hu, b = %hu\n", a, b);
		uint16_t sum = a + b;
		sum = htons(sum);
		send(conn, &sum, sizeof sum, 0);
		recv(conn, &a, sizeof a, MSG_WAITALL);
		recv(conn, &b, sizeof b, MSG_WAITALL);
		a = ntohs(a);
		b = ntohs(b);
	}
	printf("Ended connection with someone\n");
	close(conn);
}

int main() {
	signal(SIGCHLD, killChild);
	int soc;
	struct sockaddr_in server, client;
	
	soc = socket(AF_INET, SOCK_STREAM, 0);
	if (soc < 0) {
		printf("Bad socket\n");
		return 1;
	}

	memset(&server, 0, sizeof server);
	server.sin_port = htons(1337);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	if (bind(soc, (struct sockaddr*) &server, sizeof server) < 0) {
		printf("Bad bind\n");
		return 1;
	}

	listen(soc, 5);

	int clientLength = sizeof client;
	memset(&client, 0, sizeof client);

	while (1) {
		int c = accept(soc, (struct sockaddr*) &client, &clientLength);
		if (c < 0) {
			printf("Bad connection\n");
			continue;
		}
		if (fork() == 0) {
			serveClient(c);
		}
	}

	return 0;
}
