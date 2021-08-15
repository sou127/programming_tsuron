#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define PORT 8080

#define MAX 100                 // max chars in a line
void chat_server (int sockfd);
int
main (void)
{
  int sockfd, connfd, len;
  struct sockaddr_in servaddr, cli;

  // socket create and verification
  if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("socket");
      exit (EXIT_FAILURE);
    }
  else
    {
      printf ("Socket successfully created..\n");
    }
  memset (&servaddr, 0, sizeof (servaddr));

  // assign IP, PORT
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl (INADDR_ANY);
  servaddr.sin_port = htons (PORT);

  // Binding newly created socket to given IP and verification
  if ((bind (sockfd, (struct sockaddr *) &servaddr, sizeof (servaddr))) == -1)
    {
      perror ("bind");
      exit (EXIT_FAILURE);
    }
  else
    {
      printf ("Socket successfully binded..\n");
    }
  // Now server is ready to listen and verification
  if ((listen (sockfd, 5)) == -1)
    {
      perror ("listen");
      exit (EXIT_FAILURE);
    }
  else
    {
      printf ("Server listening..\n");
    }
  len = sizeof (cli);

  // Accept the data packet from client and verification
  if ((connfd =
       accept (sockfd, (struct sockaddr *) &cli, (socklen_t *) & len)) == -1)
    {
      perror ("accept");
      exit (EXIT_FAILURE);
    }
  else
    {
      printf ("server acccept the client...\n");
    }
  // Function for chatting between client and server
  chat_server (connfd);

  // After chatting close the socket
  close (sockfd);
}

void
chat_server (int sockfd)
{
  char buf[MAX];
  int n;
  // infinite loop for chat
  while (1)
    {
      bzero (buf, MAX);

      // read the message from client and copy it in bufer
      read (sockfd, buf, sizeof (buf));
      // print bufer which contains the client contents
      printf ("From friend: %s\t To friend : ", buf);
      bzero (buf, MAX);
      n = 0;
      // copy server message in the bufer
      while ((buf[n++] = getchar ()) != '\n')
        ;

      // and send that bufer to client
      write (sockfd, buf, sizeof (buf));

      // if msg contains "Exit" then server exit and chat ended.
      if (strncmp ("exit", buf, 4) == 0)
        {
          printf ("Server Exit...\n");
          break;
        }
    }
}