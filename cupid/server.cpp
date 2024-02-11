#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include "server.h"

#define PORT 7410
#define BUFFER_SIZE 1024

void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

    int serverSocket, clientSocket;
    socklen_t clientLength;
    char buffer[BUFFER_SIZE];
    sockaddr_in serverAddr, clientAddr;
    int listOfClients[BUFFER_SIZE];
    short numberOfClient = 0;

    int cupid::createServer(){
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    
        // Set up server address struct
        memset((char *)&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(PORT);
        serverAddr.sin_addr.s_addr = INADDR_ANY;

        // Bind the socket to the address
        if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
            error("Error binding socket");
        }

        return serverSocket;
    }

    int cupid::listenToClients(){
        // Listen for incoming connections
        if (listen(serverSocket, 10) == -1) {
            error("Error listening for connections");
        }

        std::cout << "Server is listening on port " << PORT << "...\n";

        // Accept a connection
        clientLength = sizeof(clientAddr);
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientLength);
        if (clientSocket == -1) {
            error("Error accepting connection");
        }

        // listOfClients[numberOfClient] = clientSocket;
        // numberOfClient++;

        // Receive data from client
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead == -1) {
            error("Error receiving data");
        }

        // Print received message
        std::cout << "Received message from " << clientSocket << " : " << buffer << std::endl;

        // Send "Hello, World!" to the client
        const char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 5\n\nHello";
        int bytesSent = send(clientSocket, response, strlen(response), 0);
            std::cout << "SENT"<< std::endl;
        if (bytesSent == -1) {
            error("Error sending data");
        }

        // Close sockets
        close(clientSocket);
        close(serverSocket);

        return 0;
    }
