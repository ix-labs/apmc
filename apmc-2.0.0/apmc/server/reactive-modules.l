%{
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "reactive-modules.h"
#include "rm.tab.h"
extern int rm_lineno;
extern struct pmfile *PMFILE;

int rm_error(char *error);
int my_isblank(char c);

%}



%%

probabilistic    { return t_PROBABILISTIC; }
dtmc             { return t_PROBABILISTIC; }
const            { return t_CONST; }
rate             { return t_RATE; }
probability      { return t_RATE; }
formula          { return t_FORMULA; }
init             { return t_INIT; }
\'=              { return t_NEXT_AFF; }
\=               { return t_EQUAL; }
min              { return t_MIN; }
max              { return t_MAX; }
\+[\ \t\n]*[0-9]+\.[0-9]+ {
  yyless(1);
  return t_PROBAND;
}
\+[\ \t\n]*[_a-zA-Z][_a-zA-Z0-9]* {
  char *p;
  struct pmentry *e;
  char plus_is_exp = 1;
  for(p = rm_text+1; my_isblank(*p); p++) ;
  if(PMFILE)
    for(e = PMFILE->constants; e; e=e->next)
      if(e->kind == PMENTRY_CONST)
        if(!strcmp(p, e->u.constant->name))
          {
	    if(e->u.constant->kind == CONST_FLOAT)
	      plus_is_exp = 0;
	    break;
          }
  yyless(1);
  if(plus_is_exp)
    return t_PLUS;
  return t_PROBAND;
}
\+[\ \t\n]*[0-9]+[\ \t\n]*\/ { yyless(1); return t_PROBAND; }
\+               { return t_PLUS; }
\*               { return t_TIMES; }
[0-9]+\.[0-9]+   { rm_lval.fl = strtod(rm_text, NULL); return t_FLOAT; }
[0-9]+           { rm_lval.integer = strtol(rm_text, NULL, 0); return t_INTEGER; }
\;               { return t_SC; }
\:               { return t_DP; }
\?               { return t_QMARK; }
\,               { return t_COMMA; }
module           { return t_MODULE; }
endmodule        { return t_ENDMODULE; }
\[               { return t_LBRACKET; }
\]               { return t_RBRACKET; }
\(               { return t_LPAR; }
\)               { return t_RPAR; }
\/               { return t_DIV; }
\<               { return t_LESS; }
\>               { return t_GREATER; }
\>\=             { return t_GEQ; }
\<\=             { return t_LEQ; }
\-\>             { return t_ARROW; }
\!\=             { return t_NEQ; }
\-               { return t_MINUS; }
\&               { return t_AND; }
\|               { return t_OR; }
\!               { return t_NOT; }
\.\.             { return t_TO; }
ceil             { return t_CEIL; }
floor            { return t_FLOOR; }
\n               { rm_lineno++; }
[\ \t]+          {  }
[_a-zA-Z][_a-zA-Z0-9]*   { rm_lval.string = strdup(rm_text); return t_ID; }
\/\/[^\n]*\n     { rm_lineno++; }
.                { char l[8+strlen(rm_text)]; sprintf(l, "unknown lex character `%s'", rm_text); rm_error(l); }

%%

int my_isblank(char c)
{
  if (c == ' ' || c == '\t')
    return 1;
  return 0;
}

int rm_wrap(void)
{
  return -1;
}

void lexnowarning(void)
{
  yyunput(0,NULL);
}
