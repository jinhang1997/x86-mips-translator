#include "common.h"
#include "translate.h"
#include "allinstr.h"

void trans_mov(char *mode, char *argus[], char *suffix)
{
  Log("mov worker (suf: %s) %s -> %s", suffix, argus[0], argus[1]);
  if (!strcmp(mode, "ir"))
  {
    trans_mov_ir(argus[0], argus[1]);
  }
  else if (!strcmp(mode, "rr"))
  {
    trans_mov_rr(argus[0], argus[1]);
  }
  else if (!strcmp(mode, "rm"))
  {
    trans_mov_rm(argus[0], argus[1], get_size_by_suf_x86(suffix[0]));
  }
  else if (!strcmp(mode, "mr"))
  {
    trans_mov_mr(argus[0], argus[1], get_size_by_suf_x86(suffix[0]));
  }
  else if (!strcmp(mode, "im"))
  {
    trans_mov_im(argus[0], argus[1], get_size_by_suf_x86(suffix[0]));
  }
}

void trans_mov_ir(const char *imm,const char *reg)//-> li reg,imm
{ 
  //char mips_reg[4];
  //bool success= true;
  //get_reg_val(reg,&success,mips_reg);
  //assert(success);
  tar_movi2r(mips_regs_name[get_reg_index(reg)], imm);
//    if (arg == (int16_t)arg) {  //the arg is s16
//      printf("addiu %s,$zero,%d\n",mips_reg,arg);
//      return;
//    }
//    else if (arg == (uint16_t)arg) {//the arg is u16
//      printf("ori %s,$zero,%d\n",mips_reg,arg);
//      return;
//    }
//  else //the size of the arg is 32 
//  {
//    printf("lui %s,0x%x\n",mips_reg,arg>>16);
//    printf("ori %s,0x%x\n",mips_reg,arg&0xffff);
//    return;
//   }
  
} 
 
void trans_mov_rr(const char *src, const char *dest)//->move reg,reg
{
  /*char mips_reg_src[4];
  char mips_reg_dest[4];
  bool success= true;
  get_reg_val(src,&success,mips_reg_src);//get reg1 
  assert(success);
  get_reg_val(dest,&success,mips_reg_dest);//get reg2 
  assert(success);*/
  tar_movr2r(mips_regs_name[get_reg_index(dest)], mips_regs_name[get_reg_index(src)]);
}

/*
void trans_mov_la2r(const char *lable,const char *reg)// ->la reg,lable
{
  char mips_reg[4];
  bool success= true;
  //get_reg_val(reg,&success,mips_reg);
  assert(success);
  tar_movla2r(mips_reg,lable);
}
*/

void trans_mov_rm(const char *reg, const char *addr, int size)//register to memory
{
  bool success = false;
  char mips_addr_dest[5];
  //char mips_reg_src[5];
  tar_getaddr(addr, mips_addr_dest);
  //get_reg_val(reg,&success,mips_reg_dest);
  tar_store(mips_regs_name[get_reg_index(reg)], "0", mips_addr_dest, size);
}

void trans_mov_mr(const char *addr, const char *reg, int size)//memory to register
{
  bool success=false;
  //char mips_reg_dest[5];
  char mips_addr_src[5];
  tar_getaddr(addr,mips_addr_src);
  //get_reg_val(reg,&success,mips_reg_dest);
  tar_loadu(mips_regs_name[get_reg_index(reg)], "0", mips_addr_src, size);
}

void trans_mov_im(const char *imm, const char *addr, int size)//imm to memory
{
  char mips_reg[5];
  tar_getaddr(addr, mips_reg);
  tar_movi2r("$t8", imm);
  tar_store("$t8", "0", mips_reg, size);
}
