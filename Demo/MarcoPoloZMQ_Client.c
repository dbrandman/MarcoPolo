/** Demo: Client using MarcoPolo + ZeroMQ
 *
 *  MarcoPolo's `FindProcess` feature can be used in conjunction with ZMQ for a
 *  distributed messaging architecture that doesn't require hardcoding IP 
 *  addresses (in ZMQ).
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#include "MarcoPolo.h"
#include "FindProcess.h"

#define MP_SERVER_NAME 			"MPZ_SERVER"

#define MP_PROCESS_NAME 		"MPZ_CLIENT"
#define MP_PROCESS_IP 			"127.0.0.1"
#define MP_PROCESS_PORT 		7000
#define MP_MULTICAST_IP 		"239.1.1.1"
#define MP_MULTICAST_PORT 		5000

#define ZMQ_CONNECT_PROTOCOL 	"tcp://%s:%d"

int main(int argc, char *argv[])
{
	// set up MarcoPolo find process listener
	FindProcessStruct mpz_client = {0};
	if(InitializeFindProcessListener(&mpz_client, MP_PROCESS_NAME, \
		MP_MULTICAST_IP, MP_MULTICAST_PORT, MP_PROCESS_IP, MP_PROCESS_PORT))
	{
		printf("Could not initialize %s process listener.\n", MP_PROCESS_NAME);
		exit(1);
	}

	// find the server process using MarcoPolo
	struct sockaddr_in addr = {0};
	if(FindProcess(&mpz_client, MP_SERVER_NAME, &addr))
	{
		printf("MarcoPolo: FindProcess function failed.\n");
		exit(1);
	}

	// extract IP and port info from sockaddr_in struct
	char serverIP[32];
	snprintf(serverIP, sizeof(serverIP), ZMQ_CONNECT_PROTOCOL, \
		inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
	printf("Found server at %s\n", serverIP);

	printf("Press ENTER to start sending messages...\n");
	getchar();

	// connect to ZMQ server
	void *context = zmq_ctx_new();
	void *requester = zmq_socket(context, ZMQ_REQ);
	zmq_connect(requester, serverIP);

	int request_nbr;
	for(request_nbr = 0; request_nbr != 10; request_nbr++) {
		char buffer[10];
		printf("Sending Hello %d...\n", request_nbr);
		zmq_send(requester, "Hello", 5, 0);
		zmq_recv(requester, buffer, 10, 0);
		printf("Received World %d\n", request_nbr);
	}

	zmq_close(requester);
	zmq_ctx_destroy(context);
	
	return 0;
}