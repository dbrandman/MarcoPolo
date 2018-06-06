/**
 * @file
 * @brief MarcoPolo -- setting up rapid communication between processes using multicast / broadcast
 * @authors David Brandman
 *
 * MarcoPolo is a very lightweight library for initializings multicast sockets and facilitating communication
 * between multiple processes. The idea is that all of the participating processes share the same well known
 * IP and port, then they can start communicating rapidly.
 *
 * The API is very straightforward. The InitializeMarcoPolo() function sets up two file descriptors: one for
 * reading multicast messages, and the second for writing messages. The Initialize function binds the
 * first descriptor and connects the second one. The Broadcast() function writes to the connected socket,
 * and the receive blocks on the bind socket. When a message is received, it calls the callback function.
 */

#pragma once

#include <netinet/in.h>  // for struct sockaddr_in

int InitializeMarcoPolo(int fd[2], char *ip, int port);
int Broadcast(int fd, void *data, int dataSize);
int Receive(int fd, int (*callback)(void *data, int dataSize, void *callbackData, int nBytes), void *callbackData, int nBytes);
int PopulateSockaddr_in(struct sockaddr_in *addr, char *ip, int port);
void PrintSockaddr_in(struct sockaddr_in *addr);