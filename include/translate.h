#ifndef _TRANSLATE_H_
#define _TRANSLATE_H_

typedef struct
{
  char instr[8];
  void (*worker)(char *mode, char *argus[]);
} Instr_Table_Entry;
#define INSTR_NUM sizeof(x86_instr_table) / sizeof(Instr_Table_Entry)

typedef char Oprand_Type;
#define REG_TYPE_NUM 8
enum OPND_TYPE
{
  OPND_NONE = 0,
  OPND_REG = 'r',
  OPND_IMM = 'i',
  OPND_MEM = 'm'
};

#define MOV_TYPE_NUM 10

void init_output(char *of_name);
void end_output();
void trans_output(char *label, char *instr, char *argus, char *extra);

void trans_push(char *mode, char *argus[]);
void trans_push_r(char *reg);

#endif