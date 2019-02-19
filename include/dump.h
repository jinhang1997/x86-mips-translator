#ifndef _DUMP_H_
#define _DUMP_H_

#include "xmt.h"
#include "readbin86.h"

int call_objdump(char *elf_name, char *func_name, uint32_t start_addr, uint32_t stop_addr);
int clean_dump_dir();
void scan_file(char *file_name);
void dump_func(char *file_name, char *func_name);
void dump_main(char *bin_file_name);

#define MAX_STACK_CAPACITY 32
#define MAX_LINE_BUF 64
#define MAX_COMMAND_BUF 256

#endif