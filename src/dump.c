#include "common.h"
#include "dump.h"

char cmd[256];
char *file_queue[MAX_QUEUE_CAPACITY];
char linebuf[MAX_LINE_BUF];
int pqueue = 0;

int call_objdump(
  char *elf_name, 
  char *func_name,
  uint32_t start_addr, 
  uint32_t stop_addr
)
{
  system("mkdir -p ./dumps/");
  sprintf(
    cmd,
    "objdump %s -d --no-show-raw-insn --start-address=0x%x --stop-address=0x%x > ./dumps/%s.dump",
    elf_name,
    start_addr,
    stop_addr,
    func_name
  );
  Log("%s", cmd);
  system(cmd);
  sprintf(cmd, "sed -i '1,7d' ./dumps/%s.dump", func_name);
  Log("%s", cmd);
  system(cmd);

  return 0;
}

int clean_dump_dir()
{
  return system("rm -rf ./dumps/");
}

void scan_file(char *file_name)
{
  uint32_t addr;
  char instr[8], argus[32], extra[32];
  FILE *fp_func_dump = NULL;
  char *tok;

  Log("file: %s", file_name);
  fp_func_dump = fopen(file_name, "r");
  if (NULL == fp_func_dump)
  {
    error(3, NULL);
  }

  //file_queue[pqueue] = (char *)malloc(strlen(file_name))

  for (;;)
  {
    fgets(linebuf, MAX_LINE_BUF, fp_func_dump);
    if (feof(fp_func_dump))
    {
      break;
    }
    instr[0] = argus[0] = extra[0] = '\0';
    sscanf(linebuf, "%x: %s %s <%s>", &addr, instr, argus, extra);
    extra[strlen(extra) - 1] = '\0';
    printf("%x // %s // %s // %s\n", addr, instr, argus, extra);
  }
}

void dump_func(char *file_name, char *func_name)
{
  Elf32_Sym *sym_ent = get_syment_by_func_name(func_name);
  Log("%s: %08x %d %08x %d %s\n",
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