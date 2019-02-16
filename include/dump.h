#ifndef _DUMP_H_
#define _DUMP_H_

int call_objdump(char *elf_name, char *func_name, uint32_t start_addr, uint32_t stop_addr);
int clean_dump_dir();

#define MAX_QUEUE_CAPACITY 32

#endif