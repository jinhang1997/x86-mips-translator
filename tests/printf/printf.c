#include <stdio.h>

int main(int argc, char const *argv[])
{
  char fmt[20] = "%s %d\n";
  char str[20] = "helloworld!";
  int num = 1234;
  printf(fmt, str, num);
  return 0;
}