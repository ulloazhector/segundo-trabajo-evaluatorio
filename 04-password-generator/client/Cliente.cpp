#include "Cliente.h"

Cliente::Cliente(const char *server_address, const int port) {
    this->server_address = server_address;
    this->port = port;
}

struct sockaddr_in Cliente::crear() {
    struct sockaddr_in servaddr;
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);

    cout << (this->sockfd == -1 
    ? "\033[1;31m[CLIENT]: Socket creation failed...\033[0m" 
    : "\033[1;32m[CLIENT]: Socket successfully created\033[0m") << endl;

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(this->server_address);
    servaddr.sin_port = htons(this->port);

    return servaddr;
}

int Cliente::conectar(int sockfd, struct sockaddr_in servaddr) {
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        cout << "\033[1;31mConnection with the server failed...\033[0m" << endl;
        return -1;
    }
    return 0;
}

void Cliente::interactuar() {
    cout <<"Connected to the server..." << endl;

    write(this->sockfd, this->buf_tx, sizeof(this->buf_tx));
    read(this->sockfd, this->buf_rx, sizeof(this->buf_rx));

    cout <<"\033[1m[CLIENT]:\033[0m Received: \033[1;36m" << this->buf_rx << "\033[0m" << endl;
}

void Cliente::cerrar() {
    close(this->sockfd);
}

int Cliente::getSockfd() {
    return (this->sockfd);
}
