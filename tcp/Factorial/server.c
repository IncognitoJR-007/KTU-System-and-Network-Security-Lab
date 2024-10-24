#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int factorial(int n) {
    if (n == 0) return 1;
    return n * factorial(n - 1);
}

void main(){
    int sd, nsd, clielen;
    char sendmsg[30], recvmsg[30];
    struct sockaddr_in servaddr, cliaddr;
    
    sd = socket(AF_INET, SOCK_STREAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(1507);
    bind(sd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    listen(sd, 5);
    
    printf("Server is waiting\n");
    clielen = sizeof(cliaddr);
    nsd = accept(sd, (struct sockaddr*)&cliaddr, &clielen);
    printf("Connected to client\n");
    
    while(1){
        recv(nsd, recvmsg, sizeof(recvmsg), 0);
        printf("Client: %s\n", recvmsg);
        
        if (strncmp(recvmsg, "fact", 4) == 0) { // Client requests factorial
            int num = atoi(recvmsg + 5);
            sprintf(sendmsg, "%d", factorial(num));
            send(nsd, sendmsg, strlen(sendmsg) + 1, 0);
        } else {
            printf("Server: ");
            fgets(sendmsg, 30, stdin);
            send(nsd, sendmsg, strlen(sendmsg) + 1, 0);
            if (strcmp(sendmsg, "exit\n") == 0) break;
        }
    }
}
