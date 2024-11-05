#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main() {
    int csd, len;
    char sendmsg[30], recvmsg[30];
    socklen_t clienten;
    struct sockaddr_in servaddr;

    csd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(1508);
    clienten = sizeof(servaddr);

    while (1) {
        printf("Client: ");
        fgets(sendmsg, 30, stdin);
        sendto(csd, sendmsg, strlen(sendmsg) + 1, 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
        if (!strcmp(sendmsg, "exit\n")) break;

        len = recvfrom(csd, recvmsg, sizeof(recvmsg), 0, (struct sockaddr*)&servaddr, &clienten);
        recvmsg[len] = '\0';
        printf("Server: %s\n", recvmsg);

        sendto(csd, sendmsg, strlen(sendmsg) + 1, 0, (struct sockaddr*)&servaddr, sizeof(servaddr)); // Send back to server
    }
    return 0;
}
