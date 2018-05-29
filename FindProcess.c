

#include "MarcoPolo.h"
#include "FindProcess.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <poll.h>

void *FindProcessListener(void *voidInput);
static void PrintFindProcessStruct(FindProcessStruct *fps);

int FindProcess(FindProcessStruct *s, char *name, struct sockaddr_in *addr)
{

	ProcessInfo incomingStruct = {0};
	ProcessInfo outgoingStruct = {0};

	strcpy(outgoingStruct.to, name);
	strcpy(outgoingStruct.from, s->name);

    struct pollfd toPoll = {.fd = s->fd[0], .events = POLLIN};
	while (1) {
		
		if (Broadcast(s->fd[1], &outgoingStruct, sizeof(ProcessInfo)))
			return -1;
	
		usleep(MICROSECONDS_BETWEEN_BROADCASTS);
		while(poll(&toPoll, 1, 0) > 0) {

			int nBytes = read(s->fd[0], &incomingStruct, sizeof(incomingStruct));

			if (nBytes < 0) {
				printf("[FindProcess] Error with reading : %s\n", strerror(errno));
				continue;
			}
			// First check to see if the struct is the correct length. If not, abort
			if (nBytes != sizeof(incomingStruct))
				continue;

			// Now check to see if the names match. If so, then respond. Set
			// the outgoingStruct to have the .to field from the sender, and then
			// Re-broadcast the information
			if (strcmp(incomingStruct.to, s->name) == 0 ) {
				memcpy(addr, &incomingStruct.addr,sizeof(struct sockaddr_in));
				return 0;
			}
		}
	}	
}


int InitializeFindProcessListener(FindProcessStruct *fps, char *name, char *multicastIP, int multicastPort, char *ip, int port)
{
	// Initialize MarcoPolo given the Multicast information
	int fd[2];
	if(	InitializeMarcoPolo(fd, multicastIP, multicastPort) )
		return -1;

	// Populate the FindProcessStruct that is both returned and used for the thread
	memcpy(fps->fd, fd, sizeof(int) * 2);
	strcpy(fps->name, name);
	PopulateSockaddr_in(&fps->addr, ip, port);

    pthread_t initializeFindProcessListenerThread;
    pthread_create(&initializeFindProcessListenerThread, NULL, &FindProcessListener, fps);

    return 0;
}

void *FindProcessListener(void *voidInput)
{
	FindProcessStruct *fps = (FindProcessStruct *) voidInput;

	ProcessInfo incomingStruct = {0};
	ProcessInfo outgoingStruct = {0};

	// Pre-populate the outgoingStruct
	strcpy(outgoingStruct.from, fps->name);
	memcpy(&outgoingStruct.addr, &fps->addr, sizeof(struct sockaddr_in));

	while (1) {
		int nBytes = read(fps->fd[0], &incomingStruct, sizeof(incomingStruct));

		if (nBytes < 0)
		{
			printf("[FindProcessListener] Error with reading: %s\n", strerror(errno));
			continue;
		}
		// First check to see if the struct is the correct length. If not, abort
		if (nBytes != sizeof(incomingStruct))
			continue;

		// Now check to see if the names match. If so, then respond. Set
		// the outgoingStruct to have the .to field from the sender, and then
		// Re-broadcast the information
		if (strcmp(incomingStruct.to, fps->name) == 0 ) {

			strcpy(outgoingStruct.to, incomingStruct.from);
			Broadcast(fps->fd[1],&outgoingStruct, sizeof(outgoingStruct));	
		}
	}	
}

static void PrintFindProcessStruct(FindProcessStruct *fps)
{
	printf("Name %s, FD: (%d, %d)\n", fps->name, fps->fd[0], fps->fd[1]);
}
