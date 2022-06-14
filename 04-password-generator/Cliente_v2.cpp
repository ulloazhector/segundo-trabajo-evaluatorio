#include "cliente.h"
#include <iostream>

using namespace std;

const char * server_address = "192.168.0.149";     /* server IP */
const int port = 8080;

int main(int argc, char const *argv[]){

	struct sockaddr_in servaddr;

	cliente cliente(server_address, port);

    servaddr = cliente.Crear();
    
    if (cliente.Conectar(cliente.GetSockfd(), servaddr) == 0){
    	
    	cliente.Interactuar();

    }    

    cliente.Cerrar();
	
	return 0;
}
