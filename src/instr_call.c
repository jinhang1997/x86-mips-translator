#include "common.h"
#include "translate.h"
#include "allinstr.h"

void trans_call(char *mode, char *argus[], char *suffix)
{
  Log("call worker");
  tar_load("$a0", "0", "$sp", 4);
  tar_load("$a1", "4", "$sp", 4);
  tar_load("$a2", "8", "$sp", 4);
  tar_load("$a3", "12", "$sp", 4);
  tar_addi("$sp", "$sp", "-4");
  tar_store("$ra", "0", "$sp", 4);
  fprintf(fp_out, "  .option pic0\n");
  fprintf(fp_out, "  jal %s\n", argus[0]);
  fprintf(fp_out, "  .option pic2\n");
  tar_addi("$sp", "$sp", "4");
  tar_load("$ra", "0", "$sp", 4);
}
/*
void trans_push_r(char *reg)
{
  int idx = get_reg_index(reg);
  //fprintf(fp_out, "  addi $sp,$sp,-4\n");
  //fprintf(fp_out, "  sw %s,$sp\n", mips_regs_name[idx]);
  tar_addi("$sp", "$sp", "-4");
  tar_store(mips_regs_name[idx], "0", "$sp",4);
}
*/