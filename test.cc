#include <stdlib.h>

//#define ADD_NOP_AT_SRC_LEVEL 1
#ifdef ADD_NOP_AT_SRC_LEVEL
#define ASM_STMT	__asm__ volatile ("nop\n\t"\
                                          "nop\n\t"\
                                          "nop\n\t"\
                                          "nop\n\t"\
                                          "nop\n\t"\
                                          "nop\n\t"\
                                          "nop\n\t"\
                                          "nop" : );
#else
#define ASM_STMT	/* no __asm__ statement */
#endif

int
foo(int a)
{
  ASM_STMT;
  int b = a;
  for (int i = 0; i < 3; i++)
    b++;

  ASM_STMT;
  if (b > 5)
    {
      ASM_STMT;
      return b;
    }

  ASM_STMT;
  return b+4;
}

int
main(int argc, char **argv)
{
  ASM_STMT;
  int a = 0;
  int b = 0;
  
  ASM_STMT;
  if (argc < 2)
    {
      ASM_STMT;
      return(-1);
    }
  ASM_STMT;
  
  ASM_STMT;
  a = atoi(argv[1]);

  ASM_STMT;
  for (int j = 0; j < 3; j++)
    {
      a++;
      ASM_STMT;
    }

  ASM_STMT;
  if (a < 5)
    {
      b = foo(a);
      ASM_STMT;
    }
  ASM_STMT;

  ASM_STMT;
  switch (a)
    {
    case 8:
      ASM_STMT;
      a+=b;
      ASM_STMT;
      break;
    case 12:
      ASM_STMT;
      a+=100;
      ASM_STMT;
      break;
    default:
      ASM_STMT;
      a+=b+50;
      ASM_STMT;
    }
  ASM_STMT;

  ASM_STMT;
  return a;
}
