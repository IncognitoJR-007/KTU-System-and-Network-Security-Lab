#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
void main(){
    int sd,len;
    socklen_t clielen;
    char sendmsg[30],recvmsg[30];
    struct sockaddr_in servaddr,cliaddr;
    sd=socket(AF_INET,SOCK_DGRAM,0);
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(1508);
    bind(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    printf("Server is waiting\n");
    clielen=sizeof(cliaddr);
    while(1){
        len=recvfrom(sd,recvmsg,sizeof(recvmsg),0,(struct sockaddr*)&cliaddr,&clielen);
        recvmsg[len]='\0';
        printf("Client:%s\n",recvmsg);
        printf("Server:");
        fgets(sendmsg,30,stdin);
        sendto(sd,sendmsg,strlen(sendmsg)+1,0,(struct sockaddr*)&cliaddr,clielen);
        if(strcmp(sendmsg,"exit")==0){
            break;
        }
    }
}
