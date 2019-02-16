#include "common.h"
#include "dump.h"

char cmd[256];
char *file_queue[MAX_QUEUE_CAPACITY];

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
    "objdump %s -d --start-address=0x%x --stop-address=0x%x > ./dumps/%s.dump",
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

}