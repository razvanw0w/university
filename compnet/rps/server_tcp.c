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
#include <time.h>

void killChild(int sig) {
	wait(0);
}

void serveClient(int conn, struct sockaddr_in client) {
	printf("New client: %s\n", inet_ntoa(client.sin_addr));
	int i;
	int serverScore = 0, clientScore = 0;
	char labels[3][10] = {"rock", "scissors", "paper"};
	for (i = 0; i < 7; ++i) {
		int r = rand() % 3;
		int rNet = htonl(r);
		send(conn, &rNet, sizeof(rNet), 0);
		int clientDraw;
		recv(conn, &clientDraw, sizeof(clientDraw), 0);
		clientDraw = ntohl(clientDraw);
		int outcome;
		if (r == clientDraw) {
			outcome = htonl(0);
		}
		else if (r == 0) {
			if (clientDraw == 1) {
				outcome = htonl(-1);
			}
			else {
				outcome = htonl(1);
			}
		}
		else if (r == 1) {
			if (clientDraw == 0) {
				outcome = htonl(1);
			}
			else {
				outcome = htonl(-1);
			}
		}
		else {
			if (clientDraw == 0) {
				outcome = htonl(-1);
			}
			else {
				outcome = htonl(1);
			}
		}
		send(conn, &outcome, sizeof(outcome), 0);
		if (outcome == htonl(-1))
			++serverScore;
		else if (outcome == htonl(1))
			++clientScore;
		printf("Server = %s, %s = %s | Server %d-%d %s\n", labels[r],
														   inet_ntoa(client.sin_addr),
														   labels[clientDraw],
														   serverScore,
														   clientScore,
														   inet_ntoa(client.sin_addr));
	}
	printf("Final score: Server %d - %d %s\n", serverScore,
											   clientScore,
											   inet_ntoa(client.sin_addr));
	close(conn);
}

int main() {
	signal(SIGCHLD, killChild);
	srand(time(0));
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

	listen(soc, 10);

	int clientLength = sizeof client;
	memset(&client, 0, sizeof client);

	while (1) {
		int c = accept(soc, (struct sockaddr*) &client, &clientLength);
		if (c < 0) {
			printf("Bad connection\n");
			continue;
		}
		if (fork() == 0) {
			serveClient(c, client);
			exit(0);
		}
	}

	return 0;
}
