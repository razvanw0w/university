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


int main() {
	uint16_t gateKeeperPort = 1337;
	uint16_t myPort;

	struct sockaddr_in gateKeeperServer;
	int s;

	gateKeeperServer.sin_family = AF_INET;
	gateKeeperServer.sin_port = htons(gateKeeperPort);
	gateKeeperServer.sin_addr.s_addr = inet_addr("10.152.2.171");

	s = socket(AF_INET, SOCK_DGRAM, 0);

	int req;
	int len = sizeof(gateKeeperServer);
	sendto(s, &req, sizeof(req), 0, (struct sockaddr*) &gateKeeperServer,
													   sizeof(gateKeeperServer));

	recvfrom(s, &myPort, sizeof(myPort), 0, (struct sockaddr*) &gateKeeperServer,
			 &len);
	myPort = ntohs(myPort);
	printf("Received port = %hu\n", myPort);
	gateKeeperServer.sin_port = htons(myPort);
	int i;

	int serverScore = 0, clientScore = 0;
	int serverHand = 1, myHand;

	bind(s, (struct sockaddr*) &gateKeeperServer, len);
	sendto(s, &serverHand, sizeof(serverHand), 0, (struct sockaddr*) &gateKeeperServer, len);
	for (i = 0; i < 7; ++i) {
		printf("Rock = 0, Scissors = 1, Paper = 2. Choose: ");
		scanf("%d", &myHand);
		myHand = htonl(myHand);
		sendto(s, &myHand, sizeof(myHand), 0, (struct sockaddr*) &gateKeeperServer,
			   sizeof(gateKeeperServer));
		recvfrom(s, &serverHand, sizeof(serverHand), 0, (struct sockaddr*) &gateKeeperServer,
				 &len);
		serverHand = ntohl(serverHand);
		printf("serverHand: %d\n", serverHand);
		int outcome;
		recvfrom(s, &outcome, sizeof(outcome), 0, (struct sockaddr*) &gateKeeperServer,
			     &len);
		outcome = ntohl(outcome);
		if (outcome == 0) {
			printf("Tie!\n");
		}
		else if (outcome == -1) {
			printf("Server wins!\n");
			++serverScore;
		}
		else {
			printf("You win!\n");
			++clientScore;
		}
		printf("Server %d - %d Me\n", serverScore, clientScore);
	}
	return 0;
}
