#include<stdio.h>
#include<string.h>
int main(void){

char str[5] = { 0 };

char *p = str;

fgets(str, sizeof(str) / sizeof(str[0]), stdin);

while (*p) {

printf("%02x", *p);

++p;

} return 0;
}