%{
#include <string.h>
#include <ctype.h>
#include "reactive-modules.h"
#include "rm.tab.h"
#include "double.h"
extern int rm_lineno;
extern struct pmfile *PMFILE;

int rm_error(char *error);

%}



%%

probabilistic    { return PROBABILISTIC; }
dtmc             { return PROBABILISTIC; }
const            { return CONST; }
rate             { return RATE; }
probability      { return RATE; }
formula          { return FORMULA; }
init             { return INIT; }
\'=              { return NEXT; }
\=               { return EQUAL; }
min              { return MIN; }
max              { return MAX; }
\+[\ \t\n]*[0-9]+\.[0-9]+ { 
  yyless(1); 
  return PROBAND;
}
\+[\ \t\n]*[_a-zA-Z][_a-zA-Z0-9]* { 
  char *p;
  struct pmentry *e;
  char plus_is_exp = 1;
  for(p = rm_text+1; isblank(*p); p++) ;
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
    return PLUS;
  return PROBAND; 
}
\+[\ \t\n]*[0-9]+[\ \t\n]*\/ { yyless(1); return PROBAND; }
\+               { return PLUS; }
\*               { return TIMES; }
[0-9]+\.[0-9]+   { rm_lval.fl=get_double(rm_text);return FLOAT; }
[0-9]+           { rm_lval.integer = strtol(rm_text,NULL,0); return INTEGER; }
\;               { return SC; }
\:               { return DP; }
\,               { return COMMA; }
module           { return MODULE; }
endmodule        { return ENDMODULE; }
\[               { return LBRACKET; }
\]               { return RBRACKET; }
\(               { return LPAR; }
\)               { return RPAR; }
\/               { return DIV; }
\<               { return LESS; }
\>               { return GREATER; }
\>\=             { return GEQ; }
\<\=             { return LEQ; }
\-\>             { return ARROW; }
\!\=             { return NEQ; }
\-               { return MINUS; }
\&               { return AND; }
\|               { return OR; }
\!               { return NOT; }
\.\.             { return TO; }
\n               { rm_lineno++; }
[\ \t]+          {  }
[_a-zA-Z][_a-zA-Z0-9]*   { rm_lval.string = strdup(rm_text); return ID; }
\/\/[^\n]*\n     { rm_lineno++; }
.                { rm_error("lex"); rm_error(rm_text); }

%%

int rm_wrap(void) 
{
  return -1;
}

void lexnowarning(void)
{
  yyunput(0,NULL);
}
