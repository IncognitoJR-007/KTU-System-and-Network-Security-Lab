#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main() {
    int sd = socket(AF_INET, SOCK_STREAM, 0), nsd;
    char msg[30];
    struct sockaddr_in servaddr = {AF_INET, htons(1507), htonl(INADDR_ANY)}, cliaddr;

    bind(sd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    listen(sd, 5);
    nsd = accept(sd, (struct sockaddr*)&cliaddr, &(int){sizeof(cliaddr)});
    while (1) {
        recv(nsd, msg, sizeof(msg), 0);
        if (!strcmp(msg, "exit")) break;
        for (int i = 0, j = strlen(msg) - 1; i < j; i++, j--) {
            char t = msg[i]; msg[i] = msg[j]; msg[j] = t;
        }
        send(nsd, msg, strlen(msg) + 1, 0);
        recv(nsd, msg, sizeof(msg), 0);
        printf("Client reversed message: %s\n", msg);
    }
    return 0;
}
