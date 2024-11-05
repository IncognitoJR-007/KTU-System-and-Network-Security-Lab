#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>

long factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

int main() {
    int sd, len, num;
    socklen_t clilen;
    char msg[30];
    struct sockaddr_in servaddr, cliaddr;

    sd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(1508);
    bind(sd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    clilen = sizeof(cliaddr);

    while (1) {
        len = recvfrom(sd, msg, sizeof(msg), 0, (struct sockaddr*)&cliaddr, &clilen);
        msg[len] = '\0';
        if (!strcmp(msg, "exit")) break;

        num = atoi(msg);
        sprintf(msg, "%ld", factorial(num));
        sendto(sd, msg, strlen(msg) + 1, 0, (struct sockaddr*)&cliaddr, clilen);
        
        recvfrom(sd, msg, sizeof(msg), 0, (struct sockaddr*)&cliaddr, &clilen); // Wait for client response
        printf("Client: %s\n", msg);
    }
    return 0;
}
