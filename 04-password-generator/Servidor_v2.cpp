#include "servidor.h"
#include <iostream>

using namespace std;

const char * server_address = "192.168.0.104";     /* server IP */

int port = 8080;


int main(int argc, char const *argv[]){

	struct sockaddr_in servaddr;

	servidor servidor(server_address, port);

    servaddr = servidor.Crear();
    
    if (servidor.Enlazar(servaddr) == 0){
    	
    	    if (servidor.Escuchar() == 0){
    	
    			servidor.Aceptar_y_Interactuar();

    		}  

    }    
	
	return 0;
}
