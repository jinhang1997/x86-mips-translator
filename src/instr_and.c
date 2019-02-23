#include "common.h"
#include "translate.h"
#include "allinstr.h"
void trans_and(char *mode, char *argus[], char *suffix)
{
	
  Log("and worker");
  Log("suf:%s",suffix);
  if (!strcmp(mode, "rr"))
  {
    trans_and_rr(argus[0],argus[1]);
  }
  else if(!strcmp(mode, "ir"))
  {
  	trans_and_ir(argus[0],argus[1]);
  }
  else if(!strcmp(mode, "mr"))
  {
  	trans_and_mr(argus[0],argus[1],get_size_by_suf_x86(suffix[0]));
  }
  else if(!strcmp(mode, "im"))
  {
  	trans_and_im(argus[0],argus[1],get_size_by_suf_x86(suffix[0]));
  }
  else if(!strcmp(mode, "rm"))
  {
  	trans_and_rm(argus[0],argus[1],get_size_by_suf_x86(suffix[0]));
  }
  else 
  {
  	TODO();
  }
  
}
void trans_and_rr(char * reg1,char * reg2)
{
	 int id1 = get_reg_index(reg1);
	 int id2 = get_reg_index(reg2);
	 tar_and(mips_regs_name[id2],mips_regs_name[id1],mips_regs_name[id2]);
}
void trans_and_ir(char * imm,char * reg)
{
	int idx = get_reg_index(reg);
	tar_movi2r("$t8",imm);
	tar_and(mips_regs_name[idx],mips_regs_name[idx],"$t8");
}
void trans_and_mr(char * addr,char * reg, int size)
{
	char mips_addr_src[5];
	tar_getaddr(addr,mips_addr_src);
	tar_load("$t8", "0", mips_addr_src, size);
	int idx = get_reg_index(reg);
	tar_and(mips_regs_name[idx],mips_regs_name[idx],"$t8");
}

void trans_and_im(char * imm,char * addr, int size)
{
	Log("%s",addr);
	tar_movi2r("$t8",imm);
	char mips_addr_src[5];
	tar_getaddr(addr,mips_addr_src);
	tar_load("$t4", "0", mips_addr_src, size);
	tar_and("$t8","$t8","$t4");
	tar_store("$t8", "0", mips_addr_src, size);
}

void trans_and_rm(char * reg,char * addr, int size)
{
	Log("%s",addr);
	char mips_addr_src[5];
	tar_getaddr(addr,mips_addr_src);
	tar_load("$t8", "0", mips_addr_src, size);
	int idx = get_reg_index(reg);
	tar_and("$t8",mips_regs_name[idx],"$t8");
	tar_store("$t8", "0", mips_addr_src, size);
}




