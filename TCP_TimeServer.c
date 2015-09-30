#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<time.h>
int main()
{
	int listenfd,connfd;
	time_t ticks;
	char buf[80];
	struct sockaddr_in sa;
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	if(listenfd==-1)
	{
		perror("socket error");
		exit(1);
	}
	bzero(&sa,sizeof(sa));
	sa.sin_family=AF_INET;
	sa.sin_port=htons(13);
	sa.sin_addr.s_addr=htonl(INADDR_ANY);
	bind(listenfd,(struct sockaddr *)&sa,sizeof(sa));
	listen(listenfd,5);
	for(;;)
	{
		connfd=accept(listenfd,NULL,NULL);
		ticks=time(NULL);
		snprintf(buf,sizeof(buf),"%.24s\r\n",ctime(&ticks));
		printf("%s",buf);
		if( write( connfd, buf, strlen( buf)) < 0) 
		{
			fprintf( stderr, "write error\n");
		}
		close(connfd);
	}
}
