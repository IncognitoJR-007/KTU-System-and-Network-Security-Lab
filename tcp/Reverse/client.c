#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main() {
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    char msg[30];
    struct sockaddr_in servaddr = {AF_INET, htons(1507), htonl(INADDR_ANY)};

    connect(sd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    while (1) {
        printf("Client: ");
        fgets(msg, 30, stdin);
        msg[strcspn(msg, "\n")] = '\0';
        if (!strcmp(msg, "exit")) break;
        send(sd, msg, strlen(msg) + 1, 0);
        recv(sd, msg, sizeof(msg), 0);
        for (int i = 0, j = strlen(msg) - 1; i < j; i++, j--) {
            char t = msg[i]; msg[i] = msg[j]; msg[j] = t;
        }
        printf("Server reversed message: %s\n", msg);
        send(sd, msg, strlen(msg) + 1, 0);
    }
    return 0;
}
