#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Usage(char *cmd){
  printf("%s [addition/subtraction/multiplication/division/modulo] num1 num2\n", cmd);
  exit(0);
}

int addition(int a, int b){
	return (a+b);
}
int subtraction(int a, int b){
	return (a-b);
}
int multiplication(int a, int b){
	return (a*b);
}
int division(int a, int b){
	return (a/b);
}
int modulo(int a, int b){
	return (a%b);
}

int main(int argc, char *argv[]){

	int (*calcp2f[])(int, int) = {addition, subtraction, multiplication, division, modulo};


    char *cmd = argv[0];

    int ans;

    if(argc == 4){
    	int a = atoi(argv[2]);
    	int b = atoi(argv[3]);
    	if(strcmp(argv[1],"addition") == 0)
        	ans = calcp2f[0](a,b);
        else if(strcmp(argv[1],"subtraction") == 0)
        	ans = calcp2f[1](a,b);
        else if(strcmp(argv[1],"multiplication") == 0)
        	ans = calcp2f[2](a,b);
        else if(strcmp(argv[1],"division") == 0)
        	ans = calcp2f[3](a,b);
        else if(strcmp(argv[1],"modulo") == 0)
        	ans = calcp2f[4](a,b);
        else
        	Usage(cmd);
    }else{
    	Usage(cmd);
    }
    
    printf("answer = %d\n", ans);


    return 0;
}


