#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>

void dg_cli(FILE *fp, int sockfd, const struct sockaddr *psa, socklen_t slen) {
	int n;
	char s[80], r[81];
	connect(sockfd, (struct sockaddr *) psa, slen);
	while(fgets(s, 80, fp) != NULL) {
		write(sockfd, s, strlen(s));
		n = read(sockfd, r, 80);
		r[n] = 0;			//null terminate
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
	sa.sin_port = htons(6001);

	inet_pton(AF_INET, argv[1], &sa.sin_addr);
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	dg_cli(stdin, sockfd, (struct sockaddr *) &sa, sizeof(sa));
	exit(0);
}
