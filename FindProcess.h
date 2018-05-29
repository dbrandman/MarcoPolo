 /* @file
 * @brief Discover another process by name, and receive its IP and port
 * @authors David Brandman
 */

/*
 * OK, so what's gotta happen? First we have to Use MarcoPolo to set up our addresses.
 * Note that we should have a name of the current process somewhere. We should also have a declaration
 * of the name and the IP to be sent back. So maybe the structure looks something like this:
 *
 * typdef struct {
 * 		char from[32];
 * 		char to[32];
 *      struct sockaddr_in inetStruct; 
 * } ProcessInfo; 
 */


 #include <netinet/in.h>  // for struct sockaddr_in

#pragma once

#define MAX_PROCESS_LENGTH 32
#define MICROSECONDS_BETWEEN_BROADCASTS 500

typedef struct {

	int fd[2];
	char name[MAX_PROCESS_LENGTH];
	struct sockaddr_in addr;

} FindProcessStruct;

 typedef struct {
 	char from[MAX_PROCESS_LENGTH];
 	char to[MAX_PROCESS_LENGTH];
    struct sockaddr_in addr; 
} ProcessInfo; 

//typedef struct {

	//int fd[2];
	//struct sockaddr_in addr;
	//char name[MAX_PROCESS_LENGTH];

//} FindProcessListenerStruct;

/**
 *@brief Whenever someone searches for name, return the IP and port
 */
int InitializeFindProcessListener(FindProcessStruct *s, char *name, char *multicastIP, int multicastPort, char *ip, int port);

int FindProcess(FindProcessStruct *s, char *name, struct sockaddr_in *addr);


