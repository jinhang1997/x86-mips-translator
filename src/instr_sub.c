#include "common.h"
#include "translate.h"
#include "allinstr.h"
void trans_sub(char *mode, char *argus[], char *suffix)
{
  Log("sub worker");
  if (!strcmp(mode, "rr"))
  {
    trans_sub_rr(argus[0],argus[1]);
  }
  else if(!strcmp(mode, "ir"))
  {
  	trans_sub_ir(argus[0],argus[1]);
  }
  else if(!strcmp(mode, "mr"))
  {
  	trans_sub_mr(argus[0],argus[1],get_size_by_suf_x86(suffix[0]));
  }
  else 
  {
  	TODO();
  }
  
}
void trans_sub_rr(char * reg1,char * reg2)
{
	 int id1 = get_reg_index(reg1);
	 int id2 = get_reg_index(reg2);
	 tar_sub(mips_regs_name[id1],mips_regs_name[id1],mips_regs_name[id2]);
}
void trans_sub_ir(char * imm,char * reg)
{
	int num;
	char **temp1,temp2[20];
	num=strtol(imm,temp1, 0); 
	num=-num;
	sprintf(temp2,"%d",num);
	int idx = get_reg_index(reg);
	tar_addi(mips_regs_name[idx],mips_regs_name[idx],temp2);
}
void trans_sub_mr(char * addr,char * reg, int size)
{
	char mips_subr_src[5];
	tar_getaddr(addr,mips_subr_src);
	tar_loadu("$t8", "0", mips_subr_src, size);
	int idx = get_reg_index(reg);
	tar_sub(mips_regs_name[idx],mips_regs_name[idx],"$t8");
}

















