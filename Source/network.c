#include "network.h"
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>

int create_listingport(int port)
{

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        printf("Failed to Create the socket");
        return 0;
    }
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if (bind(fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        printf("bind failed\n");
        close(fd);
        return -1;
    }
    return fd;
}
int requestaccept(int socketid)
{
    struct sockaddr_in addr;
    socklen_t length = sizeof(addr);
    int connectedsocket = accept(socketid, (struct sockaddr *)&addr, &length);
    if (connectedsocket < 0)
    {
        printf("connection failed \n");
        return -1;
    }
    printf("connection is established\n");
    return connectedsocket;
}
