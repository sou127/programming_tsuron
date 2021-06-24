#include <stdio.h>

int endian_Check(void){
    unsigned int i = 1;
    char *c = (char*)&i;

    return *c;
}

int main(){
	if(endian_Check())
		printf("little-endian\n");
	else
		printf("big-endian\n");
	return 0;
}