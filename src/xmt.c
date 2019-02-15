#define DEBUG
#include "common.h"
#include "readbin86.h"

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    error(1, NULL);
  }

  return readbin86(argv[1]);
}