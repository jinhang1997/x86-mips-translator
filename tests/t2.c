#include <string.h>

char str1[20] = "helloworld!"; // 在.data中

void callcopy(char *dest, char *src)
{
  strcpy(dest, src);
}

int main(int argc, char const *argv[])
{
  char str2[20] = "";
  callcopy(str2, str1);
  return 0;
}
