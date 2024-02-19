#include "server.h"
#define BUFFER_SIZE 1024

void error(const char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

int serverSocket;
sockaddr_in serverAddr;
int listOfClients[BUFFER_SIZE];
short cindex = 0;

int cupid::createServer(short port){
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	memset((char *)&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
		error("Error binding socket");
	}

	if (listen(serverSocket, 10) == -1) {
		error("Error listening for connections");
	}

	std::cout << "Server is listening on port " << port << "...\n";

	return serverSocket;
}

int cupid::listenToClients(){
	sockaddr_in clientAddr;
	socklen_t clientLength = sizeof(clientAddr);
	int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientLength);
	if (clientSocket == -1) {
		error("Error accepting connection");
	}	
	listOfClients[cindex] = clientSocket;
	cindex++;
	std::cout<<"client connected";
	return cindex;
}

int cupid::closeServer(){
	close(serverSocket);
	return 1;
}

int cupid::closeClient(){
	for (int i : listOfClients) close(i);
	return 1;
};

int cupid::closeClient(int index){
	close(index);
	return 1;
};

int cupid::sendMessage(int clientIndex, std::string message){	
	int bytesSent = send(clientIndex, message.c_str(), message.size(), 0);
		
	if (bytesSent == -1) {
		error("Error sending data");
	}
	return bytesSent;
};

int cupid::sendMessageAll(std::string message){
	for (int i = 0; i<cindex; i++){		
		int bytesSent = send(listOfClients[i], message.c_str(), message.size(), 0);
		if (bytesSent == -1) {
			error("Error sending data");
		}
	}
	return 1;
};

int cupid::receive(int index){
	char buffer[BUFFER_SIZE];
	int bytesRead = recv(listOfClients[index], buffer, sizeof(buffer), 0);
	if (bytesRead == -1) {
		error("Error receiving data");
	}

	std::cout << "Received message from " << index << " : " << buffer << std::endl;
	return 1;
}

int cupid::receiveAll(){
	for (int i = 0; i<cindex; i++)
	{
		receive(i);
	}
	return 1;
}

void cupid::printDetails(){
	std::cout << cindex;
}