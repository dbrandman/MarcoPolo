# MarcoPolo
Simple wrapper for Multicasting sockets written in C

Have you ever wanted a bunch of processes on different computers to quickly find each other? Need something super-lightweight for embedded systems? MarcoPolo is a simple tool for having processes to quickly and efficiently exchange information on the same Multicast network. 



## Usage
Suppose we would like all of the processes in our system to exchange information at IP 224.1.1.1 port 5000. This is where MarcoPolo comes in:

```C
int fd[2];
if( InitializeMarcoPolo(fd, "224.1.1.1", 5000) ) { 
    printf("Could not initialize MarcoPolo\n");
    exit(1);
}   

// Let's send a message to everyone at a known IP and port!
char myMessage[] = "HELLO!";
int sentBytes = Broadcast(fd[1], myMessage, strlen(myMessage));
if (sentBytes < 0) {
    printf("Could not send message!\n");
}   

// Let's receive messages!
Receive(fd[0], callback, NULL, 0); 
```

The callback() function can do something nice, like print the message!

```C
int callback(void *data, int dataSize, void *callbackData, int nBytes)
{   
    printf("Received %d bytes: %s\n", dataSize, (char*) data);
    return 0;
}
```

The InitializeMarcoPolo() function takes in an array of integers (length 2), similar to the pipe() system call. 



### Finding other processes by name
Let's suppose Bob and Alice are processes that live on different computers, and they both have their own IPs and ports. What if Alice wants to find Bob's contact information, using only his name? Enter `FindProcess`, which is included in this repo. `FindProcess` wraps MarcoPolo, handling basic process name-based handshaking.

```C
struct sockaddr_in addr = {0};
FindProcessStruct alice = {0};
FindProcessStruct bob   = {0};

InitializeFindProcessListener(&alice, "ALICE", "239.1.1.1", 5000, "127.0.0.1", 60000);	
InitializeFindProcessListener(&bob, "BOB", "239.1.1.1", 5000, "127.0.0.1", 7000);	

// Sends out a request for Bob, and blocks until it's received
FindProcess(&alice, "BOB", &addr); 
PrintSockaddr_in(&addr); // Prints: 127.0.0.1 Port 7000
```



### Watch out!
Make sure that you've enabled multicast on your device:
```
route add -net 224.0.0.0 netmask 240.0.0.0 dev lo
```



## Building the library

### MarcoPolo
In the root MarcoPolo/ folder run:

```shell
make build
```

The built shared library will be placed in the Build/ folder.



## Demos
There are some examples available that showcase MarcoPolo in different use-cases. This is still a work in progress, so more examples will be added in the future. Pull-requests with new examples welcome!

Please note that some of the demos have dependencies, which need to be installed first. The dependencies are:
* [ZeroMQ](http://zeromq.org/)

To build the examples, in the root MarcoPolo/ folder run:

```shell
make demo
```

The demos will be built and placed into Demo/Build/.


## Test
In the root MarcoPolo/ folder, run:

```shell
make test
```

The tests will be built and placed into Test/Build/.



## Using the MarcoPolo in your own code
When compiling your own code with MarcoPolo, you have two options.

### Build with source
Compile the MarcoPolo source directly into your project (i.e. don't use the shared library):

```shell
gcc \
    MyProcess.c -o MyProcess -I/path/to/MarcoPolo \
    /path/to/MarcoPolo.c /path/to/FindProcess.c \
    -lpthread
```

You only need to include the FindProcess.c file if you're using its functionality.


### Install library system-wide (requires super-user permissions)
To build and then install (or update) the shared library, run (requires super-user permissions):

```shell
make build
make install
```

Now, to compile your project, use the following `gcc` command:

```shell
gcc MyProcess.c -o MyProcess -lmarcopolo -lpthread
```

Please note that your code should now include the MarcoPolo header files like so:

```C
#include <MarcoPolo.h>
#include <FindProcess.h>
```

To uninstall MarcoPolo, run `make uninstall` (requires super-user permissions).