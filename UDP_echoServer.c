#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

void dg_echo(int sockfd, struct sockaddr *pca, socklen_t clen) {
	socklen_t len;
	int n;
	char s[80];
	
	for( ; ; ) {
		len = clen;
		n = recvfrom(sockfd, s, 80, 0, pca, &len);
		
		sendto(sockfd, s, strlen(s), 0, pca, len);
	}
}

int main(int argc, char **argv) {
	int sockfd;
	struct sockaddr_in sa, ca;
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&sa, sizeof(sa));
	
	sa.sin_family = AF_INET;
	sa.sin_port = htons(6000);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	
	bind(sockfd, (struct sockaddr *) &sa, sizeof(sa));
	dg_echo(sockfd, (struct sockaddr *) &ca, sizeof(ca));
}
