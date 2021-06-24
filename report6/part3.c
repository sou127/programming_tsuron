#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

union {
	double x;
	unsigned char byte[sizeof (double)];
} converter;

int endian_Check(void){
    unsigned int i = 1;
    char *c = (char*)&i;

    return *c;
}

int main() {
	int i;
	scanf("%le", &converter.x);

	if(endian_Check()){
		for(i = sizeof(converter.byte)-1; i >= 0; --i)
			printf("%02x", converter.byte[i]);
	}else{
		for(i = 0; i <= sizeof(converter.byte)-1; i++)
			printf("%02x", converter.byte[i]);
	}
	printf("\n");

	return 0;
}