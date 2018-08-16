#include "MarcoPolo.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int callback(void *data, int dataSize, void *callbackData, int nBytes)
{
	printf("Received %d bytes: %s\n", dataSize, (char*) data);
	return 0;
}

int main()
{
	// Initialize MarcoPolo. 
	// The first file descriptor is for reading; the second for writing
	int fd[2];
	if( InitializeMarcoPolo(fd, "224.1.1.1", 5000) ) {
		printf("Could not initialize MarcoPolo\n");
		exit(1);
	}

	// Now send a message!
	char myMessage[] = "HELLO!";
	int sentBytes = Broadcast(fd[1], myMessage, strlen(myMessage));
	if (sentBytes < 0) {
		printf("Could not send message!\n");
	}

	// Receive the message and print it to screen
	printf("Send message! Bytes: %d \n", sentBytes);
	Receive(fd[0], callback, NULL, 0); 	

	exit(0);
}