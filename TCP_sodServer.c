#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int sumOfDigit(int num) {
	int sum=0,rem=0;

 	while(num > 0) {
        	while(num != 0) {
                      rem = num%10;
                      sum = sum+rem;
                      num=num/10;
                }
								printf("%d\n",sum);	
                if(sum > 9) {
                        num = sum;
                        sum = 0;
                }
	}	
	return sum;
}

int main() {
			char str[100];
    	int listen_fd, comm_fd, s=0, sum=0, i=0;
 
    	struct sockaddr_in servaddr;
 
    	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
 
    	bzero( &servaddr, sizeof(servaddr));
 
    	servaddr.sin_family = AF_INET;
    	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    	servaddr.sin_port = htons(21090);
 
    	bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    	listen(listen_fd, 10);
    	comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
 
    	while(1) {
        	bzero( str, 100);
        	read(comm_fd,str,100);
  		    s = atoi(str);
		      printf("number recieved-->%d ", s);
		      sum = sumOfDigit(s);
		      sprintf(str, "%d ", sum);
        	write(comm_fd, str, strlen(str)+1);
    	}
			fflush(stdout);
    	return 0;
}
