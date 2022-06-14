#include "cliente.h"
        
        cliente::cliente(const char * server_address, const int port){
            
                this->server_address = server_address;

                this->port = port;


        
//                this->buf_rx = (char *) malloc (100 * sizeof(char));

        }

        struct sockaddr_in cliente::Crear(){
        
            struct sockaddr_in servaddr; 

            this->sockfd = socket(AF_INET, SOCK_STREAM, 0); 
            
            if (this->sockfd == -1){ 
            
                    printf("CLIENT: socket creation failed...\n"); 

                    // Aca habia un return  
            
            } else {
            
                    printf("CLIENT: Socket successfully created..\n"); 
            
            }
 
                    memset(&servaddr, 0, sizeof(servaddr));

                
            servaddr.sin_family = AF_INET; 
            servaddr.sin_addr.s_addr = inet_addr( this->server_address ); 
            servaddr.sin_port = htons(this->port); 

            return servaddr;
        }


        int cliente::Conectar(int sockfd, struct sockaddr_in servaddr){

            if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) { 
            
                printf("connection with the server failed...\n");  
                return -1;
            
            } else {
            
                return 0;
            
            }

        }


        void cliente::Interactuar(){

            printf("connected to the server..\n"); 
          
            /* send test sequences*/
            write(this->sockfd, this->buf_tx, sizeof(this->buf_tx));     
            read(this->sockfd, this->buf_rx, sizeof(this->buf_rx));

            printf("CLIENT:Received: %s \n", this->buf_rx);

        }

        void cliente::Cerrar(){

            close(this->sockfd);

        }

        int cliente::GetSockfd(){
        
                return (this->sockfd);
        
        }
