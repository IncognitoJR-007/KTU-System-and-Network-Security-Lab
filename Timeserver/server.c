#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<time.h>

int main(){
    int soket,len;
    socklen_t clielen;
    time_t currentTime;
    currentTime = time(NULL);
    char sendmsg[30];
    struct sockaddr_in servaddr,cliaddr;
    soket=socket(AF_INET,SOCK_DGRAM,0);
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(1508);
    bind(soket,(struct sockaddr*)&servaddr,sizeof(servaddr));
    printf("Server is waiting\n");
    clielen=sizeof(cliaddr);
    recvfrom(soket,sendmsg,sizeof(sendmsg),0,(struct sockaddr*)&cliaddr,&clielen);
    currentTime = time(NULL);
    sendmsg[0] = '\0';
    strcpy(sendmsg,ctime(&currentTime));
    printf("Client:%s\n",sendmsg);
    sendto(soket,sendmsg,strlen(sendmsg)+1,0,(struct sockaddr*)&cliaddr,clielen);

    
    
    return 0;
}
