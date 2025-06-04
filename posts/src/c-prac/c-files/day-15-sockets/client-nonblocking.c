#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> // 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include<errno.h>


void error(char *msg)
{
    perror(msg);
    printf("erno : %d\n",errno);
    // exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;             /* The variable server is a pointer to a structure of type hostent. This structure is defined in the header file netdb.h */

    char read_buffer[256];   
    char write_buffer[256];   
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    server = gethostbyname(argv[1]);      /* argv[1] contains the name of a host on the Internet, e.g. cheerios@cs.rpi.edu. The function: */
    if (server == NULL) {                  // returns a pointer to a hostent containing information about that host. 
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }


    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    
    bcopy((char *)server->h_addr_list[0], (char *)&serv_addr.sin_addr.s_addr, server->h_length);

    serv_addr.sin_port = htons(portno);


    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    
    fcntl(sockfd, F_SETFL, fcntl(sockfd,F_GETFL) | O_NONBLOCK);

    while(1)
    {
        printf("Please enter the message: ");
        bzero(write_buffer,256);
        fgets(write_buffer,255,stdin);
        // n = write(sockfd,write_buffer,strlen(write_buffer));
        n = send(sockfd,write_buffer,strlen(write_buffer),0);
        if (n < 0) 
             error("ERROR writing to socket");
        bzero(read_buffer,256);
        // n = read(sockfd,read_buffer,255);
        n = recv(sockfd,read_buffer,255,0);
        if (n < 0) 
             error("ERROR reading from socket");
        printf("%s\n",read_buffer);
    }
    return 0;
}   