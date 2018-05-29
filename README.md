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
