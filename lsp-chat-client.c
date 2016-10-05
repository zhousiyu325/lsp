/**
 * client program of chat
 * by localhost pur whoami
 * 0ct 5 2016 
 * version 1.0
 **/

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char **argv)
{
	int sockfd, len;
	struct sockaddr_in dest;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("socket created.\n");
	dest.sin_family = AF_INET;
	dest.sin_port = htons(atoi(argv[2]));
	inet_aton(argv[1], (struct in_addr *) &dest.sin_addr.s_addr);
	connect(sockfd, (struct sockaddr *) &dest, sizeof(dest));
	printf("server connected\n");
	return 0;
}

		
