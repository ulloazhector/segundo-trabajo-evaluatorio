#include "Servidor.h"

Servidor::Servidor(const char *server_address, int port) {
    this->server_address = server_address;
    this->port = port;
    this->len_tx = 0;
}

struct sockaddr_in Servidor::crear() {

    struct sockaddr_in servaddr;
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->sockfd == -1)
        fprintf(stderr, "\033[1;31m[SERVER-error]: socket creation failed. %d: %s \033[0m\n", errno, strerror(errno));
    else
        cout << "\033[1;32m[SERVER]: Socket successfully created\033[0m" << endl;

    /* clear structure */
    memset(&servaddr, 0, sizeof(servaddr));

    /* assign IP, SERV_PORT, IPV4 */
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(this->server_address);
    servaddr.sin_port = htons(this->port);

    return servaddr;
}

int Servidor::enlazar(struct sockaddr_in servaddr) {

    if ((bind(this->sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) {
        fprintf(stderr, "\033[1;31m[SERVER-error]: Socket bind failed. %d: %s \033[0m\n", errno, strerror(errno));
        return -1;
    }
    cout << "\033[1;32m[SERVER]: Socket successfully binded\033[0m" << endl;
    return 0;
}

int Servidor::escuchar() {

    if ((listen(this->sockfd, this->usuarios)) != 0) {
        fprintf(stderr, "\033[1;31m[SERVER-error]: Socket listen failed. %d: %s \033[0m\n", errno, strerror(errno));
        return -1;
    }
    cout << "\033[1;36m[SERVER]: Listening on SERV_PORT " << this->port << endl
         << "...\033[0m" << endl
         << endl;
    return 0;
}

void Servidor::generarPassword() {
    int password = rand() % 99999 + 100000;
    sprintf(this->buff_tx, "%d", password);
}

int Servidor::aceptarInteractuar() {
    struct sockaddr_in client;
    len = sizeof(client);
    /* Accept the data from incoming sockets in a iterative way */
    while (1) {
        this->connfd = accept(this->sockfd, (struct sockaddr *)&client, &(this->len));
        if (this->connfd < 0) {
            fprintf(stderr, "\033[1;31m[SERVER-error]: Connection not accepted. %d: %s \033[0m\n", errno, strerror(errno));
            return -1;
        } else {
            generarPassword();

            while (1) {
                this->len_rx = read(this->connfd, this->buff_rx, sizeof(this->buff_rx));
                if (this->len_rx == -1) {
                    fprintf(stderr, "\033[1;31m[SERVER-error]: Connfd cannot be read. %d: %s \033[0m\n", errno, strerror(errno));
                } else if (this->len_rx == 0) {
                    cout << "Password generado: \033[1;46m" << this->buff_tx << "\033[0m" << endl;
                    cout << "\033[1m[SERVER]:\033[0m Client socket closed" << endl
                         << endl;
                    close(this->connfd);
                    break;
                } else {
                    write(this->connfd, &this->buff_tx, sizeof(this->buff_tx));
                    cout << "\033[1m[CLIENT]:\033[0m " << this->buff_rx << endl;
                }
            }
        }
    }
}
