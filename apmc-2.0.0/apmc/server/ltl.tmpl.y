%{

extern int ltl_lineno;

#include <stdlib.h>
#include <string.h>

#include "expr.h"

int ltl_lex(void);
int ltl_error(char *error);

extern exprlist *LTL;
void free_LTL();

%}

%token <integer>t_INTEGER
%token <string>t_ID
%token <fl>t_FLOAT
%token t_DP t_QMARK

%union{
  char *string;
  int   integer;
  double fl;

  expr *expr;
  exprlist *el;
}

%start expressions

%type <expr>expr
%type <el>exprlist
%type <el>exprrange

#include_precedence<expr.tmpl.y>

%%

expressions:
{
  LTL = NULL;
}
| expr expressions
{
  exprlist *el;
  el = new(exprlist);
  el->e = $1;
  el->next = LTL;
  LTL = el;
}
;

#include_rules<expr.tmpl.y>

%%

#include <stdio.h>
int ltl_parse();
int ltl_lex(void);
extern FILE *ltl_in;

int ltl_error(char *s) {
  fprintf(stderr, "error in LTL Formula at line %d : %s\n", ltl_lineno, s);
  return 0;
}

static void free_ltl(exprlist *le)
{
  if(le == NULL)
    return;

  icall(free_expr, le->e);
  icall(free_ltl, le->next);
}

void free_LTL()
{
  icall(free_ltl, LTL);
}

