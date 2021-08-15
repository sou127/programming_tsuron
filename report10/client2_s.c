#include<unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX 100
#define PORT 8080

void chat_client (int sockfd);

int
main (void)
{
  int sockfd, connfd;
  struct sockaddr_in servaddr, cli;

  // socket create and varification
  if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      printf ("socket creation failed...\n");
      exit (0);
    }
  else
    {
      printf ("Socket successfully created..\n");
    }
  memset (&servaddr, 0, sizeof (servaddr));

  // assign IP, PORT
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr ("127.0.0.1");
  servaddr.sin_port = htons (PORT);

  // connect the client socket to server socket
  if (connect (sockfd, (struct sockaddr *) &servaddr, sizeof (servaddr)) ==
      -1)
    {
      perror ("connect");
      exit (EXIT_FAILURE);
    }
  else
    {
      printf ("connected to the server..\n");
    }
  // function for chat
  chat_client (sockfd);

  // close the socket
  close (sockfd);
}

void
chat_client (int sockfd)
{
  char buf[MAX];
  char *line = NULL;
  size_t len = 0;

  while (1)
    {
      memset (buf, 0, sizeof (buf));
      printf ("Enter the string : ");
      getline (&line, &len, stdin);
      strncpy (buf, line, MAX);
      write (sockfd, buf, sizeof (buf));
      memset (buf, 0, sizeof (buf));
      read (sockfd, buf, sizeof (buf));
      printf ("From Server : %s", buf);
      if ((strncmp (buf, "exit", 4)) == 0)
        {
          printf ("Client Exit...\n");
          break;
        }
    }
}