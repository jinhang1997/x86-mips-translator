#ifndef _READBIN86_H_
#define _READBIN86_H_

extern FILE *fp_x86elf_in; /* ELF file to read */
extern Elf32_Ehdr elf_header; /* ELF header */
extern Elf32_Shdr *sh_list; /* section headers array */
extern Elf32_Sym *sym_list; /* symbol table array */

extern Elf32_Shdr *shent_symtab; /* section header of symtab */
extern Elf32_Shdr *shent_strtab; /* section header of strtab */

extern char *shstrtab; /* section headers' string table */
extern char *strtab; /* symbols' string table */

extern char *sh_type_str[];

void error(int errid, char const *word);
void read_elf_header();
void print_elf_header();
void read_section_headers();
void print_section_headers();
Elf32_Shdr *get_shent_by_name(char const *target);
void read_symbol_table();
void print_symbol_table();
int readbin86_main(char *elf_x86_name);
Elf32_Sym *get_syment_by_func_name(char *func_name);

#endif