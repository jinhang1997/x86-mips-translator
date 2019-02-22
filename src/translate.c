#include "common.h"
#include "translate.h"
#include "allinstr.h"

FILE *fp_out = NULL;
const Instr_Table_Entry x86_instr_table[] = {
  { "push", trans_push },
  { "mov", trans_mov },
  { "pop",trans_pop },
  { "ret",trans_ret },
  { "call", trans_call },
  { "add",trans_add },
  { "sub",trans_sub },
  { "leave",trans_leave},
};
const char *x86_regs_name[] = { "%eax", "%ecx", "%edx", "%ebx", "%esp", "%ebp", "%esi", "%edi" };
const char *mips_regs_name[] = { "$t0", "$t1", "$t2", "$t3", "$sp", "$t5", "$t6", "$t7" };
const char *opnd_type_name[] = { "OPND_NONE", "OPND_REG", "OPND_IMM", "OPND_MEM" };
const char *mode_type_name[] = { "", "r", "m", "i", "rr", "rm", "mr", "mm", "ir", "im"};
const char *regsl[] = { "eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi" };
const char *regsw[] = { "ax", "cx", "dx", "bx", "sp", "bp", "si", "di" };
const char *regsb[] = { "al", "cl", "dl", "bl", "ah", "ch", "dh", "bh" };
const char *x86_op_size[]={ " ","b","w"," ","l" };
const char *mips_op_size[]={ " ","b","h"," ","w" };

int get_size_by_suf_x86(char suf)
{
  int i;
  for (i=1; i<5; ++i)
  {
    if (x86_op_size[i][0] == suf)
    {
      return i;
    }
  }
  return 4;
}

void get_reg_val(const char *s, bool *success, char *mips_reg)
{
  int i;
  *success = true;
  for (i = 0; i < 8; i ++) {
    if (strcmp(regsl[i], s+1) == 0) {
      mips_reg[0]='$';
      mips_reg[1]='t';
      mips_reg[2]='0'+i;
      mips_reg[3]='\0';
      return;
    }
  }
  for (i = 0; i < 8; i ++) {
    if (strcmp(regsw[i], s+1) == 0) {
      TODO();
       return;
    }
  }
  for (i = 0; i < 8; i ++) {
    if (strcmp(regsb[i], s+1) == 0) {
      TODO();
       return;
    }
  }
  *success = false;
}

/* get the memory address , return in addr_reg */
void tar_getaddr(const char *s,char *addr_reg)
{ 
  bool success= true;
  bool is_offset_exist=false;
  char offset[15];
  if(s[0]!='(')//weather there are offset? 
  is_offset_exist=true;
  
  int len=strlen(s);
  int i,pos,comma_count=0;
  for(i=0;i<len;i++)//get the number of comma
  {
    if(s[i]=='(')
      pos=i+1;  
    
    if(s[i]==',')
      comma_count++; 
  }
  char backet[20];
  strncpy(backet,s+pos,len-pos-1);//get the strig in ()
  if(is_offset_exist)//get the strig of offset
  {
    strncpy(offset,s,pos-1);
  }
  printf("# %s\n",backet);
  char mips_reg[5];
  if(comma_count==0)
  {
    if(backet[0]=='%')//base or other reg  
    {
      //int b_len=strlen(backet);
      get_reg_val(backet,&success,addr_reg);
      assert(success);
      if(!is_offset_exist)
      {
        return;//only register
      }
      strcpy(mips_reg,addr_reg); 
    }
    else // only imm  
    {
      tar_movi2r("$t9",backet);
    }
  }
  else if (comma_count==1)
  {
    char mips_reg_src[5];
    char *r1=strtok(backet,",");
    get_reg_val(r1,&success,mips_reg_src);//get reg1 
      assert(success);
    char *r2=strtok(NULL,",");
    if(r2[0]=='%') //base add other reg
    {
        get_reg_val(r2,&success,mips_reg);//get reg2 
        assert(success);
        tar_addu(mips_reg,mips_reg_src,mips_reg);
    }
    else  //proportion index   
    {
      tar_get_indexaddr(mips_reg,mips_reg_src,r2);
    }
  }
  else if (comma_count==2)
  {
    char mips_reg_base[5];
    char mips_reg_index[5];
    char *r1=strtok(backet,",");
    get_reg_val(r1,&success,mips_reg_base);//get reg1 
      assert(success);
    char *r2=strtok(NULL,",");
    get_reg_val(r2,&success,mips_reg_index);//get reg2 
      assert(success);
      char *imm=strtok(NULL,",");
      tar_get_indexaddr(mips_reg,mips_reg_index,imm);
      tar_addu(mips_reg,mips_reg_base,mips_reg);
  }
  else 
  assert("There are too many commas");
  if(is_offset_exist)
  tar_regaddoff(mips_reg,offset);
  
  strcpy(addr_reg,"$t9");
} 

void display_reg()
{
  int i;
  char mips_reg[3];
  bool success= true;
  for (i = 0; i < 8; i ++) {
  get_reg_val(regsl[i],&success,mips_reg);
    assert(success);
    printf("%s\n",mips_reg );
  }
}

int get_reg_index(const char *x86_reg)
{
  int i;
  for (i=0; i<REG_TYPE_NUM; ++i)
  {
    if (!strcmp(x86_regs_name[i], x86_reg))
    {
      return i;
    }
  }
  return -1;
}

Oprand_Type get_opnd_type(char *str)
{
  int i;
  if (str[0] == '$')
  {
    return OPND_IMM;
  }
  for (i=0; i<REG_TYPE_NUM; ++i)
  {
    if (!strcmp(str, x86_regs_name[i]))
    {
      return OPND_REG;
    }
  }
  return OPND_MEM;
}

void init_output(char *of_name)
{
  char out_file[64];
  sprintf(out_file, "./dumps/out.S");
  Log("mips assembly: %s", out_file);
  fp_out = fopen(out_file, "w");
  fprintf(fp_out, "  .text\n");
}

void end_output()
{
  fclose(fp_out);
}

void function_header(char *func_name)
{
  fprintf(fp_out, "  .globl %s\n", func_name);
  fprintf(fp_out, "  .ent %s\n", func_name);
  fprintf(fp_out, "  .type %s, @function\n", func_name);
  fprintf(fp_out, "%s:\n", func_name);
}

void function_footer(char *func_name)
{
  fprintf(fp_out, "  .end %s\n", func_name);
}

void trans_output(char *label, char *instr, char *argus, char *extra)
{
  char instr_stripped[16], suffix[4];
  char str_argu[64], mode_type[4];
  char *p_argus[3] = { NULL };
  int instr_len = strlen(instr), count_argu = 0;
  int i, flag;

  // print jump label
  if (label)
  {
    fprintf(fp_out, "%s: ", label);
  }

  // analyze operands, prepare str_argu & mode_type
  strcpy(str_argu, argus);
  memset(mode_type, 0x00, sizeof(mode_type));
  for (count_argu=0; count_argu<3; ++count_argu)
  {
    p_argus[count_argu] = strtok(((count_argu == 0)? str_argu: NULL), ","); 
    if (NULL == p_argus[count_argu])
    {
      break;
    }
    mode_type[count_argu] = get_opnd_type(p_argus[count_argu]);
    if ('i' == mode_type[count_argu])
    {
      p_argus[count_argu] = p_argus[count_argu] + 1;
    }
    Log("%s (%c)", p_argus[count_argu], mode_type[count_argu]);
  }
  Log("mode_type: %s", mode_type);
  
  // TODO: analyze extra infomation, usually function names
  if (NULL!=extra && 0!=strcmp(extra, ""))
  {
    p_argus[0] = extra;
  }
  //

  // call working functions
  flag = 0;
  // 1st loop: search treated as no suffix for instr. like `call`
  for (i=0; i<INSTR_NUM; ++i)
  {
    if (!strcmp(x86_instr_table[i].instr, instr))
    {
      (x86_instr_table[i].worker)(mode_type, p_argus, "");
      flag = 1;
      break;
    }
  }
  strcpy(instr_stripped, instr);
  strcpy(suffix, &instr[instr_len-1]);
  instr_stripped[instr_len-1] = '\0';
  // 2st loop: search with 1 letter suffix striped, like `mov/l`
  if (0 == flag)
  {
    for (i=0; i<INSTR_NUM; ++i)
    {
      if (!strcmp(x86_instr_table[i].instr, instr_stripped))
      {
        (x86_instr_table[i].worker)(mode_type, p_argus, suffix);
        flag = 1;
        break;
      }
    }
  }
  strcpy(instr_stripped, instr);
  strcpy(suffix, &instr[instr_len-2]);
  instr_stripped[instr_len-2] = '\0';
  Log("instr:%s suf:%s",instr,suffix);
  // 3st loop: search with 1 letter suffix striped, like `movz/bl`
  if (0 == flag)
  {
    for (i=0; i<INSTR_NUM; ++i)
    {
      if (!strcmp(x86_instr_table[i].instr, instr_stripped))
      {
        (x86_instr_table[i].worker)(mode_type, p_argus, suffix);
        flag = 1;
        break;
      }
    }
  }
}

