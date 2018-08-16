#include "FindProcess.h"
#include "MarcoPolo.h" // For PrintSockaddr_in
#include <stdio.h>
#include <stdlib.h>
int main()
{
	FindProcessStruct alice = {0};
	FindProcessStruct bob = {0};

	if( InitializeFindProcessListener(&alice, "ALICE", "239.1.1.1", 5000, "127.0.0.1", 60000)){
		printf("Could not initialize ProcessListener Alice\n");
		exit(1);
	}

	if ( InitializeFindProcessListener(&bob, "BOB", "239.1.1.1", 5000, "127.0.0.1", 7000)) {
		printf("Could not initialize ProcessListener Bob");
		exit(1);
	}

	// Give the threads a second to initialize!
	printf("Push a key to continue...\n");
	getchar();

	// Now populate the addr structure based on Bob's contact information
	struct sockaddr_in addr = {0};
	if(FindProcess(&alice, "BOB", &addr)){
		printf("Could not run FindProcess\n");
		exit(1);
	}

	// Print the result to screen! This should show 127.0.0.1 Port 7000
	PrintSockaddr_in(&addr);

	return 0;
}