/*Test MarcoPolo built with FindProcess wrapper:

First, build MarcoPolo with the FindProcess wrapper:

    $ make include=FindProcess

Compile this script with the following command:

    $ gcc Example.c -o Example -Wl,-rpath=. -L. -I. -lmarcopolo -lpthread

*/

#include <stdio.h>
#include "FindProcess.h"
#include "MarcoPolo.h"

int main(int argc, char *argv[]) {

    struct sockaddr_in addr = {0};
    FindProcessStruct alice = {0};
    FindProcessStruct bob = {0};

    InitializeFindProcessListener(&alice, "ALICE", "239.1.1.1", 5000, "127.0.0.1", 60000);  
    InitializeFindProcessListener(&bob, "BOB", "239.1.1.1", 5000, "127.0.0.1", 7000);   

    // Sends out a request for Bob, and blocks until it's received
    FindProcess(&alice, "BOB", &addr);

    printf("Found process 'BOB' at:\n");
    PrintSockaddr_in(&addr);

    // Clean up...

    return 0;

}