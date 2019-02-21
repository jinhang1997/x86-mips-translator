#include "common.h"
#include "translate.h"
#include "allinstr.h"
void trans_ret(char *mode, char *argus[], char *suffix)
{
  tar_movr2r("$v0","$t0");
  tar_jr("$ra"); 
}
