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

void dump_func(char *file_name, char *func_name)
{
  Elf32_Sym *sym_ent = get_syment_by_func_name(func_name);
  Log("%s: %08x %d %08x %d %s",
    file_name,
    sym_ent->st_value,
    sym_ent->st_size,
    ELF32_ST_TYPE(sym_ent->st_info),
    sym_ent->st_shndx,
    strtab + sym_ent->st_name
  );
  call_objdump(
    file_name, 
    func_name, 
    sym_ent->st_value, 
    sym_ent->st_value + sym_ent->st_size
  );
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    error(1, NULL);
  }

  readbin86(argv[1]);

  dump_func(argv[1], "main");
  dump_func(argv[1], "transfer");
  //clean_dump_dir();

  return 0;
}