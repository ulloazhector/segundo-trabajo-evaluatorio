#include "servidor.h"

    servidor::servidor(const char * server_address, int port){

                this->server_address = server_address;

                this->port = port;

                this->usuarios = 5;

                this->len_tx = 0;            

    }

    struct sockaddr_in servidor::Crear(){

            struct sockaddr_in servaddr;

            this->sockfd = socket(AF_INET, SOCK_STREAM, 0); 
            
            if (this->sockfd == -1) { 
            
                fprintf(stderr, "[SERVER-error]: socket creation failed. %d: %s \n", errno, strerror( errno ));
            
                //Aca habia un return
            
            } else {
                
                printf("[SERVER]: Socket successfully created..\n"); 
            
            }
            
            /* clear structure */
            memset(&servaddr, 0, sizeof(servaddr));
          
            /* assign IP, SERV_PORT, IPV4 */
            servaddr.sin_family = AF_INET; 
            servaddr.sin_addr.s_addr = inet_addr(this->server_address); 
            servaddr.sin_port = htons(this->port); 
            
            return servaddr;

    }

    int servidor::Enlazar(struct sockaddr_in servaddr){

            if ((bind(this->sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) {

                fprintf(stderr, "[SERVER-error]: socket bind failed. %d: %s \n", errno, strerror( errno ));
          
                return -1;
            
            } else {
            
                printf("[SERVER]: Socket successfully binded \n");

                return 0;
            
            }

    }

    int servidor::Escuchar(){

        if ((listen(this->sockfd, this->usuarios)) != 0) { 
            
            fprintf(stderr, "[SERVER-error]: socket listen failed. %d: %s \n", errno, strerror( errno ));
            
            return -1;
        
        } else {

            printf("[SERVER]: Listening on SERV_PORT %d \n\n", ntohs(this->port) ); 
        
            return 0;

        }

    }

    void servidor::GenerarPassword(){

            int password = rand() % 99999 + 100000; 

            sprintf(this->buff_tx, "%d", password);            

    }
  
    int servidor::Aceptar_y_Interactuar(){

            struct sockaddr_in client; 

            len = sizeof(client); 
          
              /* Accept the data from incoming sockets in a iterative way */
              while(1) {
                
                this->connfd = accept(this->sockfd, (struct sockaddr *)&client, &(this->len)); 
                
                if (this->connfd < 0){ 
                
                    fprintf(stderr, "[SERVER-error]: connection not accepted. %d: %s \n", errno, strerror( errno ));
                
                    return -1;
                
                } else {              
                
                    GenerarPassword();

                    printf("%s\n",this->buff_tx );
                    
                    while(1) {  
                        
                        this->len_rx = read(this->connfd, this->buff_rx, sizeof(this->buff_rx));  
                        
                        if(this->len_rx == -1){
                       
                            fprintf(stderr, "[SERVER-error]: connfd cannot be read. %d: %s \n", errno, strerror( errno ));
                        
                        } else if(this->len_rx == 0) {
                        
                            printf("[SERVER]: client socket closed \n\n");
                        
                            close(this->connfd);
                        
                            break; 
                        
                        } else {
                            
                            write(this->connfd, &this->buff_tx, sizeof(this->buff_tx));
                            
                            printf("[SERVER]: %s \n", this->buff_rx);
                        
                        }            
                    }  
                }                      
            }

    }
