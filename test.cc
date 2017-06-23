#include <stdio.h>
#include <stdlib.h>

extern int bar(void);

int
foo(int a)
{
  int b = a;
  for (int i = 0; i < 3; i++)
    b++;

  if (b > 5)
    {
      return b;
    }
  else
    b = bar();

  return b+4;
}

int
t2(int a)
{
  asm("nop\n"::);
  return a+1;
}

int
t3(int a)
{
  for (int i = 0; i < a; i++)
    {
      printf("i = %d\n", i);
    }
}

int
t1(int a)
{
  if (a)
    t2(a);
  else
    t3(a);
}

int
main(int argc, char **argv)
{
  int a = 0;
  int b = 0;
  
  if (argc < 2)
    {
      return(-1);
    }
  
  a = atoi(argv[1]);

  for (int j = 0; j < 3; j++)
    {
      a++;
    }

  if (a < 5)
    {
      b = foo(a);
    }

  switch (a)
    {
    case 8:
      a+=b;
      break;
    case 12:
      a+=100;
      break;
    default:
      a+=b+50;
    }

  return a;
}
