#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080

int main(int argc, char const *argv[]) {
    int sock = 0, read_bytes, write_bytes;
    struct sockaddr_in dest_addr;
    char *hello = "Hello from tcp client";
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(SERVER_PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, SERVER_IP, &dest_addr.sin_addr) <= 0) {
        printf("\nInvalid address or Address not supported \n");
        return -1;
    }

    printf("tcp client connecting to %s:%d\n", SERVER_IP, SERVER_PORT);

    if (connect(sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    write_bytes = send(sock, hello, strlen(hello), 0);
    printf("message sent to server: [length=%d bytes], [msg=%s]\n", write_bytes, hello);

    read_bytes = recv(sock, buffer, 1024, 0);
    printf("message received from server: [length=%d bytes], [msg=%s]\n", read_bytes, buffer);

    return 0;
}
