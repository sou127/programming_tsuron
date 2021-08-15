#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int read_parse_input(char *cmd[], char input[]);
void child(char *cmd[]);

int main(){
	char *cmd[255];
	char *input = NULL;
	int status;

	while(read_parse_input(cmd, input)){

		pid_t pid = fork();
		if(pid == 0){
			child(cmd);
		}else{
			pid_t r = waitpid(pid, &status, 0);
			if(r<0){
				perror("waitpid");
				exit(EXIT_FAILURE);
			}
		}
	}
	free(input);
	return 0;
}


int read_parse_input(char *cmd[], char input[]){

	size_t len = 0;
	ssize_t nread;
	printf("%% ");
	nread = getline(&input, &len, stdin);

	int i=0;
	while(input[i]!='\n')
		i++;
	input[i] = '\0';
	if(strcmp(input, "exit")==0 || nread == -1){
		printf("main program exited\n");
		exit(0);
	}

	i = 0;
	cmd[i] = strtok(input, " ");
	while(cmd[i] != NULL){
		i++;
		cmd[i] = strtok(NULL, " ");
	}

	
	return 1;
}