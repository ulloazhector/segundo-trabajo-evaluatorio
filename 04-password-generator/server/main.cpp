#include "Servidor.h"
#include <iostream>

using namespace std;

// const char *server_address = "192.168.0.105"; /* server IP */
// int port = 8080;

int main(int argc, const char **argv) {

    struct sockaddr_in servaddr;

    Servidor servidor(argv[1], stoi(argv[2]));

    servaddr = servidor.crear();

    if (servidor.enlazar(servaddr) == 0)
        if (servidor.escuchar() == 0)
            servidor.aceptarInteractuar();

    return 0;
}