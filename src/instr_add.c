#include "common.h"
#include "translate.h"
#include "allinstr.h"
void trans_add(char *mode, char *argus[], char *suffix)
{
  Log("add worker");
  if (!strcmp(mode, "rr"))
  {
    trans_add_rr(argus[0],argus[1]);
  }
  else if(!strcmp(mode, "ir"))
  {
  	trans_add_ir(argus[0],argus[1]);
  }
  else if(!strcmp(mode, "mr"))
  {
  	trans_add_mr(argus[0],argus[1],get_size_by_suf_x86(suffix[0]));
  }
  else 
  {
  	TODO();
  }
  
}
void trans_add_rr(char * reg1,char * reg2)
{
	 int id1 = get_reg_index(reg1);
	 int id2 = get_reg_index(reg2);
	 tar_add(mips_regs_name[id1],mips_regs_name[id1],mips_regs_name[id2]);
}
void trans_add_ir(char * imm,char * reg)
{
	int idx = get_reg_index(reg);
	tar_addi(mips_regs_name[idx],mips_regs_name[idx],imm);
}
void trans_add_mr(char * addr,char * reg, int size)
{
	char mips_addr_src[5];
	tar_getaddr(addr,mips_addr_src);
	tar_loadu("$t8", "0", mips_addr_src, size);
	int idx = get_reg_index(reg);
	tar_add(mips_regs_name[idx],mips_regs_name[idx],"$t8");
}

















