#include<stdio.h>

int main(){
	double a = 20;
	int n = 2;
	char c = 's';
	
	int *npoint;
	char *cpoint;
	double *dpoint;
	
	npoint = &n;
	cpoint = &c;
	dpoint = &a;

	printf("The address of char is %p\n", &c); //display the address of c instead of a pointer for c
   	printf("The address of int is %p\n", &n); //display the address of n instead of a pointer for n
   	printf("The address of double is %p\n", &a);//display the address of a instead of a pointer for a
   	printf("The address of char* is %p\n", &cpoint);//display the address of cpoint instead of a pointer for &c
   	printf("The address of int* is %p\n", &npoint);//display the address of npoint instead of a pointer for &n
   	printf("The address of double* is %p\n\n", &dpoint);//display the address of dpoint instead of a pointer for &a
   	
   	printf("The value of char is %c\n", c); //display the value of c instead of *cpoint
   	printf("The value of int is %d\n", n); //display the value of n instead of *npoint
   	printf("The value of double is %f\n", a); //display the value of a instead of *dpoint
   	printf("The value of char* is %p\n", cpoint); //display the value of cpoint instead of &c
   	printf("The value of int* is %p\n", npoint); //display the value of npoint instead of &n
   	printf("The value of double* is %p\n\n", dpoint); //display the value of dpoint instead of &a
   	
   	printf("The size of char is %lu\n", sizeof(c));
   	printf("The size of int is %lu\n", sizeof(n));
   	printf("The size of double is %lu\n", sizeof(a));
   	printf("The size of char* is %lu\n", sizeof(cpoint));//display sizeof(cpoint) instead of sizeof(&c)
   	printf("The size of int* is %lu\n", sizeof(npoint));//display sizeof(npoint) instead of sizeof(&n)
   	printf("The size of double* is %lu\n", sizeof(dpoint));//display sizeof(dpoint) instead of sizeof(&a)
   	
   	
   	
	return 0;
}
