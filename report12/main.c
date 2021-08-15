#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include "myHeader.h"

char **argp;

void *routine(void *argm);

int main(int argc, char * argv[]){

    int i;
    argp = argv;
    pthread_t threads[argc - 1];

    struct timespec startTime, endTime;
    clock_gettime (CLOCK_REALTIME, &startTime);

    for(i=0;i<argc - 1;i++){
        pthread_create(&threads[i], NULL, routine, argp[i+1]);
    }

    for(i=0;i<argc - 1;i++){
        pthread_join(threads[i], NULL);
    }

    clock_gettime (CLOCK_REALTIME, &endTime);

    printf ("elapsed = ");
    if (endTime.tv_nsec - startTime.tv_nsec < 0)
    {
      printf ("%10ld.%09ld", endTime.tv_sec - startTime.tv_sec - 1,
              1000000000 + endTime.tv_nsec - startTime.tv_nsec);
    }
    else
    {
      printf ("%10ld.%09ld", endTime.tv_sec - startTime.tv_sec,
              endTime.tv_nsec - startTime.tv_nsec);
    }
    printf ("(sec)\n");

    return 0;
}


void *routine(void *argm){

    char *argv = argm;

    RAWDATA_t raw;
    int i, j, c;
    int ave, sum;
    char IntputFileName[FNAMELEN] = { 0 };
    char OutputFileName[FNAMELEN] = { 0 };
    char *p;

    int n;

    FILE *fo;
    
    strcpy (IntputFileName, argv);
    p = strstr (IntputFileName, EXT);
    if (p == NULL){
      fprintf (stderr, "Input File should be named .jpg\n");
      exit (EXIT_FAILURE);
    }
    else{
      strcpy (OutputFileName, IntputFileName);
      puts (OutputFileName);
      p = strstr (OutputFileName, EXT);
      *p = '\0';
      strcat (OutputFileName, "_gray");
      strcat (OutputFileName, EXT);
    }

    if (jpegFileReadDecode (&raw, IntputFileName) == -1){
      printf ("tiffFileReadDecode error\n");
      exit (EXIT_FAILURE);
    }

    /* convert colour to gray scale */

    jpegConvertColourtoGray (&raw);
    if (jpegFileEncodeWrite (&raw, OutputFileName) == -1)
    {
      printf ("tiffFileEncodeWrite error\n");
      freeRawData (&raw);
      exit (EXIT_FAILURE);
    }

    freeRawData (&raw);
}