#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

void main()
{
    int sd, num = 1;
    socklen_t addrien;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[100];
    
    // Create socket
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    
    // Configure server address
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(1508);
    
    // Configure client address
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    cliaddr.sin_port = htons(1508);
    
    // Bind socket to client address
    bind(sd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
    
    printf("Client is running...\n");
    
    // Get start time
    
    // Send request to server
    sendto(sd, &num, sizeof(num), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
    addrien = sizeof(cliaddr);
    
    // Receive response from server
    recvfrom(sd, &buffer, sizeof(buffer), 0, (struct sockaddr *)&cliaddr, &addrien);
    
    
    
    // Print server's time
    printf("Server's Time: %s\n", buffer);
}
