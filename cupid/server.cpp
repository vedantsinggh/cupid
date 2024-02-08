#include <iostream>
#include "server.h"
#include <sys/socket.h>

#define print(x) std::cout<<x<<std::endl

namespace cupid{
	Server::Server(){

	}
	Server::~Server(){

	}
	
	int Server::startServer(){
		int err_code = socket(AF_INET, SOCK_STREAM, 0);		
		return err_code;
	}

	void Server::getName(){
		print("THIS IS MY NAME!!");
	}
}
