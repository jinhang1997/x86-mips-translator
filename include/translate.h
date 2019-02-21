#ifndef _TRANSLATE_H_
#define _TRANSLATE_H_

typedef struct
{
  char instr[8];
  void (*worker)(char *mode, char *argus[], char *suffix);
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
extern const Instr_Table_Entry x86_instr_table[];
extern const char *x86_regs_name[];
extern const char *mips_regs_name[];
extern const char *opnd_type_name[];
extern const char *mode_type_name[];
extern const char *x86_op_size[];
extern const char *mips_op_size[];

int get_size_by_suf_x86(char suf);
void get_reg_val(const char *s, bool *success, char *mips_reg);
void tar_getaddr(const char *s, char *addr_reg);
void display_reg();
int get_reg_index(const char *x86_reg);
void init_output(char *of_name);
void end_output();
void function_header(char *func_name);
void function_footer(char *func_name);
void trans_output(char *label, char *instr, char *argus, char *extra);
Oprand_Type get_opnd_type(char *str);

#endif