#include<stdio.h>
#include<string.h>
#include "April_nospaces.h"

int main() {
	char ch, *pointer;
	int k, charCounter = 0;

	scanf("%c",&ch);

	for(k=0;k<LINES;k++){
		pointer = words[k];
		while(pointer = strchr(pointer, (int) ch)){
			++charCounter; ++pointer;
		}
	}

	printf("%d\n", charCounter);

	return 0;
}

