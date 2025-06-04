// Server side C/C++ program to demonstrate Socket
// programming
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>     // contains constants and structures needed for internet domain addresses.
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

/*
This function is called when a system call fails. It displays a message about
the error on stderr and then aborts the program.
*/
void error(char *msg)
{
  perror(msg);
  exit(1);
}

int main(int argc, char const* argv[]){
  int socketfd, newsocketfd;  // file descriptors
  int portno; // stores the port number on which the server accepts connections
  int clilen; // stores the size of the address of the client. This is needed for the accept system call
  int n; // contains the number of characters read or written

  char buffer_in[256];  // server reads characters from the socket connection into this buffer
  char buffer_out[256];  // server writes characters to the client
  
  struct sockaddr_in serv_addr, cli_addr; // A sockaddr_in is a structure containing an internet address. 
  /*
    struct sockaddr_in {
            short   sin_family;     // contains a code for the address family
            u_short sin_port;       // port number
            struct  in_addr sin_addr;
            char    sin_zero[8];
    };
  An in_addr structure, defined in the same header file, contains only one
  field, a unsigned long called s_addr. The variable serv_addr will contain the
  address of the server, and cli_addr will contain the address of the client
  which connects to the server. 
  */
  
  if (argc < 2) {
    fprintf(stderr,"ERROR, no port provided\n");
    exit(1);
  }
  
  socketfd = socket(AF_INET, SOCK_STREAM, 0); 
  if (socketfd < 0) 
    error("ERROR opening socket");

  /*
  The socket() system call creates a new socket. It takes three arguments. The
  first is the address domain of the socket.  AF_INET stands for IPV4

  The second argument is the type of socket.
    - SOCK_STREAM: TCP(reliable, connection oriented)
    - SOCK_DGRAM: UDP(unreliable, connectionless)

  The third argument is the protocol. If this argument is zero (and it always
  should be except for unusual circumstances), the operating system will choose
  the most appropriate protocol. It will choose TCP for stream sockets and UDP
  for datagram sockets.

  The socket system call returns an entry into the file descriptor table (i.e.
  a small integer). This value is used for all subsequent references to this
  socket. If the socket call fails, it returns -1. In this case the program
  displays and error message and exits. However, this system call is unlikely
  to fail.

  */
  
  bzero((char *) &serv_addr, sizeof(serv_addr));
  /*
  The function bzero() sets all values in a buffer to zero. It takes two
  arguments, the first is a pointer to the buffer and the second is the size of
  the buffer. Thus, this line initializes serv_addr to zeros.
  */

  portno = atoi(argv[1]);

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(portno);
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  // printf("%d\n", INADDR_ANY);

  /*
  The second field of serv_addr is unsigned short sin_port , which contain the
  port number. However, instead of simply copying the port number to this
  field, it is necessary to convert this to network byte order using the
  function htons() which converts a port number in host byte order to a port
  number in network byte order.

  The third field of sockaddr_in is a structure of type struct in_addr which
  contains only a single field unsigned long s_addr. This field contains the IP
  address of the host. For server code, this will always be the IP address of
  the machine on which the server is running, and there is a symbolic constant
  INADDR_ANY which gets this address.
  */

  if (bind(socketfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR on binding");

  /*
  The bind() system call binds a socket to an address, in this case the address
  of the current host and port number on which the server will run. It takes
  three arguments, the socket file descriptor, the address to which is bound,
  and the size of the address to which it is bound. 
  The second argument is a pointer to a structure of type sockaddr, but what is
  passed in is a structure of type sockaddr_in, and so this must be cast to the
  correct type. This can fail for a number of reasons, the most obvious being
  that this socket is already in use on this machine.
  */

  listen(socketfd,5);
  /*
  The listen system call allows the process to listen on the socket for
  connections. The first argument is the socket file descriptor, and the second
  is the size of the backlog queue, i.e., the number of connections that can be
  waiting while the process is handling a particular connection. If the first
  argument is a valid socket, this call cannot fail, and so the code doesn't
  check for errors.
  */

  clilen = sizeof(cli_addr);
  newsocketfd = accept(socketfd, (struct sockaddr *) &cli_addr, &clilen);
  if (newsocketfd < 0) 
    error("ERROR on accept");

  /*
  The accept() system call causes the process to block until a client connects
  to the server. Thus, it wakes up the process when a connection from a client
  has been successfully established. It returns a new file descriptor, and all
  communication on this connection should be done using the new file descriptor. 
  The second argument is a reference pointer to the address of the client on
  the other end of the connection, and the third argument is the size of this
  structure.
  */

  while(1){
    
    // clearing buffers
    bzero(buffer_in,256);
    bzero(buffer_out,256);
    printf("Enter msg for client: ");
    fgets(buffer_out, 255, stdin);

    n = read(newsocketfd,buffer_in,255);
    if (n < 0)
      error("ERROR reading from socket");
    printf("Client: %s",buffer_in);

    /*
    Note that the read() will block until there is something for it to read
    in the socket, i.e. after the client has executed a write(). It will read
    either the total number of characters in the socket or 255, whichever is
    less, and return the number of characters read.
    */

    n = write(newsocketfd, buffer_out, strlen(buffer_out));
    if (n < 0)
      error("ERROR writing to socket");

    /*
    Once a connection has been established, both ends can both read and write to
    the connection. Naturally, everything written by the client will be read by
    the server, and everything written by the server will be read by the client.
    This code simply writes a short message to the client. The last argument of
    write is the size of the message.
    */

  }
  return 0; 
}