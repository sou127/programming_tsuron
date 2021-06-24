#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM 10000000

int cmpfunc(const void * a, const void * b) {
   return ( *(int*)b - *(int*)a );
}

int main(void)
{
	int  *p, *p_org;

	if ((p = (int *)malloc(sizeof(int) * NUM)) == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	p_org = p;

	memset(p, 0, sizeof(int) * NUM);

	for(int i=0;i<NUM;i++){
		scanf("%d", &p[i]);
	}

	qsort(p, NUM, sizeof(int), cmpfunc);

	for(int i=0;i<NUM;i++){
		printf("%d\n", p[i]);
	}

	free(p_org);

	return 0;
}