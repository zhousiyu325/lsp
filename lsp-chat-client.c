/**
 * client program of chat
 * by localhost pur whoami Atum
 * 0ct 5 2016 
 * version 1.0
 **/

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>

int main(int argc, char **argv)
{
	int sockfd, len;
	struct sockaddr_in dest;

	//1.create socket object
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		exit(errno);
	}
	printf("socket created.\n");
	//set dest 0
	bzero(&dest, sizeof(dest));
	//address protocal
	dest.sin_family = AF_INET;
	//the port of server
	dest.sin_port = htons(atoi(argv[2]));
	//get the ip of server
	if (inet_aton(argv[1], (struct in_addr *) &dest.sin_addr.s_addr) == 0)
	{
		perror(argv[1]);
		exit(errno);
	}
	//connect the server
	if(connect(sockfd, (struct sockaddr *) &dest, sizeof(dest)) == -1)
	{
		perror("connect");
		exit(errno);
	}
	printf("server connected\n");
	return 0;
}

		
