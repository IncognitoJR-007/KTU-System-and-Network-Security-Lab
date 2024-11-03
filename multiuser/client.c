#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

char msg[500];
void *recieve_message(void *sock){
    int client = *((int *)sock);
    int len;
    while((len = recv(client,msg,500,0)) > 0){
        msg[len] = '\0';
        printf("%s\n",msg);
    }
    return 0;
}

void main(){
    struct sockaddr_in server;
    pthread_t recvt;
    int client = 0,sock = 0;
    char sendmsg[30],clientname[30],tempmsg[60];
    printf("Enter your name:");
    scanf("%s",clientname);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8810);
    sock = socket(AF_INET,SOCK_STREAM,0);
    printf("Client Started\n");
    if(connect(sock,(struct sockaddr*)&server,sizeof(server)) < 0){
        printf("Connection failed\n");
        return;
    }
    pthread_create(&recvt,NULL,recieve_message,&sock);
    while(fgets(sendmsg,30,stdin) > 0){
        sprintf(tempmsg,"%s:%s",clientname,sendmsg);
        send(sock,tempmsg,strlen(tempmsg),0);

    }
    pthread_join(recvt,NULL);
    close(sock);
}
