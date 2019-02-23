#ifndef _ALLINSTR_H_
#define _ALLINSTR_H_

#include "mips_target.h"

/* push */
void trans_push(char *mode, char *argus[], char *suffix);
void trans_push_r(char *reg);
void trans_push_i(char *imm);
void trans_push_m(char *addr,int size);

/* pop */
void trans_pop(char *mode, char *argus[], char *suffix);
void trans_pop_r(char *reg);

/* mov */
void trans_mov(char *mode, char *argus[], char *suffix);
void trans_mov_ir(const char *imm,const char *reg);//-> li reg,imm
void trans_mov_rr(const char *src,const char *dest );//->move reg,reg
void trans_mov_la2r(const char *lable,const char *reg);// ->la reg,lable
void trans_mov_rm( const char *reg ,const char *addr, int size );//register to memory
void trans_mov_mr(const char *addr,const char *reg ,int size);//memory to register
void trans_mov_im(const char *imm,const char *addr, int size);//imm to memory

/* lea */
void trans_lea(char *mode, char *argus[], char *suffix);
void trans_lea_mr(const char *addr,const char *reg ,int size);//memory to register

/* ret */
void trans_ret(char *mode, char *argus[], char *suffix);

/* call */
void trans_call(char *mode, char *argus[], char *suffix);
void trans_call_text(char *mode, char *argus[], char *suffix);
void trans_call_plt(char *mode, char *argus[], char *suffix);

/* add */
void trans_add(char *mode, char *argus[], char *suffix);
void trans_add_rr(char * reg1,char * reg2);
void trans_add_ir(char * imm,char * reg);
void trans_add_mr(char * addr,char * reg, int size);
void trans_add_im(char * imm,char * addr, int size);
void trans_add_rm(char * imm,char * addr, int size);

/* sub */
void trans_sub(char *mode, char *argus[], char *suffix);
void trans_sub_rr(char * reg1,char * reg2);
void trans_sub_ir(char * imm,char * reg);
void trans_sub_mr(char * addr,char * reg, int size);
void trans_sub_im(char * imm,char * addr, int size);
void trans_sub_rm(char * imm,char * addr, int size);

/* cmp */
void trans_cmp(char *mode, char *argus[], char *suffix);
void trans_cmp_rr(char * reg1,char * reg2);
void trans_cmp_ir(char * imm,char * reg);
void trans_cmp_mr(char * addr,char * reg, int size);
void trans_cmp_im(char * imm,char * addr, int size);
void trans_cmp_rm(char * imm,char * addr, int size);

/* and */
void trans_and(char *mode, char *argus[], char *suffix);
void trans_and_rr(char * reg1,char * reg2);
void trans_and_ir(char * imm,char * reg);
void trans_and_mr(char * addr,char * reg, int size);
void trans_and_im(char * imm,char * addr, int size);
void trans_and_rm(char * imm,char * addr, int size);

/* jmp */
void trans_jmp(char *mode, char *argus[], char *suffix);

/*leave*/
void trans_leave(char *mode, char *argus[], char *suffix);

/* jcc */
void trans_ja(char *mode, char *argus[], char *suffix);
void trans_jnbe(char *mode, char *argus[], char *suffix);
void trans_jnc(char *mode, char *argus[], char *suffix);
void trans_jae(char *mode, char *argus[], char *suffix);
void trans_jnb(char *mode, char *argus[], char *suffix);
void trans_jc(char *mode, char *argus[], char *suffix);
void trans_jb(char *mode, char *argus[], char *suffix);
void trans_jnae(char *mode, char *argus[], char *suffix);
void trans_jbe(char *mode, char *argus[], char *suffix);
void trans_jna(char *mode, char *argus[], char *suffix);

void trans_jg(char *mode, char *argus[], char *suffix);
void trans_jnle(char *mode, char *argus[], char *suffix);
void trans_jge(char *mode, char *argus[], char *suffix);
void trans_jnl(char *mode, char *argus[], char *suffix);
void trans_jl(char *mode, char *argus[], char *suffix);
void trans_jnge(char *mode, char *argus[], char *suffix);
void trans_jle(char *mode, char *argus[], char *suffix);
void trans_jng(char *mode, char *argus[], char *suffix);

void trans_jz(char *mode, char *argus[], char *suffix);
void trans_je(char *mode, char *argus[], char *suffix);
void trans_jnz(char *mode, char *argus[], char *suffix);
void trans_jne(char *mode, char *argus[], char *suffix);




#endif
