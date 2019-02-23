#include "common.h"
#include "translate.h"
#include "allinstr.h"
void trans_jmp(char *mode, char *argus[], char *suffix)
{
  tar_j(argus[0]);
}
