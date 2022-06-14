/*standard symbols */
#include <unistd.h>
#include <cstdlib>  

/*Aleatorios*/
#include <time.h>

/* sockets */
#include <netdb.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <arpa/inet.h>

/* strings / errors*/
#include <errno.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 

#define TAM_DEL_BUFFER 50
#define CANT_DE_CARACTERES 8
#ifndef _SERVIDOR_H_
#define _SERVIDOR_H_

class servidor {

    private:
        const char * server_address;
        int port;
        char buff_rx[TAM_DEL_BUFFER];
        char buff_tx[CANT_DE_CARACTERES];
        int sockfd;
        int connfd;
        int len_rx;
        int len_tx;
        unsigned int len;
        int usuarios;
        int cant_de_caracteres;

    public:

        servidor(const char * server_address, const int port);
        struct sockaddr_in Crear();
        int Enlazar(struct sockaddr_in servaddr);
        int Escuchar();
        int Aceptar_y_Interactuar();

        void GenerarPassword();
};

#endif
