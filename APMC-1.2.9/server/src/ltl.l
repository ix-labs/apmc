%{
#include "ltl.tab.h"
extern int ltl_lineno;

int ltl_error(char*);

%}

%%
true             { return TRUE;}
false            { return FALSE;}
U                { return UNTIL;}
X                { return NEXT;}
\=               { return EQUAL; }
[0-9]+           { ltl_lval.integer = atoi(ltl_text); return INTEGER; }
\(               { return LPAR; }
\)               { return RPAR; }
\+               { return PLUS; }
\<               { return LESS; }
\>               { return GREATER; }
\>\=             { return GEQ; }
\<\=             { return LEQ; }
\-               { return MINUS; }
\&               { return AND; }
\|               { return OR; }
\!               { return NOT; }
\n               { ltl_lineno++; }
[\ \t]+          {  }
[_a-zA-Z][_a-zA-Z0-9]*   { ltl_lval.string = ltl_text; return ID; }
\/\/[^\n]*\n     { ltl_lineno++; }
.                { ltl_error("lex"); ltl_error(ltl_text); };

%%

void lex_no_warning(void) {
  yyunput(0, NULL);
}

int ltl_wrap(void) {
  return -1;
}

