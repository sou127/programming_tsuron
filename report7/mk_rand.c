#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define MAX 100

void Usage(char *cmd){
  printf ("%s -nx or -Nx (x>0)\n", cmd);
  exit (EXIT_FAILURE);
}

int main(int argc, char **argv) {
  int opt;
  int opt_n = 0, opt_N = 0;
  int N = MAX, N_n, N_N;
  char cmd[100];
  int k;

  strcpy(cmd, *argv);

  if (argc < 2)
    Usage (cmd);

  while ((opt = getopt(argc, argv, "n:N:")) != -1){
    switch (opt){
      case 'n':
        opt_n = 1;
        N_n = atoi(optarg);
        N = atoi(optarg);
        break;
      case 'N':
        opt_N = 1;
        N_N = atoi(optarg);
        N = atoi(optarg);
        break;
      }
  }
  if ((opt_n == 1) && (opt_N == 1)){
    opt_N = 0;
    N = N_n;
  }

  if (N < 1)
    Usage (cmd);

  if (opt_N)
    srand(time(NULL));

  //    printf("%d\n", N);
  for (k = 0; k < N; k++){
    printf("%d\n", rand());
  }

  return 0;
}

