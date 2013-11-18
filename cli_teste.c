//UDPClient.c
 
/*
 * gcc -o client UDPClient.c
 * ./client <server-ip>
 */
 
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include "struc_usuario.h"

#define BUFLEN 512
// #define PORT 9930
#define _XOPEN_SOURCE 500

 
void err(char *s)
{
    perror(s);
    exit(1);
}
 
int main(int argc, char** argv)
{
    struct sockaddr_in serv_addr;
    int sockfd, i, slen=sizeof(serv_addr);
    char buf[BUFLEN];
    int j, k;
    size_t namesize;
    char *name;
    char dns[128];
    int port = atoi(argv[2]);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
        err("socket");
    //getlogin_r(char *name, size_t namesize);
    //name = getlogin1();

    bzero(&serv_addr, sizeof(serv_addr));

//printf("%d\n", k);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if ( inet_aton( argv[1] , &serv_addr.sin_addr ) == 0 )
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
    /*for(j = 1; j < argc; j++){
        if (sendto(sockfd, argv[j], BUFLEN, 0, (struct sockaddr*)&serv_addr, slen)==-1)
            err("sendto()");
    }*/
    if(strcmp(argv[3], "register") == 0 ){
        
        if( argv[4] != NULL){
            sprintf(buf ,"R%s %s",argv[1],argv[4]);
            getlogin_r( argv[4], strlen( argv[4] ) );
        }else{
            name = getlogin();
            if( name != NULL)
                printf("Sem usuario %s\n", name);
            else{
                printf("Você não digitou um login anteriormente\n");
                exit(0);
            }
        } 
        

        if ( sendto(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&serv_addr, slen) == -1 )
            err("sendto()");
        
        // if (sendto(sockfd, argv[4], BUFLEN, 0, (struct sockaddr*)&serv_addr, slen)==-1)
        //     err("sendto()");
        //if (sendto(sockfd, name, namesize, 0, (struct sockaddr*)&serv_addr, slen)==-1)
          //  err("sendto()");
    }
    gethostname(dns, sizeof(dns));
    printf("%s\n", dns);
 
    close(sockfd);
    return 0;


}
