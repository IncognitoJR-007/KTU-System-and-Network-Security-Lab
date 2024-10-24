#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int factorial(int n) {
    if (n == 0) return 1;
    return n * factorial(n - 1);
}

int main(){
    int sd;
    char sendmsg[30], recvmsg[30];
    struct sockaddr_in servaddr;
    
    sd = socket(AF_INET, SOCK_STREAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(1507);
    connect(sd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    
    printf("Connected to server\n");
    
    while(1){
        printf("Client: ");
        fgets(sendmsg, 30, stdin);
        
        if (strncmp(sendmsg, "fact", 4) == 0) { // Client requests factorial
            int num = atoi(sendmsg + 5);
            sprintf(sendmsg, "fact %d", num);
            send(sd, sendmsg, strlen(sendmsg) + 1, 0);
            recv(sd, recvmsg, sizeof(recvmsg), 0);
            printf("Server: %s\n", recvmsg);
        } else {
            send(sd, sendmsg, strlen(sendmsg) + 1, 0);
            recv(sd, recvmsg, sizeof(recvmsg), 0);
            printf("Server: %s\n", recvmsg);
            if (strcmp(sendmsg, "exit\n") == 0) break;
        }
    }
    return 0;
}
