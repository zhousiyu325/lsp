/**
 * server program of lsp-chat 
 * by 	WHOAMI localhost purstar Atum
 * Oct 5 2016
 * version 1.0	
 **/

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	unsigned int my_port, lisnum;
	int sockfd, new_fd;
	socklen_t len;
	if (argv[2])
		my_port = atoi(argv[2]);
	else
		my_port = 7575;
	if (argv[3])
		lisnum = atoi(argv[3]);
	else
		lisnum = 5; 
	struct sockaddr_in server_addr, clients_addr;
	//create socket object
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0))==-1)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	//set server_addr 0
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(my_port);
	if (argv[1])
		server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	else
		server_addr.sin_addr.s_addr = INADDR_ANY;
	//bind the socket with ip and port
	if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr)) == -1)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
	//listern and wait for connecting
	if(listen(sockfd,lisnum) == -1)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	printf("wait for connect\n");
	len = sizeof(struct sockaddr);
	//get the client connection
	if((new_fd = accept(sockfd, (struct sockaddr *) &clients_addr, &len) == -1))
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}
	else
		printf("server: got connection from %s, port %d, socket %d\n",inet_ntoa(clients_addr.sin_addr),ntohs(clients_addr.sin_port),new_fd);
	return 0;
}

