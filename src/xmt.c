//#define DEBUG
#include "common.h"
#include "readbin86.h"

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

  Elf32_Sym *main_ent = get_syment_by_func_name("main");
  Log("main: %08x %d %08x %d %s\n", 
    main_ent->st_value,
    main_ent->st_size,
    ELF32_ST_TYPE(main_ent->st_info),
    main_ent->st_shndx,
    strtab + main_ent->st_name
  );

  return 0;
}