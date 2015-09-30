#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
int main(int argc,char **argv)
{
	int sockfd,n;
	char s[80];
	struct sockaddr_in sa;
	if(argc!=2)
	{
		printf("\nusage:./a.out <server's IP address>");
		exit(1);
	}
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		perror("socket error");
		exit(1);
	}
	bzero(&sa,sizeof(sa));
	sa.sin_family=AF_INET;
	sa.sin_port=htons(13);
	inet_pton(AF_INET,argv[1],&sa.sin_addr);
	connect(sockfd,(struct sockaddr *)&sa,sizeof(sa));
	while((n=read(sockfd,s,80))>0)
	{
		s[n]=0;
		fputs(s,stdout);
	}
	if(n<0)
	close(sockfd);
}
