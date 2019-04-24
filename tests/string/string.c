#include <stdio.h>

int main(int argc, char const *argv[])
{
  char *str = "helloworld!\n";
  int i = 0;
  while (str[i] != 0)
  {
    putchar(str[i]);
    ++i;
  }
  return 0;
}