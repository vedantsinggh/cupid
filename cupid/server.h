#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

void error(const char *msg);

class cupid{

public:
    int serverSocket, clientSocket;
    socklen_t clientLength;
    char buffer[BUFFER_SIZE];
    sockaddr_in serverAddr, clientAddr;
    int listOfClients[BUFFER_SIZE];
    short numberOfClient;

    int createServer();

    int listenToClients();

    int closeServer();
};
