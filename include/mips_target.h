#ifndef _MIPS_TARGET_H
#define _MIPS_TARGET_H

#include "translate.h"

static inline void tar_movi2r(const char *reg,const char *imm)
{
  fprintf(fp_out, "  li  %s,%s\n",reg,imm);
}

static inline void tar_movr2r(const char *dest,const char *src)
{
  fprintf(fp_out, "  move  %s,%s\n",dest,src);
}
 
static inline void tar_movla2r(const char *s,const char *lable)
{
  fprintf(fp_out, "  la  %s,%s\n",s,lable);
}
static inline void tar_add(const char *rd,const char* rs, const char* rt)
{
  fprintf(fp_out, "  add  %s,%s,%s\n",rd,rs,rt);  
}
static inline void tar_addu(const char *rd,const char* rs, const char* rt)
{
  fprintf(fp_out, "  addu  %s,%s,%s\n",rd,rs,rt);  
}

static inline void tar_addi(const char *rt,const char* rs, const char* imm)
{
  fprintf(fp_out, "  addi  %s,%s,%s\n",rt,rs,imm);  
}

static inline void tar_addiu(const char *rt,const char* rs, const char* imm)
{
  fprintf(fp_out, "  addiu  %s,%s,%s\n",rt,rs,imm);    
}
static inline void tar_sub(const char *rd,const char* rs, const char* rt)
{
	fprintf(fp_out, "  sub	%s,%s,%s\n",rd,rs,rt);	
}
static inline void tar_subu(const char *rd,const char* rs, const char* rt)
{
	fprintf(fp_out, "  subu  %s,%s,%s\n",rd,rs,rt);  
}


static inline void tar_sll(const char *rd,const char* rs, const char* rt)
{
  fprintf(fp_out, "  sll  %s,%s,%s\n",rd,rs,rt); 
}
 static inline void tar_jr(const char* rs)
{
  fprintf(fp_out, "  jr  %s\n",rs); 
}
 
static inline void tar_load(const char* rt,const char* offset,const char* rs ,int size)
{
  fprintf(fp_out, "  l%s  %s,%s(%s)\n",mips_op_size[size],rt,offset,rs);
}

static inline void tar_store(const char* rt,const char* offset,const char* rs ,int size)
{
  fprintf(fp_out, "  s%s  %s,%s(%s)\n",mips_op_size[size],rt,offset,rs);
}

static inline void tar_loadu(const char* rt,const char* offset,const char* rs ,int size)
{
  fprintf(fp_out, "  l%su  %s,%s(%s)\n",mips_op_size[size],rt,offset,rs);
}
 
static inline void tar_regaddoff(const char *reg,const char* offset)  // get the code of reg=reg+offset
{
  tar_movi2r("$t9",offset);
  tar_addu("$t9",reg,"$t9");
}
 
static inline void tar_get_indexaddr(char* dest,const char *src,const char* imm)
{
  const char* proportion[]={"1","2","4","8"};
  char index[2];
  int i;
  for (i = 0; i < 4; i ++) 
  if (strstr(imm,proportion[i])!=NULL) 
  {
      sprintf(index,"%d",i);
      break;
  }
  strcpy(dest,"$t8");//temp is $t8 
  tar_sll(dest,src,index);
}

#endif
