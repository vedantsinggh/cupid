#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <string>
#include <string.h>

#define BUFFER_SIZE 1024

void error(const char *msg);

class cupid{

public:
	int serverSocket;
	sockaddr_in serverAddr;
	int listOfClients[BUFFER_SIZE];
	short cindex = 0;

	int createServer(short port);

	int listenToClients();

	int closeServer();
		
	int closeClient();

	int closeClient(int clientIndex);
		
	int sendMessage(int clientIndex, std::string Message);

	int sendMessageAll(std::string message);
	
	int receive(int index);

	int receiveAll();

	void printDetails();
};
