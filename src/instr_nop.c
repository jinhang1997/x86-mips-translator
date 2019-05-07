#include "common.h"
#include "translate.h"
#include "allinstr.h"
void trans_nop(char *mode, char *argus[], char *suffix)
{
	
  Log("nop worker");
  Log("suf:%s",suffix);
  fprintf(fp_out, "  nop\n");
}
