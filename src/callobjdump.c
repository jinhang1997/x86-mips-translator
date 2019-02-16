#include "common.h"

int call_objdump()
{
  if ((pid = fork()) == -1)
  {
    return -1;
  }
  else if (pid == 0)
  {
    //printf("pid = %d\n", pid);
    execvp("objdump", argv);
    exit(EXIT_SUCCESS);
  }
  else
  {
    //printf("pid = %d\n", pid);
    wait(&status);
    //printf("status = %d\n", status);
    return WEXITSTATUS(status);
  }
}