#include "cupid/server.h"

int main(){
    cupid cu;
    cu.createServer();
    while (1) cu.listenToClients();
}
