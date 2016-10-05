/**
 * server program of lsp-chat 
 * by 	WHOAMI localhost purstar
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
	unsigned int myport, lisnum;
	int sockfd, new_fd;
	socklen_t len;
	if (argv[2])
		myport = atoi(argv[2]);
	else
		myport = 7575;
	if (argv[3])
		lisnum = atoi(argv[3]);
	else
		lisnum = 5; 
	struct sockaddr_in server_addr, clients_addr;
	// create socket object
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(myport);
	if (argv[1])
		server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	else
		server_addr.sin_addr.s_addr = INADDR_ANY;
	bind(sockfd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr));
	listen(sockfd,lisnum);
	printf("wait for connect\n");
	len = sizeof(struct sockaddr);
	new_fd = accept(sockfd, (struct sockaddr *) &clients_addr, &len);
	printf("server: got connection from %s, port %d, socket %d\n",inet_ntoa(clients_addr.sin_addr),ntohs(clients_addr.sin_port),new_fd);
	return 0;
}

