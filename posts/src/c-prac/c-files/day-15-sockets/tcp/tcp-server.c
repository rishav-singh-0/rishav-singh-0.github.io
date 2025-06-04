#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define LISTEN_IP "127.0.0.1"
#define LISTEN_PORT 8080

int main(int argc, char const *argv[]) {
    int server_fd, new_socket, n;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from tcp server";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return -1;
    }

    // Forcefully attaching socket to the PORT
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        return -1;
    }
    address.sin_family = AF_INET;
    address.sin_port = htons(LISTEN_PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, LISTEN_IP, &address.sin_addr) <= 0) {
        printf("\nInvalid address or Address not supported \n");
        return -1;
    }

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return -1;
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        return -1;
    }

    printf("tcp server listening on port %d...\n", LISTEN_PORT);

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("accept");
        return -1;
    }

    n = recv(new_socket, buffer, 1024, 0);
    printf("message received from client: [length=%d bytes], [msg=%s]\n", n, buffer);

    n = send(new_socket, hello, strlen(hello), 0);
    printf("message sent to client: [length=%d bytes], [msg=%s]\n", n, hello);

    return 0;
}
