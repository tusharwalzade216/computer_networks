#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>

void dg_cli(FILE *fp, int sockfd, struct sockaddr *psa, socklen_t slen) {
	int n;
	char s[80], r[80];
	
	while(fgets(s, 80, fp) != NULL) {
		sendto(sockfd, s, strlen(s), 0, psa, slen);
		n = recvfrom(sockfd, r, 80, 0, NULL, NULL);
		
		r[n] = 0;
		fputs(r, stdout);
	}
}

int main(int argc, char **argv) {
	int sockfd;
	struct sockaddr_in sa;
	
	if(argc != 2) {
		perror("IP tak na bhau...!");
		exit(1);
	}
	
	bzero(&sa, sizeof(sa));
	
	sa.sin_family = AF_INET;
	sa.sin_port = htons(6000);

	inet_pton(AF_INET, argv[1], &sa.sin_addr);
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	dg_cli(stdin, sockfd, (struct sockaddr *) &sa, sizeof(sa));
	exit(0);
}
