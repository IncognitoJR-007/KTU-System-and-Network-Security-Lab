#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<pthread.h>

pthread_mutex_t mutex;
int clients[20];
int n =0;
void sendtoall(char *msg,int curr){
    int i;
    pthread_mutex_lock(&mutex);
    for(i=0;i<n;i++){
        if(clients[i] != curr){
            if(send(clients[i],msg,strlen(msg),0) < 0){
                printf("Failed to send message\n");
            }
        }
    }
    pthread_mutex_unlock(&mutex);
}

void *recvmg(void *sock){
    int client = *((int *)sock);
    char msg[500];
    int len;
    while((len = recv(client,msg,500,0)) > 0){
        msg[len] = '\0';
        sendtoall(msg,client);
    }
    return 0;
}

void main(){
    struct sockaddr_in server;
    pthread_t recvt;
    int client = 0,sock = 0;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8810);
    sock = socket(AF_INET,SOCK_STREAM,0);
    printf("Server Started\n");
    if(bind(sock,(struct sockaddr*)&server,sizeof(server)) < 0){
        printf("Binding failed\n");
        return;
    }
    listen(sock,20);
    while(1){
        if((client = accept(sock,NULL,NULL)) < 0){
            printf("Failed to accept client\n");
        }
        pthread_mutex_lock(&mutex);
        clients[n] = client;
        n++;
        pthread_create(&recvt,NULL,recvmg,&client);
        pthread_mutex_unlock(&mutex);
    }
    
}
