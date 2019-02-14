#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <elf.h>
#include "debug.h"

FILE *fp; /* ELF file */
Elf32_Ehdr elf_header; /* ELF header */
Elf32_Shdr *sh_list = NULL; /* section headers array */
char *shstrtab = NULL; /* section headers' string table */

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
  else
  {
    printf("unknown error.\n");
  }

  exit(errid);
}

void read_elf_header()
{
  int i;
  char magic[4] = {0x7f, 0x45, 0x4c, 0x46};
  
  // read and print elf headers
  fread(&elf_header, sizeof(Elf32_Ehdr), 1, fp);
  for (i = 0; i < 4; ++i)
  {  
    if (elf_header.e_ident[i] != magic[i])
    {
      error(4, NULL);
    }
  }
}

void print_elf_header()
{
  printf("Indentifiers: ");
  for (int i = 0; i < EI_NIDENT; ++i)
  {
    printf("%02x ", elf_header.e_ident[i]);
  }
  putchar('\n');
  printf("Section header offset: %d (0x%08x)\n", elf_header.e_shoff, elf_header.e_shoff);
  printf("Size of each section header: %d (0x%08x)\n", elf_header.e_shentsize, elf_header.e_shentsize);
  printf("Number of section headers: %d (0x%08x)\n", elf_header.e_shnum, elf_header.e_shoff);
  printf("Index of names of section headers: %d (0x%08x)\n", elf_header.e_shstrndx, elf_header.e_shstrndx);
  putchar('\n');
}

void read_section_headers()
{
  // read section headers
  if (fseek(fp, elf_header.e_shoff, SEEK_SET) != 0)
  {
    error(3, NULL);
  }
  sh_list = (Elf32_Shdr *)malloc(sizeof(Elf32_Shdr) * elf_header.e_shnum);
  if (!sh_list)
  {
    error(3, NULL);
  }
  fread(sh_list, sizeof(Elf32_Shdr) * elf_header.e_shnum, 1, fp);

  // read names of sections
  if (fseek(fp, sh_list[elf_header.e_shstrndx].sh_offset, SEEK_SET) != 0)
  {
    error(3, NULL);
  }
  shstrtab = (char *)malloc(sizeof(char) * sh_list[elf_header.e_shstrndx].sh_size);
  if (!shstrtab)
  {
    error(3, NULL);
  }
  fread(shstrtab, sizeof(char), sh_list[elf_header.e_shstrndx].sh_size, fp);
}

void print_section_headers()
{
  if (!sh_list)
  {
    error(3, NULL);
  }
  printf("Section headers:\n");
  printf("  [%2s] %-20s %-8s %-8s %-8s %-8s\n","Nr", "Name", "Type", "Address", "Offset", "Size");
  for (int i = 0; i < elf_header.e_shnum; ++i)
  {
    printf("  [%2d] %-20s %08x %08x %08x %08x\n",
      i, 
      shstrtab + sh_list[i].sh_name,
      sh_list[i].sh_type, 
      sh_list[i].sh_addr, 
      sh_list[i].sh_offset, 
      sh_list[i].sh_size
    );
  }
  putchar('\n');
}

Elf32_Shdr *get_shent_by_name(char const *target)
{
  int i;
  for (i = 0; i < elf_header.e_shnum; ++i)
  {
    if (!strcmp(target, shstrtab + sh_list[i].sh_name))
    {
      return &sh_list[i];
    }
  }
  return NULL;
}

int main(int argc, char const *argv[])
{
  if (argc < 2)
  {
    error(1, NULL);
  }

  fp = fopen(argv[1], "r");
  if (NULL == fp)
  {
    error(2, argv[1]);
  }
  printf("File: %s\n", argv[1]);

  read_elf_header();
  print_elf_header();

  read_section_headers();
  print_section_headers();

  fclose(fp);

  return 0;
}