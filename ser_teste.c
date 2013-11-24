//UDPServer.c
 
/* 
 *  gcc -o server UDPServer.c
 *  ./server
 */
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>   
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include "struc_usuario.h"
#include "utils.c"
#define BUFLEN 512 
void err(char *str)
{
    perror(str);
    exit(1);
}
 
int main(int argc, char **argv)
{
    struct sockaddr_in my_addr, cli_addr;
    int sockfd, i; 
    socklen_t slen = sizeof(cli_addr);
    char buf[BUFLEN];
    char buf2[BUFLEN];
    int port = atoi(argv[1]);
    int times;
    Tipo_Lista *usuariosAtivos;
    struct Tipo_Elemento *aux;
    usuariosAtivos = Lista_Vazia();   
    usuariosAtivos = Lista_Vazia();    
    char **dados;

    if ( ( sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP) ) == -1)
      err("socket");
    else
      printf("Server : Socket() successful\n");
 
    bzero(&my_addr, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons( port );
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
     
    if (bind(sockfd, (struct sockaddr* ) &my_addr, sizeof(my_addr))==-1)
      err("bind");
    else
      printf("Server : bind() successful\n");
 
    while(1)
    {
        if ( recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&cli_addr, &slen) == -1) err("recvfrom()");
        if( buf[0] == 'R' ){
            char *dados[5];
            char *result = NULL;
            int count = 0;
            result = strtok(buf, " ");
            while (result != NULL) {  
                dados[count] = result;
                result = strtok(NULL," ");
                count++;
            }
            aux = Busca_Elemento( usuariosAtivos , dados[3] );
            if( aux == NULL){ 
                Insere_Lista(usuariosAtivos , dados[1] , dados[2] , dados[3]);

            }else{  
                insereValores(aux , dados[1] , dados[2] );
                                
            }

            Imprime_Lista(usuariosAtivos); 
        }else if( buf[0] == 'D' ){
            char *dados[5];
            char *result = NULL;
            int count = 0;
            result = strtok(buf, " ");
            while (result != NULL) {  
                dados[count] = result;
                result = strtok(NULL," ");
                count++;
            }
            aux = Busca_Elemento( usuariosAtivos , dados[3] );
            if(aux == NULL){
                printf("Usuario nao tem registro de log\n");
                if (sendto(sockfd, "ERRO", BUFLEN, 0, (struct sockaddr*)&cli_addr, slen) == -1)
                err("sendto()");
                continue;
            }else if (aux->idCount == 1){
                Elimina_Elemento(usuariosAtivos, aux);
                if (sendto(sockfd, "Usuario nao possui mais conexoes", BUFLEN, 0, (struct sockaddr*)&cli_addr, slen) == -1)
                    err("sendto()");
            }else
                eliminaValores(aux , dados[1] , dados[2] );

            Imprime_Lista(usuariosAtivos); 

        }else if( buf[0] == 'P' ){
            char *dados[5];
            char *result = NULL;
            int count = 0;
            result = strtok(buf, " ");
            while (result != NULL) {  
                dados[count] = result;
                result = strtok(NULL," ");
                count++;
            }
            aux = Busca_Elemento(usuariosAtivos , dados[3] );          
            if(aux == NULL){
                printf("Usuario nao tem registro de log\n");
                if (sendto(sockfd, "ERRO", BUFLEN, 0, (struct sockaddr*)&cli_addr, slen) == -1)
                err("sendto()");
                continue;

            } 
            else if (sendto(sockfd, aux->ip[aux->idCount], BUFLEN, 0, (struct sockaddr*)&cli_addr, slen) == -1 )
                err("sendto()");
            else if (sendto(sockfd, aux->dns[aux->idCount], BUFLEN, 0, (struct sockaddr*)&cli_addr, slen) == -1 )
                err("sendto()");
        
            //char *dig = (char*)(((int)'0')+aux->idCount);
            char dig[BUFLEN];
            sprintf(dig, "%d", aux->idCount);
            if (sendto(sockfd, dig, BUFLEN, 0, (struct sockaddr*)&cli_addr, slen) == -1 )
                err("sendto()");
        }

    }
 
    close(sockfd);
    return 0;
}
