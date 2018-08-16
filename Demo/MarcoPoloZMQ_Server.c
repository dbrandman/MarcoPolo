/** Demo: Client using MarcoPolo + ZeroMQ
 *
 *  MarcoPolo's `FindProcess` feature can be used in conjunction with ZMQ for a
 *  distributed messaging architecture that doesn't require hardcoding IP 
 *  addresses (in ZMQ).
 */

#include <stdio.h>
#include <stdlib.h>

#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#include "MarcoPolo.h"
#include "FindProcess.h"

#define MP_PROCESS_NAME 	"MPZ_SERVER"
#define MP_PROCESS_IP 		"127.0.0.1"
#define MP_PROCESS_PORT 	6000
#define MP_MULTICAST_IP 	"239.1.1.1"
#define MP_MULTICAST_PORT 	5000

#define ZMQ_PROTOCOL 		"tcp://%s:%d"

int main(int argc, char *argv[])
{
	// set up MarcoPolo find process listener
	FindProcessStruct mpz_server = {0};
	if(InitializeFindProcessListener(&mpz_server, MP_PROCESS_NAME, \
		MP_MULTICAST_IP, MP_MULTICAST_PORT, MP_PROCESS_IP, MP_PROCESS_PORT))
	{
		printf("Could not initialize %s process listener.\n", MP_PROCESS_NAME);
		exit(1);
	}

	// build serverIP from constants
	char serverIP[32];
	snprintf(serverIP, sizeof(serverIP), ZMQ_PROTOCOL, \
		MP_PROCESS_IP, MP_PROCESS_PORT);

	// create a ZMQ socket to talk to connecting clients
	void *context = zmq_ctx_new();
	void *responder = zmq_socket(context, ZMQ_REP);
	int rc = zmq_bind(responder, serverIP);
	assert(rc == 0);

	printf("Server bound on %s, waiting for clients...\n", serverIP);

	while(1)
	{
		char buffer[10];
		zmq_recv(responder, buffer, 10, 0);
		printf("Received Hello\n");
		sleep(1);  // do some work
		zmq_send(responder, "World", 5, 0);
	}

	return 0;
}