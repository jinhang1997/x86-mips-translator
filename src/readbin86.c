#include "common.h"
#include "xmt.h"

FILE *fp_x86elf_in; /* ELF file to read */
Elf32_Ehdr elf_header; /* ELF header */
Elf32_Shdr *sh_list = NULL; /* section headers array */
Elf32_Sym *sym_list = NULL; /* symbol table array */

Elf32_Shdr *shent_symtab = NULL; /* section header of symtab */
Elf32_Shdr *shent_strtab = NULL; /* section header of strtab */

char *shstrtab = NULL; /* section headers' string table */
char *strtab = NULL; /* symbols' string table */

char *sh_type_str[] = {
  "NULL",
  "PROGBITS",
  "SYMTAB",
  "STRTAB",
  "RELA",
  "HASH",
  "DYNAMIC",
  "NOTE",
  "NOBITS",
  "REL",
  "SHLIB",
  "DYNSYM",
  "<NOT USED>",
  "<NOT USED>",
  "INIT_ARRAY",
  "FINI_ARRAY",
  "PREINIT_ARRAY",
  "GROUP",
  "SYMTAB_SHNDX",
  "NUM",
  "<OTHER>",
};

void read_elf_header()
{
  int i;
  char magic[4] = {0x7f, 0x45, 0x4c, 0x46};
  
  // read and print elf headers
  fread(&elf_header, sizeof(Elf32_Ehdr), 1, fp_x86elf_in);
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
  int i;
  printf("Identification: ");
  for (i = 0; i < EI_NIDENT; ++i)
  {
    printf("%02x ", elf_header.e_ident[i]);
  }
  putchar('\n');
  printf("Section header offset: %d\n", elf_header.e_shoff);
  printf("Size of each section header: %d\n", elf_header.e_shentsize);
  printf("Number of section headers: %d\n", elf_header.e_shoff);
  printf("Index of names of section headers: %d\n", elf_header.e_shstrndx);
  putchar('\n');
}

void read_section_headers()
{
  // read section headers
  if (fseek(fp_x86elf_in, elf_header.e_shoff, SEEK_SET) != 0)
  {
    error(3, NULL);
  }
  sh_list = (Elf32_Shdr *)malloc(sizeof(Elf32_Shdr) * elf_header.e_shnum);
  if (!sh_list)
  {
    error(3, NULL);
  }
  fread(sh_list, sizeof(Elf32_Shdr) * elf_header.e_shnum, 1, fp_x86elf_in);

  // read names of sections
  if (fseek(fp_x86elf_in, sh_list[elf_header.e_shstrndx].sh_offset, SEEK_SET) != 0)
  {
    error(3, NULL);
  }
  shstrtab = (char *)malloc(sizeof(char) * sh_list[elf_header.e_shstrndx].sh_size);
  if (!shstrtab)
  {
    error(3, NULL);
  }
  fread(shstrtab, sizeof(char), sh_list[elf_header.e_shstrndx].sh_size, fp_x86elf_in);
}

void print_section_headers()
{
  int sh_str_idx, i;
  if (!sh_list)
  {
    error(3, NULL);
  }
  printf("Section headers:\n");
  printf("  [%2s] %-20s %-14s %-8s %-8s %-8s\n","Nr", "Name", "Type", "Address", "Offset", "Size");
  for (i = 0; i < elf_header.e_shnum; ++i)
  {
    sh_str_idx = (sh_list[i].sh_type >= 20) ? 20 : sh_list[i].sh_type;
    printf("  [%2d] %-20s %-14s %08x %08x %08x\n",
      i, 
      shstrtab + sh_list[i].sh_name,
      sh_type_str[sh_str_idx], 
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

void read_symbol_table()
{
  shent_symtab = get_shent_by_name(".symtab");
  shent_strtab = get_shent_by_name(".strtab");
  if (!shent_symtab)
  {
    error(5, "symtab not found");
  }
  if (!shent_symtab)
  {
    error(5, "strtab not found");
  }

  // read symbol table
  if (fseek(fp_x86elf_in, shent_symtab->sh_offset, SEEK_SET) != 0)
  {
    error(3, NULL);
  }
  sym_list = (Elf32_Sym *)malloc(shent_symtab->sh_size);
  if (!sym_list)
  {
    error(3, NULL);
  }
  fread(sym_list, shent_symtab->sh_size, 1, fp_x86elf_in);

  // read names of symbols
  if (fseek(fp_x86elf_in, shent_strtab->sh_offset, SEEK_SET) != 0)
  {
    error(3, NULL);
  }
  strtab = (char *)malloc(shent_strtab->sh_size);
  if (!strtab)
  {
    error(3, NULL);
  }
  fread(strtab, shent_strtab->sh_size, 1, fp_x86elf_in);
}

void print_symbol_table()
{
  int i, num, ndx;

  num = shent_symtab->sh_size / sizeof(Elf32_Sym);
  printf("Symbol table '.symtab' contains %d entries:\n", num);
  printf("   %3s: %8s %5s %-8s %3s %s\n", "Num", "Value", "Size", "Type", "Ndx", "Name");
  for (i = 0; i < num; ++i)
  {
    ndx = sym_list[i].st_shndx;
    if (sym_list[i].st_shndx > num)
    {
      ndx = -1;
    }
    printf("   %3d: %08x %5d %08x %3d %s\n", 
      i,
      sym_list[i].st_value,
      sym_list[i].st_size,
      ELF32_ST_TYPE(sym_list[i].st_info),
      ndx,
      strtab + sym_list[i].st_name
    );
  }
  putchar('\n');
}

Elf32_Sym *get_syment_by_func_name(char *func_name)
{
  int i, num;

  num = shent_symtab->sh_size / sizeof(Elf32_Sym);
  for (i = 0; i < num; ++i)
  {
    if (!strcmp(func_name, strtab + sym_list[i].st_name))
    {
      return &sym_list[i];
    }
  }

  return NULL;
}

int readbin86_main(char *elf_x86_name)
{
  fp_x86elf_in = fopen(elf_x86_name, "r");
  if (NULL == fp_x86elf_in)
  {
    error(2, elf_x86_name);
  }
  printf("File: %s\n", elf_x86_name);

  read_elf_header();
  print_elf_header();

  read_section_headers();
  print_section_headers();

  read_symbol_table();
  print_symbol_table();

  fclose(fp_x86elf_in);

  return 0;
}