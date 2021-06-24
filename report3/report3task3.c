#include<stdio.h>
#include<string.h>

int main() {

	char buf1[10], buf2[10], str[10];

	scanf("%10s", buf1);
	scanf("%10s", buf2);

	strncpy(str, buf1, 10 - strlen(str));
	strncat(str, buf2, 10 - strlen(str));

    printf("%s\n", str);

	return 0;
}