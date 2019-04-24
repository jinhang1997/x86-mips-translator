#include <stdio.h>

int main(int argc, char const *argv[])
{
  char fmt[20] = "%s\n";
  char str[20] = "helloworld!";
  printf(fmt, str);
  return 0;
}