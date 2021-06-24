#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "drink.h"


int main(int argc, char **argv){
	if(argc==2){
		char *selDrink = argv[1];
		int first = -1, last = -1, variants = Venti - Short + 1;

		for(int i=0;i<no_of_drinks;i++){
			if(strcmp(selDrink,menu[i].kind)!=0)
				continue;
			if(first==-1)
				first = i;
			last = i;
		}

		if((first>=0 && first<no_of_drinks)){
			for(;first<=last;first++){
				printf("%s\n", menu[first].name);
				for (int i = 0; i < variants; ++i)
					printf("\t%s\t%d\n", cupsizename[i], menu[first].price[i]);
			}
		}
	}else
		exit(0);
	return 0;
}