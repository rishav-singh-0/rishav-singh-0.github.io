#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> // 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>

pthread_t thread;

struct args {
  int socketfd;
  char* buf;
};

void error(char *msg)
{
    perror(msg);
    // printf("erno : %d\n",errno);
    // exit(0);
}

void * get_input(void* iArgs){
  struct args* args = (struct args*)iArgs;
  int n = 0;
  while(1){
    bzero(args->buf,256);
    printf("Enter msg for server: ");
    fgets(args->buf, 255, stdin);

    n = send(args->socketfd, args->buf, strlen(args->buf), 0);
    if (n < 0)
      error("ERROR writing to socket");
  }
  return NULL;
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

    bzero(write_buffer,256);
    struct args arg = {sockfd, write_buffer};
    pthread_create(&thread, NULL, get_input, (void*)&arg);

    while(1)
    {
        // if (n < 0) 
        //      error("ERROR writing to socket");
        bzero(read_buffer,256);
        // n = read(sockfd,read_buffer,255);
        n = recv(sockfd,read_buffer,255,0);
        // if (n < 0) 
        //      error("ERROR reading from socket");
        if (n > 0)
          printf("Server: %s",read_buffer);

        // printf("%s\n",read_buffer);
    }
    return 0;
}   