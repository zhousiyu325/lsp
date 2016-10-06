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
#include <netdb.h>  
#include <net/if.h>  
#include <sys/ioctl.h>  
#include <sys/types.h>

#define MAXBUF 1024
#define MAC_SIZE    18  
#define IP_SIZE     16  

// get ip by domain  
int get_ip_by_domain(const char *domain, char *ip)  
{  
	char **pptr;  
   	struct hostent *hptr;   
 	hptr = gethostbyname(domain);  
   	if(NULL == hptr)  
   	{  
        	printf("gethostbyname error for host:%s/n", domain);  
       		return -1;  
    	}  
    	for(pptr = hptr->h_addr_list ; *pptr != NULL; pptr++)  
        	if (NULL != inet_ntop(hptr->h_addrtype, *pptr, ip, IP_SIZE) )   
            		return 0; 
    	return -1;  
} 

int main(int argc, char **argv)
{
	int sockfd, len;
	struct sockaddr_in dest;

   	 char buffer[MAXBUF + 1];
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
	char ip[IP_SIZE];
	get_ip_by_domain(argv[1], ip);
	//get the ip of server
	if (inet_aton(ip, (struct in_addr *) &dest.sin_addr.s_addr) == 0)
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

	printf("pls send message to send:");
	fgets(buffer,MAXBUF,stdin);
	send(sockfd,buffer,strlen(buffer) - 1, 0);
	return 0;
}

		
