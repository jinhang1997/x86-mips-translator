#include "common.h"
#include "translate.h"
#include "allinstr.h"
void trans_jmp(char *mode, char *argus[], char *suffix)
{
	Log("%s",argus[0]);
  tar_j(argus[0]);
}
