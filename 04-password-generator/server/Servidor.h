/*standard symbols */
#include <cstdlib>
#include <unistd.h>

/*Aleatorios*/
#include <time.h>

/* sockets */
#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

/* strings / errors*/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_DEL_BUFFER 50
#define CANT_DE_CARACTERES 8
#ifndef _SERVIDOR_H_
#define _SERVIDOR_H_

using namespace std;

class Servidor {
private:
    const char *server_address;
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
    Servidor(const char *server_address, const int port);
    struct sockaddr_in crear();
    int enlazar(struct sockaddr_in servaddr);
    int escuchar();
    int aceptarInteractuar();
    void generarPassword();
};

#endif
