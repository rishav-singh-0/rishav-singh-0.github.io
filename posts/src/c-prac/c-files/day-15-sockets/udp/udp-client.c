#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080

int main() {
    int sockfd, n;
    socklen_t len;
    char buffer[1024];
    struct sockaddr_in dest_addr, recv_addr;
    char *hello = "Hello from udp client";

    // Creating socket file descriptor
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&dest_addr, 0, sizeof(dest_addr));

    // Filling server information
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(SERVER_PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, SERVER_IP, &dest_addr.sin_addr) <= 0) {
        printf("\nInvalid address or Address not supported \n");
        return -1;
    }

    n = sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM,
               (const struct sockaddr *)&dest_addr, sizeof(dest_addr));
    printf("message sent to server peer: [length=%d bytes], [msg=%s]\n", n, hello);

    n = recvfrom(sockfd, (char *)buffer, 1024, MSG_WAITALL, (struct sockaddr *)&recv_addr, &len);
    buffer[n] = '\0';
    printf("message received from server peer: [length=%d bytes], [msg=%s]\n", n, buffer);

    close(sockfd);

    return 0;
}
