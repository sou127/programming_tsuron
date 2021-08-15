#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFSIZE 256

int wordCount(const char *s);

int main (void){
  char input[BUFSIZE];
  char buf[BUFSIZE];
  ssize_t bytes;
  int fd[2];
  int fd2[2];
  char *msg;
  pid_t pid;

  if (pipe (fd) == -1)
    {
      perror ("pipe");
      exit (EXIT_FAILURE);
    }
  if (pipe (fd2) == -1)
    {
      perror ("pipe");
      exit (EXIT_FAILURE);
    }

  memset (input, 0, sizeof (input));    //clear input
  memset (buf, 0, sizeof (buf));        //clear buf

  if ((pid = fork ()) == -1)
    {
      perror ("fork");
      exit (EXIT_FAILURE);
    }
  else if (pid == 0)
    {
      char *s = buf;
      close (fd[1]);
      read (fd[0], buf, BUFSIZE);
      printf("child started calculating...\n");
      int wc = wordCount(buf);
    
      double nums[wc];
      
      int len, c = 0;
      int x, total=0;
      while(1==sscanf(s, "%d%n", &x, &len)){
          total += (nums[c++] = x);
          s += len;
      }
      int ans = nums[0]+nums[1];
      char retVal[BUFSIZE];
      snprintf(retVal, BUFSIZE,"%d\n",ans);

      printf("calculated. exiting child...\n");
      close (fd[0]);
      write (fd2[1], retVal, strlen (buf)+1);
    }
  else
    {
      int status;
      pid_t r;
      close (fd[0]);
      printf("reading as string from parent\n");
      fgets (input, BUFSIZE, stdin);
      write (fd[1], input, strlen (input) + 1);
      if ((r = waitpid (pid, &status, 0)) < 0)
        {
          perror ("waitpid");
          exit (EXIT_FAILURE);
        }
        read (fd2[0], buf, BUFSIZE);
        printf("printing result from parent\n");
        write (STDOUT_FILENO, buf, strlen (buf));
        close(fd2[0]);
      close (fd[1]);
      
    }

  return 0;
}


int wordCount(const char *s){
    char prev = ' ';
    int wc = 0;

    while(*s){
        if(isspace(prev) && !isspace(*s)){
            ++wc;
        }
        prev = *s++;
    }
    return wc;
}
