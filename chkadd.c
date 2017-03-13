#include <assert.h>

extern int delta;
extern int ariane;

/* This prints an "Assertion failed" message and aborts.  */
extern void __assert_fail (const char *__assertion, const char *__file,
			   unsigned int __line, const char *__function)
     __THROW __attribute__ ((__noreturn__));

void chktst()
{
  int local_ariane = 0;
 lab1:
  ariane += delta;
  local_ariane = ariane;


 lab2:
  if (ariane != local_ariane)
    __assert_fail(0, __FILE__, __LINE__, __ASSERT_FUNCTION);
  ariane -= delta;
}
