#include "common.h"
#include "translate.h"

static FILE *fp_out = NULL;
static Instr_Table_Entry x86_instr_table[] = {
  {"push", trans_push},
  /*{"mov", },
  {"pop", },
  {"ret", },*/
};
static char *x86_regs_name[] = { "%eax", "%ecx", "%edx", "%ebx", "%esp", "%ebp", "%esi", "%edi" };
static char *mips_regs_name[] = { "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7" };
static char *opnd_type_name[] = { "OPND_NONE", "OPND_REG", "OPND_IMM", "OPND_MEM" };
static char *mode_type_name[] = { "", "r", "m", "i", "rr", "rm", "mr", "mm", "ir", "im"};

int get_reg_index(char *x86_reg)
{
  int i;
  for (i=0; i<REG_TYPE_NUM; ++i)
  {
    if (!strcmp(x86_regs_name[i], x86_reg))
    {
      return i;
    }
  }
  return -1;
}

Oprand_Type get_opnd_type(char *str)
{
  int i;
  if (str[0] == '$')
  {
    return OPND_IMM;
  }
  for (i=0; i<REG_TYPE_NUM; ++i)
  {
    if (!strcmp(str, x86_regs_name[i]))
    {
      return OPND_REG;
    }
  }
  return OPND_MEM;
}

void init_output(char *of_name)
{
  char out_file[64];
  sprintf(out_file, "./dumps/out.S");
  Log("mips assembly: %s", out_file);
  fp_out = fopen(out_file, "w");
  fprintf(fp_out, "  .text\n");
}

void end_output()
{
  fclose(fp_out);
}

void trans_output(char *label, char *instr, char *argus, char *extra)
{
  char instr1[16], instr2[16], suf[4];
  char str_argu[64], mode_type[4];
  char *p_str = NULL, *p_argus[3] = { NULL };
  int instr_len = strlen(instr), count_argu = 0;
  int i, flag;

  if (label)
  {
    fprintf(fp_out, "%s: ", label);
  }

  // analyze instuction
  strcpy(instr1, instr);
  strcpy(instr2, instr);
  strcpy(suf, &instr[instr_len-2]);
  instr1[instr_len-1] = '\0';
  instr1[instr_len-2] = '\0';

  // analyze operands
  
  strcpy(str_argu, argus);
  memset(mode_type, 0x00, sizeof(mode_type));
  for (count_argu=0; count_argu<3; ++count_argu)
  {
    p_argus[count_argu] = strtok(((count_argu == 0)? str_argu: NULL), ","); 
    if (NULL == p_argus[count_argu])
    {
      break;
    }
    mode_type[count_argu] = get_opnd_type(p_argus[count_argu]);
    Log("%s (%c)", p_argus[count_argu], mode_type[count_argu]);
  }
  Log("args: %s, mode_type: %s", str_argu, mode_type);
  
  // analyze extra infomation 


  // call working functions
  flag = 0;
  for (i=0; i<INSTR_NUM; ++i)
  {
    if (!strcmp(x86_instr_table[i].instr, instr))
    {
      (x86_instr_table[i].worker)(mode_type, p_argus);
      flag = 1;
      break;
    }
  }

}

void trans_push(char *mode, char *argus[])
{
  Log("push worker");
  if (!strcmp(mode, "r"))
  {
    trans_push_r(argus[0]);
  }
}

void trans_push_r(char *reg)
{
  int idx = get_reg_index(reg);
  fprintf(fp_out, "  addi $sp,$sp,-4\n");
  fprintf(fp_out, "  sw %s,$sp\n", mips_regs_name[idx]);
}
