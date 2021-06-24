#include<stdio.h>
#include<string.h>
#include "April_nospaces.h"

int main() {
	char ch[10], *pointer;
	int k, charCounter = 0;

	scanf("%10s",ch);

	for(k=0;k<LINES;k++){
		pointer = words[k];
		while(pointer = strstr(pointer, ch)){
			++charCounter; ++pointer;
		}
	}

	printf("%d\n", charCounter);

	return 0;
}

