# MarcoPolo
Simple wrapper for Multicasting sockets written in C

Have you ever wanted a bunch of processes on different computers to quickly find each other? Need something super-lightweight for embedded systems? MarcoPolo is a simple tool for having processes to quickly and efficiently exchange information on the same Multicast network. 

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

The InitializeMarcoPolo() function takes in a 2D array of integers, similar to the pipe() system call. 

Let's suppose Bob and Alice are processes that live on different computers, and they both have their own IPs and ports. What if Alice wants to find Bob's contact information, using only his name? Let's use findProcess, which is wrapped around MarcoPolo!
 

```C
struct sockaddr_in addr = {0};
FindProcessStruct alice = {0};
FindProcessStruct bob = {0};

InitializeFindProcessListener(&alice, "ALICE", "239.1.1.1", 5000, "127.0.0.1", 60000);	
InitializeFindProcessListener(&bob, "BOB", "239.1.1.1", 5000, "127.0.0.1", 7000);	

// Sends out a request for Bob, and blocks until it's received
FindProcess(&alice, "BOB", &addr); 
PrintSockaddr_in(&addr); // Prints: 127.0.0.1 Port 7000

```

## Watch out!
Make sure that you've enabled multicast on your device:
```
route add -net 224.0.0.0 netmask 240.0.0.0 dev lo
```
