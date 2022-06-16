#include <iostream>
#include <string>
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <sys/socket.h> 
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <unistd.h>

#define TAM_DEL_BUFFER 50
#ifndef _CLIENTE_H_
#define _CLIENTE_H_

using namespace std;

class Cliente {

    private:
        const char * server_address;
        int port;
        char buf_tx[TAM_DEL_BUFFER] = "Necesito una nueva password";
        char buf_rx[TAM_DEL_BUFFER];
        int sockfd;

    public:

        Cliente(const char * server_address, const int port);
        struct sockaddr_in crear();
        int conectar(int sockfd, struct sockaddr_in servaddr);
        void interactuar();
        void cerrar();
        int getSockfd();
};

#endif
