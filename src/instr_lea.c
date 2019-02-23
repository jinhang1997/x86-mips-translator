#include "common.h"
#include "translate.h"
#include "allinstr.h"

void trans_lea(char *mode, char *argus[], char *suffix)
{
  Log("lea worker (suf: %s) %s -> %s", suffix, argus[0], argus[1]);

 if (!strcmp(mode, "mr"))
  {
    trans_lea_mr(argus[0], argus[1], get_size_by_suf_x86(suffix[0]));
  }
 else
 	{
 		TODO();
 	}

}


void trans_lea_mr(const char *addr, const char *reg, int size)//memory to register
{
  bool success=false;
  //char mips_reg_dest[5];
  char mips_addr_src[5];
  tar_getaddr(addr,mips_addr_src);
  //get_reg_val(reg,&success,mips_reg_dest);
  tar_movr2r(mips_regs_name[get_reg_index(reg)],mips_addr_src);
}

