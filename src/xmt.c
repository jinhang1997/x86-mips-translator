//#define DEBUG
#include "common.h"
#include "xmt.h"

void error(int errid, char const *word)
{
  printf("\nfatal error %d: ", errid);
  if (errid == 1)
  {
    printf("no input file given.\n");
  }
  else if (errid == 2)
  {
    printf("unable to open specified file `%s'.\n", word);
  }
  else if (errid == 3)
  {
    printf("error while reading file.\n");
  }
  else if (errid == 4)
  {
    printf("not a ELF file.\n");
  }
  else if (errid == 5)
  {
    printf("analyze error: %s\n", word);
  }
  else
  {
    printf("unknown error.\n");
  }

  exit(errid);
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    error(1, NULL);
  }

  readbin86(argv[1]);

  dump_func(argv[1], "main");
  scan_file("./dumps/main.dump");
  dump_func(argv[1], "transfer");
  scan_file("./dumps/transfer.dump");
  //clean_dump_dir();

  return 0;
}