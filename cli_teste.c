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
#define _XOPEN_SOURCE 500

#define NI_MAXHOST 1025
#define NI_MAXSERV 32
 

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
    char buf2[BUFLEN];
    int j, k;
    size_t namesize;
    char *name;
    char dns[128];
    int port = atoi(argv[2]);

    int s;
    struct sockaddr_in my;
    socklen_t addressLength = sizeof(struct sockaddr_in);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
        err("socket");  


    bzero(&serv_addr, sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if ( inet_aton( argv[1] , &serv_addr.sin_addr ) == 0 )
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }


    if(strcmp(argv[3], "register") == 0 ){
        
        connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

        if (getsockname(sockfd, (struct sockaddr *)&my, &addressLength) == -1) {
          perror("getsockname() failed");
          return -1;
        } 
        char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV]; 
        if ( getnameinfo((struct sockaddr*)&my, sizeof(my) , hbuf, sizeof(hbuf), sbuf,sizeof(sbuf),0) == 0){
            if( argv[4] != NULL)
                sprintf(buf ,"R %s %s %s", inet_ntoa(my.sin_addr) ,hbuf,argv[4]); 
            else
                sprintf(buf ,"R %s %s %s", inet_ntoa(my.sin_addr) ,hbuf,getlogin());
        } 
        if ( sendto(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&serv_addr, slen) == -1 )
            err("sendto()");
    }


    if(strcmp(argv[3], "deregister") == 0 ){
        connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

        if (getsockname(sockfd, (struct sockaddr *)&my, &addressLength) == -1) {
          perror("getsockname() failed");
          return -1;
        } 

        char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV]; 
        if ( getnameinfo((struct sockaddr*)&my, sizeof(my) , hbuf, sizeof(hbuf), sbuf,sizeof(sbuf),0) == 0){
            if( argv[4] != NULL)
                sprintf(buf ,"D %s %s %s", inet_ntoa(my.sin_addr) ,hbuf,argv[4]); 
            else
                sprintf(buf ,"D %s %s %s", inet_ntoa(my.sin_addr) ,hbuf,getlogin());
        } 

        if ( sendto(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&serv_addr, slen) == -1 )
            err("sendto()");
    }  

    if(strcmp(argv[3], "query") == 0 ){
        connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

        if (getsockname(sockfd, (struct sockaddr *)&my, &addressLength) == -1) {
          perror("getsockname() failed");
          return -1;
        } 
        char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV]; 
        if ( getnameinfo((struct sockaddr*)&my, sizeof(my) , hbuf, sizeof(hbuf), sbuf,sizeof(sbuf),0) == 0){
            if( argv[4] != NULL)
                sprintf(buf ,"P %s %s %s", inet_ntoa(my.sin_addr) ,hbuf,argv[4]); 
            else
                sprintf(buf ,"P %s %s %s", inet_ntoa(my.sin_addr) ,hbuf,getlogin());
        } 

        if (sendto(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&serv_addr, slen) == -1 )
            err("sendto()");
        
        for(k = 0; k < 3; k++){
            if (recvfrom(sockfd, buf2, BUFLEN, 0, (struct sockaddr*)&serv_addr, &slen) == -1)
                err("recvfrom()");
            printf("%s\n", buf2);
            if(strcmp(buf2, "ERRO") == 0)
                exit(0);

        }
    } 
    close(sockfd);
    return 0;


}
