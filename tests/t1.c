#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void transfer(char *dest, char *src, int len)
{
  do
  {
    if (*src == '\0')
    {
      break;
    }
    *dest = *src;
    src++;
    dest++;
  }
  while (--len > 0);
}

int main()
{
  char str1[20] = "helloworld!";
  char str2[20] = "";
  int len1 = strlen(str1);
  printf("len of str1: %d\n", len1);
  transfer(str2, str1, 5);
  printf("%s\n", str2);
  return 0;
}
