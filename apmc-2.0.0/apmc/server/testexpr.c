#include <stdio.h>
#include <stdlib.h>
#include "expr.h"

exprlist *LTL;
int ltl_lineno;
extern FILE *ltl_in;

int main(int argc, char *argv[])
{
  exprlist *le;
  char *e;
  int i;

  /* 
   *  extern int ltl_debug;
   *  ltl_debug=1;
   */

  PMFILE = new(pmfile);

  ltl_in = stdin;
  if( ltl_parse() )
    {
      printf("parse error\n");
    }

  i = 0;
  for(le = LTL; le; le = le->next)
    {
      e = generate_expr(stdout, le->e, "(void)");
      fprintf(stdout, "expr%d(void) { return %s;\n }\n", i, e);
      free(e);
      i++;
    }  

  return 0;
}
