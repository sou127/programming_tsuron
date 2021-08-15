#include<stdio.h>
#include<string.h>
int main(void)
{
  char a[8] = "0123456";
  char b[8];

  printf("Before a = %s\n", a);

  fgets(b, sizeof(b), stdin);
  //scanf("%s", b);
  printf("After a = %s\n", a);
  return 0;
}

