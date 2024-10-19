#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main(){
    int sd,nsd,le,clielen;
    char sendmsg[30],recvmsg[30];
    struct sockaddr_in servaddr,cliaddr;
    sd=socket(AF_INET,SOCK_STREAM,0);
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(1507);
    connect(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    printf("Connected to server\n");
    while(1){
        printf("Client:");
        fgets(sendmsg,30,stdin);
        send(sd,sendmsg,strlen(sendmsg)+1,0);
        if(strcmp(sendmsg,"exit")==0){
            break;
        }
        recv(sd,recvmsg,sizeof(recvmsg),0);
        printf("Server:%s\n",recvmsg);
    }
    return 0;
}
