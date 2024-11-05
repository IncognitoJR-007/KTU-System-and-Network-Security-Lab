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

        int len = strlen(msg);
        int is_palindrome = 1;
        for (int i = 0; i < len / 2; i++) {
            if (msg[i] != msg[len - i - 1]) {
                is_palindrome = 0;
                break;
            }
        }
        strcpy(msg, is_palindrome ? "Palindrome" : "Not Palindrome");
        send(nsd, msg, strlen(msg) + 1, 0);
    }
    return 0;
}
