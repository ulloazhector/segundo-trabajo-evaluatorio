#include "Cliente.h"
#include <iostream>

using namespace std;

int main(int argc, const char **argv){

	struct sockaddr_in servaddr;

	Cliente cliente(argv[1], stoi(argv[2]));

    servaddr = cliente.crear();
    if (cliente.conectar(cliente.getSockfd(), servaddr) == 0)
    	cliente.interactuar();
    
    cliente.cerrar();
	
	return 0;
}
