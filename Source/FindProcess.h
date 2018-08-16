/** @file
  * @brief Discover another process by name, and receive its IP and port
  * @authors David Brandman
  */

#include <netinet/in.h>  // for struct sockaddr_in

#pragma once

#define MAX_PROCESS_LENGTH 32
#define MICROSECONDS_BETWEEN_BROADCASTS 500

typedef struct
{
	int fd[2];
	char name[MAX_PROCESS_LENGTH];
	struct sockaddr_in addr;

} FindProcessStruct;

typedef struct
{
 	char from[MAX_PROCESS_LENGTH];
 	char to[MAX_PROCESS_LENGTH];
    struct sockaddr_in addr; 

} ProcessInfo; 

/**
 *@brief Whenever someone searches for name, return the IP and port
 */
int InitializeFindProcessListener(FindProcessStruct *s, char *name, char *multicastIP, int multicastPort, char *ip, int port);

int FindProcess(FindProcessStruct *s, char *name, struct sockaddr_in *addr);