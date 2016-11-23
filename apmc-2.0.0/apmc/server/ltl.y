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

%nonassoc t_LPAR t_RPAR t_CEIL t_FLOOR t_MIN t_MAX
%left t_QMARK
%left t_DP
%left t_UNTIL
%left t_OR
%left t_AND
%left t_EQUAL t_NEQ
%nonassoc t_TO
%left t_COMMA
%left t_LESS t_LEQ t_GREATER t_GEQ
%left t_PLUS t_MINUS
%left t_TIMES
%left t_DIV
%left t_NEXT
%left t_NOT
%nonassoc t_INTEGER t_ID t_FLOAT t_TRUE t_FALSE


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


expr:
  t_TRUE
{
  $$ = new_expr_by_intcst(1);
}
| t_FALSE
{
  $$ = new_expr_by_intcst(0);
}
|
  t_INTEGER 
{
  $$ = new_expr_by_intcst($1);
}
| t_FLOAT
{
  $$ = new_expr_by_floatcst($1);
}
| t_ID 
{
  $$ = new_expr_by_id($1, SEARCH_IN_FORMULAE | SEARCH_IN_CONSTANTS | SEARCH_IN_VARIABLES);
  if($$ == NULL)
    {
      char msg[128+strlen($1)];
      sprintf(msg, "identifier %s is used but not defined", $1);
      rm_error(msg);
      ifree($1);
      YYABORT;
    }
  ifree($1);
}
| t_NOT expr
{
  $$ = new_expr_by_unary(NOT, $2);
}
| t_NEXT expr
{
  $$ = new_expr_by_unary(NEXT, $2);
}
| t_CEIL t_LPAR expr t_RPAR
{
  $$ = new_expr_by_unary(CEIL, $3);
}
| t_FLOOR t_LPAR expr t_RPAR
{
  $$ = new_expr_by_unary(FLOOR, $3);
}
| t_LPAR expr t_RPAR
{
  $$ = $2;
}
| expr t_AND expr
{
  $$ = new_expr_by_binary($1, AND, $3);
}
| expr t_OR expr
{
  $$ = new_expr_by_binary($1, OR, $3);
}
| expr t_EQUAL expr
{
  $$ = new_expr_by_binary($1, EQUAL, $3);
}
| expr t_EQUAL expr t_COMMA exprlist
{
  struct exprlist *v;

  v = new(struct exprlist);
  v->e = $3;
  v->next = $5;
  $$ = new_equal_el($1, v);
}
| expr t_EQUAL expr t_TO expr
{
  struct exprlist *v;

  v = new_exprlist_range($3, $5);
  if(v==NULL)
    YYABORT;

  $$ = new_equal_el($1, v);
}
|
  expr t_EQUAL expr t_TO expr t_COMMA exprlist
{
  struct exprlist *v, *el;

  el = new_exprlist_range($3, $5);
  if(v == NULL)
    YYABORT;

  for(v=el; v->next; v=v->next);
  v->next = $7;

  $$ = new_equal_el($1, el);
}
| expr t_NEQ expr
{
  $$ = new_expr_by_binary($1, NEQ, $3);
}
| expr t_LESS expr
{
  $$ = new_expr_by_binary($1, LESS, $3);
}
| expr t_GREATER expr
{
  $$ = new_expr_by_binary($1, GREATER, $3);
}
| expr t_LEQ expr
{
  $$ = new_expr_by_binary($1, LEQ, $3);
}
| expr t_GEQ expr
{
  $$ = new_expr_by_binary($1, GEQ, $3);
}
| expr t_PLUS expr
{
  $$ = new_expr_by_binary($1, PLUS, $3);
}
| expr t_MINUS expr
{
  $$ = new_expr_by_binary($1, MINUS, $3);
}
| expr t_TIMES expr
{
  $$ = new_expr_by_binary($1, TIMES, $3);
}
| expr t_DIV expr
{
  $$ = new_expr_by_binary($1, DIV, $3);
}
| expr t_UNTIL expr
{
  $$ = new_expr_by_binary($1, UNTIL, $3);
}
| t_MIN t_LPAR expr t_COMMA expr t_RPAR
{
  $$ = new_expr_by_binary($3, MIN, $5);
}
| t_MAX t_LPAR expr t_COMMA expr t_RPAR
{
  $$ = new_expr_by_binary($3, MAX, $5);
}
| expr t_QMARK expr t_DP expr
{
  $$ = new_expr_by_ternary(ITE, $1, $3, $5);
}
;

exprlist:
  exprrange t_COMMA exprlist
{
  struct exprlist *v;

  $$ = $1;
  for(v = $1; v->next; v = v->next) ;
  v->next = $3;
}
| exprrange
{
  $$ = $1;
}
;

exprrange:
  expr
{
  $$ = new(struct exprlist);
  $$->e = $1;
}
| expr t_TO expr
{
  $$ = new_exprlist_range($1, $3);
}
;


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

