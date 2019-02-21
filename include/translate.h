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

extern FILE *fp_out;
extern Instr_Table_Entry x86_instr_table[];
extern char *x86_regs_name[];
extern char *mips_regs_name[];
extern char *opnd_type_name[];
extern char *mode_type_name[];

void init_output(char *of_name);
void end_output();
void trans_output(char *label, char *instr, char *argus, char *extra);
int get_reg_index(char *x86_reg);
Oprand_Type get_opnd_type(char *str);

#endif