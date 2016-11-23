%{
#include <string.h>
#include <stdlib.h>

#include "expr.h"
#include "ltl.tab.h"
extern int ltl_lineno;

int ltl_error(char *error);

%}

%%

true             { return t_TRUE;}
false            { return t_FALSE;}
U                { return t_UNTIL;}
X                { return t_NEXT;}
\=               { return t_EQUAL; }
min              { return t_MIN; }
max              { return t_MAX; }
\+               { return t_PLUS; }
\*               { return t_TIMES; }
[0-9]+\.[0-9]+   { ltl_lval.fl = strtod(ltl_text, NULL); return t_FLOAT; }
[0-9]+           { ltl_lval.integer = strtol(ltl_text,NULL,0); return t_INTEGER; }
\,               { return t_COMMA; }
\:               { return t_DP; }
\?               { return t_QMARK; }
\(               { return t_LPAR; }
\)               { return t_RPAR; }
\/               { return t_DIV; }
\<               { return t_LESS; }
\>               { return t_GREATER; }
\>\=             { return t_GEQ; }
\<\=             { return t_LEQ; }
\!\=             { return t_NEQ; }
\-               { return t_MINUS; }
\&               { return t_AND; }
\|               { return t_OR; }
\!               { return t_NOT; }
\.\.             { return t_TO; }
ceil             { return t_CEIL; }
floor            { return t_FLOOR; }
\n               { ltl_lineno++; }
[\ \t]+          {  }
[_a-zA-Z][_a-zA-Z0-9]*   { ltl_lval.string = strdup(ltl_text); return t_ID; }
\/\/[^\n]*\n     { ltl_lineno++; }
.                { ltl_error("lex"); ltl_error(ltl_text); }

%%

int ltl_wrap(void) 
{
  return -1;
}
