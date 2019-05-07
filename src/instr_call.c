#include "common.h"
#include "translate.h"
#include "allinstr.h"

void trans_call(char *mode, char *argus[], char *suffix)
{
  int func_name_len;

  Log("call worker %s", argus[0]);
  func_name_len = strlen(argus[0]);
  if (func_name_len>4 && 0!=strcmp(&argus[0][func_name_len-4], "@plt"))
  {
    // functions not in `.plt` section, means user function
    trans_call_text(mode, argus, suffix);
  }
  else
  {
    // functions in `.plt` section, means library function
    trans_call_plt(mode, argus, suffix);
  }
}

void trans_call_text(char *mode, char *argus[], char *suffix)
{
  tar_load("$a0", "0", "$sp", 4);
  tar_load("$a1", "4", "$sp", 4);
  tar_load("$a2", "8", "$sp", 4);
  tar_load("$a3", "12", "$sp", 4);
  tar_addi("$sp", "$sp", "-4");
  tar_store("$ra", "0", "$sp", 4);
  fprintf(fp_out, "  .option pic0\n");
  fprintf(fp_out, "  jal %s\n", argus[0]);
  fprintf(fp_out, "  .option pic2\n");
  tar_load("$ra", "0", "$sp", 4);
  tar_addi("$sp", "$sp", "4");
}

void trans_call_plt(char *mode, char *argus[], char *suffix)
{
  char full_name[64];
  char *func_name = NULL;
  char sx[4] = "$s0", tx[4] = "$t0";
  int i;

  strcpy(full_name, argus[0]);
  func_name = strtok(full_name, "@");

  // load arguments
  tar_load("$a0", "0", "$sp", 4);
  tar_load("$a1", "4", "$sp", 4);
  tar_load("$a2", "8", "$sp", 4);
  tar_load("$a3", "12", "$sp", 4);
  // push $ra into stack ot protect the return value
  //tar_addi("$sp", "$sp", "-4");
  //tar_store("$ra", "0", "$sp", 4);
  // set global pointer
  fprintf(fp_out, "  lui  $gp,%%hi(__gnu_local_gp)\n");
  fprintf(fp_out, "  addiu  $gp,$gp,%%lo(__gnu_local_gp)\n");
  // push to protect global pointer
  /*tar_addi("$sp", "$sp", "-4");
  tar_store("$gp", "0", "$sp", 4);*/
  // save all general registers
  for (i=0; i<8; i++)
  {
    if (i == 4)
    {
      // protect ra in $s4
      tar_movr2r(sx, "$ra");
    }
    else
    {
      tar_movr2r(sx, tx);
    }
    ++sx[2];
    ++tx[2];
  }
  // acquire address of library function and jump there
  // MUST load the address into $t9 and `jal $t9`
  fprintf(fp_out, "  lw  $v0,%%call16(%s)($gp)\n", func_name);
  tar_movr2r("$t9", "$v0");
  fprintf(fp_out, "  .option pic0\n");
  fprintf(fp_out, "  jal $t9\n");
  fprintf(fp_out, "  .option pic2\n");
  // rewind all general registers
  tx[2] = sx[2] = '0';
  for (i=0; i<8; i++)
  {
    if (i == 4)
    {
      // rewind ra from $s4
      tar_movr2r("$ra", sx);
    }
    else
    {
      tar_movr2r(tx, sx);
    }
    ++sx[2];
    ++tx[2];
  }
  // pop global pointer
  /*tar_load("$gp", "0", "$sp", 4);
  tar_addi("$sp", "$sp", "4");*/
  // move return value in $v0 to $t0
  tar_movr2r("$t0", "$v0");
  // pop old $ra
  //tar_load("$ra", "0", "$sp", 4);
  //tar_addi("$sp", "$sp", "4");
}
