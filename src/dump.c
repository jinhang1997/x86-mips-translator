#include "common.h"
#include "dump.h"

static char cmd[MAX_COMMAND_BUF];
static char *stk_func[MAX_STACK_CAPACITY] = { NULL };
static char linebuf[MAX_LINE_BUF];
static int stk_func_top = 0;
static Jump_Label list_label[MAX_LABEL_CAPACITY];
static int jump_label_count = 0;
static int label_number = 0;

void list_label_query(uint32_t inst_addr, char *ret_label_name)
{
  int i;
  for (i=0; i<jump_label_count; ++i)
  {
    if (list_label[i].addr == inst_addr)
    {
      strcpy(ret_label_name, list_label[i].label);
    }
  }
}

void list_label_append(uint32_t inst_addr)
{
  char label[16];
  list_label[jump_label_count].addr = inst_addr;
  sprintf(label, ".TL%d", label_number);
  strcpy(list_label[jump_label_count].label, label);
  ++label_number;
  ++jump_label_count;
}

int stk_func_push(char *func_name)
{
  if (stk_func_top == MAX_STACK_CAPACITY)
  {
    return 1;
  }
  stk_func[stk_func_top] = (char *)malloc(strlen(func_name) + 1);
  strcpy(stk_func[stk_func_top], func_name);
  Log("push[%d]: %s", stk_func_top, stk_func[stk_func_top]);
  ++stk_func_top;
  return 0;
}

int stk_func_pop(char *stk_ret_func_name)
{
  if (stk_func_top == 0)
  {
    return 1;
  }
  --stk_func_top;
  strcpy(stk_ret_func_name, stk_func[stk_func_top]);
  Log("pop[%d]: %s", stk_func_top, stk_func[stk_func_top]);
  free(stk_func[stk_func_top]);
  stk_func[stk_func_top] = NULL;
  return 0;
}

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

void dump_control(uint32_t func_addr, char *instr, char *argus, char *extra)
{
  int func_name_len;
  if (!strcmp(instr, "call"))
  {
    func_name_len = strlen(extra);
    Log("func push control: %s", extra);
    if (func_name_len>4 && 0!=strcmp(&extra[func_name_len-4], "@plt"))
    {
      stk_func_push(extra);
    }
    if (!strcmp(extra, "__stack_chk_fail@plt"))
    {
      // TODO: ignore stack overflow check
      // and output it as `nop` instead
      trans_output(NULL, "nop", NULL, NULL);
    }
    else
    {
      // TODO: call translator to output instructions
      trans_output(NULL, instr, argus, extra);
    }
  }
  else
  {
    trans_output(NULL, instr, argus, extra);
  }
}

void scan_file(char *file_name)
{
  uint32_t func_addr;
  char instr[8], argus[32], extra[32];
  FILE *fp_func_dump = NULL;

  Log("scanning file: %s", file_name);
  fp_func_dump = fopen(file_name, "r");
  if (NULL == fp_func_dump)
  {
    error(3, NULL);
  }

  // TODO: print function header to output file
  //

  // 1st scan: record labels
  Log("1st scan:");
  for (;;)
  {
    fgets(linebuf, MAX_LINE_BUF, fp_func_dump);
    if (feof(fp_func_dump))
    {
      break;
    }
    instr[0] = argus[0] = extra[0] = '\0';
    sscanf(linebuf, "%x: %s %s <%s>", &func_addr, instr, argus, extra);
    extra[strlen(extra) - 1] = '\0';
    printf("%x - %s - %s - %s\n", func_addr, instr, argus, extra);
    // match jmp & jcc
    if (instr[0] == 'j')
    {

    }
  }
  // ready for 2nd scan
  clearerr(fp_func_dump);
  rewind(fp_func_dump);

  // 2nd scan: translate with function recoginition
  Log("2nd scan:");
  for (;;)
  {
    fgets(linebuf, MAX_LINE_BUF, fp_func_dump);
    if (feof(fp_func_dump))
    {
      break;
    }
    instr[0] = argus[0] = extra[0] = '\0';
    sscanf(linebuf, "%x: %s %s <%s>", &func_addr, instr, argus, extra);
    extra[strlen(extra) - 1] = '\0';
    printf("%x - %s - %s - %s\n", func_addr, instr, argus, extra);
    dump_control(func_addr, instr, argus, extra);
  }
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

void dump_main(char *elf_x86_name)
{
  char func_name_buf[64], dump_file_name[64];

  init_output(elf_x86_name);
  stk_func_push("main");
  while (stk_func_top)
  {
    stk_func_pop(func_name_buf);
    Log("%s to dump", func_name_buf);
    dump_func(elf_x86_name, func_name_buf);
    sprintf(dump_file_name, "./dumps/%s.dump", func_name_buf);
    Log("%s to scan", dump_file_name);
    function_header(func_name_buf);
    scan_file(dump_file_name);
    function_footer(func_name_buf);
  }
  end_output();
}