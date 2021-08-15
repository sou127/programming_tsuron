#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

void child(char *cmd[]){
	if(execvp(cmd[0], cmd) == -1){
        printf("command not found\n");
        exit(EXIT_FAILURE);
    }
}