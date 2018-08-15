/**
@brief MarcoPolo -- a tool for rapidly multicasting / broadcasting information to multiple processes
@authors David Brandman

*/

#include <errno.h>
#include <arpa/inet.h> // for the inet() call for populating structs and such
#include <sys/socket.h> // socket() creation
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "MarcoPolo.h"

/** The buffer for receiving new messages has a default buffer size */
#define DEFAULT_RECEIVE_BUFFER_SIZE 2048


int InitializeMarcoPolo(int fd[2], char *ip, int port)
{
	// Populate the sockaddr_in structure given the ip and port
	struct sockaddr_in addr = {0};
	if (PopulateSockaddr_in(&addr, ip, port))
		return -1;

	int enable = 1;
	// Both sockets must be initialized, set reusable, and then multicast enabled
	for (int i = 0; i < 2; i++)
	{
		// Initialize the socket
		fd[i] = socket(AF_INET, SOCK_DGRAM, 0);
		if (fd[i] < 0) {
			printf("Could not create socket %d: %s\n", fd[i], strerror(errno));
			return -1;	
		}

		// Make the socket reusable
		if (setsockopt(fd[i], SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {   
			printf("Setsockopt(SO_REUSEADDR) for socket %d: %s\n", fd[i], strerror(errno));
			return -1; 
		}   

		// Enable multicast
		struct sockaddr_in *multiLocal = (struct sockaddr_in *) &addr;
		struct ip_mreq mreq;
		mreq.imr_multiaddr.s_addr = multiLocal->sin_addr.s_addr;
		mreq.imr_interface.s_addr = htonl(INADDR_ANY);
		if(setsockopt(fd[i], IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
			printf("Establishing multicast for socket %d: %s\n", fd[i], strerror(errno));
			return -1;
		}
	}

	// Bind the first socket
	if(bind(fd[0], (const struct sockaddr *) &addr, sizeof(struct sockaddr_in)) < 0) { 
		printf("Bind AF_INET socket: %s\n", strerror(errno)); 
		return -1; 
	}

	// Connect the second socket
	if(connect(fd[1], (const struct sockaddr *) &addr, sizeof(struct sockaddr_in))) {
		printf("Connect AF_INET: %s\n", strerror(errno));
		return -1;
	}

	return 0;
}

/** 

*/
int Broadcast(int fd, void *data, int dataSize)
{
	int n = send(fd, data, dataSize, 0);
	if (n < 0) {
		printf("Could not send: %s\n", strerror(errno));
	}
	return n;	
}

/** 

*/
int Receive(int fd, int (*callback)(void*, int, void*, int), void *callbackData, int nBytes) 
{
	char buffer[DEFAULT_RECEIVE_BUFFER_SIZE] = {0};
    int n = read(fd, buffer, DEFAULT_RECEIVE_BUFFER_SIZE);
	if (n < 0) {
		printf("Could not read: %s\n", strerror(errno));
		return n;
	}
	
	return callback(buffer, n, callbackData, nBytes); 
}

/** 

*/
int PopulateSockaddr_in(struct sockaddr_in *addr, char *ip, int port)
{
    if(ip == NULL)
        return -1;

    addr->sin_family      = AF_INET;
    addr->sin_addr.s_addr = inet_addr(ip);
    addr->sin_port        = htons(port);

    return 0;
}

void PrintSockaddr_in(struct sockaddr_in *addr)
{
    printf("AF_INET IP  : %s Port: %d\n", inet_ntoa(addr->sin_addr), ntohs(addr->sin_port));  
}
