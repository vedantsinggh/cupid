#include "cupid/server.h"

int main(){
	cupid cu;
	cu.createServer(5050);
	while (1)
	{
		cu.listenToClients();
		cu.receiveAll();
	}
}
