#include "common.h"
#include "translate.h"
#include "allinstr.h"
void trans_ja(char *mode, char *argus[], char *suffix)
{
  tar_bgtz("$t9",argus[0]);
}

void trans_jnbe(char *mode, char *argus[], char *suffix)
{
  tar_bgtz("$t9",argus[0]);
}

void trans_jnc(char *mode, char *argus[], char *suffix)
{
  tar_bgez("$t9",argus[0]);
}

void trans_jae(char *mode, char *argus[], char *suffix)
{
  tar_bgez("$t9",argus[0]);
}
void trans_jnb(char *mode, char *argus[], char *suffix)
{
  tar_bgez("$t9",argus[0]);
}

void trans_jc(char *mode, char *argus[], char *suffix)
{
  tar_bltz("$t9",argus[0]);
}
void trans_jb(char *mode, char *argus[], char *suffix)
{
  tar_bltz("$t9",argus[0]);
}
void trans_jnae(char *mode, char *argus[], char *suffix)
{
  tar_bltz("$t9",argus[0]);
}

void trans_jbe(char *mode, char *argus[], char *suffix)
{
  tar_blez("$t9",argus[0]);
}
void trans_jna(char *mode, char *argus[], char *suffix)
{
  tar_blez("$t9",argus[0]);
}




void trans_jg(char *mode, char *argus[], char *suffix)
{
  tar_bgtz("$t8",argus[0]);
}

void trans_jnle(char *mode, char *argus[], char *suffix)
{
  tar_bgtz("$t8",argus[0]);
}

void trans_jge(char *mode, char *argus[], char *suffix)
{
  tar_bgez("$t8",argus[0]);
}

void trans_jnl(char *mode, char *argus[], char *suffix)
{
  tar_bgez("$t8",argus[0]);
}

void trans_jl(char *mode, char *argus[], char *suffix)
{
  tar_bltz("$t8",argus[0]);
}
void trans_jnge(char *mode, char *argus[], char *suffix)
{
  tar_bltz("$t8",argus[0]);
}


void trans_jle(char *mode, char *argus[], char *suffix)
{
  tar_blez("$t8",argus[0]);
}
void trans_jng(char *mode, char *argus[], char *suffix)
{
  tar_blez("$t8",argus[0]);
}


void trans_jz(char *mode, char *argus[], char *suffix)
{
  tar_beq("$t8","$zero",argus[0]);
}

void trans_je(char *mode, char *argus[], char *suffix)
{
  tar_beq("$t8","$zero",argus[0]);
}
void trans_jnz(char *mode, char *argus[], char *suffix)
{
  tar_bne("$t8","$zero",argus[0]);
}

void trans_jne(char *mode, char *argus[], char *suffix)
{
  tar_bne("$t8","$zero",argus[0]);
}



