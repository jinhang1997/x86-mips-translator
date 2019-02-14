#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>

Elf32_Ehdr elf_header;

int error(int errid, char const *word)
{
  printf("fatal error %d: ", errid);
  if (errid == 1)
  {
    printf("no input file given.\n");
  }
  else if (errid == 2)
  {
    printf("unable to open specified file `%s'.\n", word);
  }
  else
  {
    printf("unknown error.\n");
  }

  return errid;
}

void print_elf_header(FILE *fp)
{
  int i;

  fread(&elf_header, sizeof(Elf32_Ehdr), 1, fp);

  for (int i = 0; i < EI_NIDENT; ++i)
  {
    printf("%02x ", elf_header.e_ident[i]);
  }
  printf("\n");
  printf("%04x\n", elf_header.e_type);
  printf("%08x\n", elf_header.e_shoff);

}

int main(int argc, char const *argv[])
{
  FILE *fp;

  if (argc < 2)
  {
    return error(1, NULL);
  }

  fp = fopen(argv[1], "rb");
  if (NULL == fp)
  {
    return error(2, argv[1]);
  }

  print_elf_header(fp);

  fclose(fp);

  return 0;
}