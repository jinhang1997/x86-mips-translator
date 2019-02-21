#include "common.h"
#include "translate.h"
#include "allinstr.h"

void trans_pop(char *mode, char *argus[], char *suffix)
{
  Log("pop worker");
  if (!strcmp(mode, "r"))
  {
    trans_pop_r(argus[0]);
  }
}

void trans_pop_r(char *reg)
{
  int idx = get_reg_index(reg);
  //fprintf(fp_out, "  addi $sp,$sp,-4\n");
  //fprintf(fp_out, "  sw %s,$sp\n", mips_regs_name[idx]);
  tar_addi("$sp", "$sp", "4");
  tar_load(mips_regs_name[idx], "0", "$sp",4);
}
 
