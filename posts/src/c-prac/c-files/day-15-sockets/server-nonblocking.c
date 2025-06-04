#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>     // contains constants and structures needed for internet domain addresses.
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <pthread.h>

pthread_t thread;

#define PORT 8080

void error(char *msg)
{
  perror(msg);
  printf("%s\n", strerror(errno));
  // exit(1);
}

void * get_input(char buf[]){
    printf("Enter msg for client: ");
    fgets(buf, 255, stdin);
	return NULL;
}

int main(int argc, char const* argv[]){
  int socketfd, newsocketfd;  // file descriptors
  int portno; // stores the port number on which the server accepts connections
  int clilen; // stores the size of the address of the client. This is needed for the accept system call
  int n; // contains the number of characters read or written

  char buffer_in[256];  // server reads characters from the socket connection into this buffer
  char buffer_out[256];  // server writes characters to the client
  
  struct sockaddr_in serv_addr, cli_addr; // A sockaddr_in is a structure containing an internet address. 
  
  if (argc < 2) {
    fprintf(stderr,"ERROR, no port provided\n");
    exit(1);
  }
  
  socketfd = socket(AF_INET, SOCK_STREAM, 0); 
  if (socketfd < 0) 
    error("ERROR opening socket");

  
  bzero((char *) &serv_addr, sizeof(serv_addr));

  portno = atoi(argv[1]);
  // portno = atoi("8080");

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(portno);
  serv_addr.sin_addr.s_addr = INADDR_ANY;

  // Forcefully attaching socket to the port 8080
  int opt = 1;
  if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEADDR, &opt, sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  if (bind(socketfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR on binding");

  listen(socketfd,5);

  clilen = sizeof(cli_addr);
  // printf("Before accept: %d\n", cli_addr.sin_addr.s_addr);
  newsocketfd = accept(socketfd, (struct sockaddr *) &cli_addr, &clilen);
  // printf("After accept: %d\n", cli_addr.sin_addr.s_addr);
  if (newsocketfd < 0) 
    error("ERROR on accept");

  // Add the Non-Blocking param to the socket.
  fcntl(newsocketfd, F_SETFL, fcntl(newsocketfd,F_GETFL) | O_NONBLOCK);

  while(1){
    
    // clearing buffers
    bzero(buffer_in,256);
    bzero(buffer_out,256);
	// pthread_create(&thread, NULL, get_input, buffer_out);

    printf("Enter msg for client: ");
    fgets(buffer_out, 255, stdin);

    n = recv(newsocketfd,buffer_in,255, 0);
    if (n < 0)
      error("ERROR reading from socket");
    printf("Client: %s",buffer_in);

    // n = write(newsocketfd, buffer_out, strlen(buffer_out));
    n = send(newsocketfd, buffer_out, strlen(buffer_out), 0);
    if (n < 0)
      error("ERROR writing to socket");

  }
//   pthread_join(thread, NULL);
  return 0; 
}