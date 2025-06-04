#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define LISTEN_IP "127.0.0.1"
#define LISTEN_PORT 8080

int main(int argc, char const *argv[]) {
    int sockfd, n;
    socklen_t len;
    char buffer[1024];
    struct sockaddr_in servaddr, cliaddr;
    char *hello = "Hello from udp server";

    // Creating socket file descriptor
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;  // IPv4
    servaddr.sin_port = htons(LISTEN_PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, LISTEN_IP, &servaddr.sin_addr) <= 0) {
        printf("\nInvalid address or Address not supported \n");
        return -1;
    }

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        return -1;
    }

    printf("udp server started on port %d...\n", LISTEN_PORT);

    len = sizeof(cliaddr);

    n = recvfrom(sockfd, (char *)buffer, 1024, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
    buffer[n] = '\0';
    printf("message received from client peer: [length=%d bytes], [msg=%s]\n", n, buffer);

    n = sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM,
               (const struct sockaddr *)&cliaddr, len);
    printf("message sent to client peer: [length=%d bytes], [msg=%s]\n", n, hello);

    return 0;
}
