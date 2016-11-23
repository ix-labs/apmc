%{

extern int rm_lineno;

#include <stdlib.h>
#include <string.h>
#include "reactive-modules.h"
#include "rm_free.h"

int rm_lex(void);
int rm_error(char *error);
extern struct pmfile *PMFILE;
struct moduledef *CURRENT_MODULE;

%}

%token t_CONST t_EQUAL t_SC t_DP t_COMMA t_MODULE t_ENDMODULE t_LBRACKET 
%token t_RBRACKET t_RATE t_LPAR t_RPAR t_PROBAND t_NEXT_AFF
%token t_ARROW t_AND t_PROBABILISTIC t_TO t_FORMULA 
%token t_INIT 
%token <integer>t_INTEGER
%token <fl>t_FLOAT
%token <string>t_ID

%union{
  char *string;
  int   integer;
  double fl;

  struct pmentry *pmentry;
  struct constdef *constdef;
  struct moduledef *moduledef;
  struct formuladef *formuladef;
  struct expr *expr;
  struct vardef *vardef;
  struct rule *rule;
  struct action *action;
  struct probaff *probaff;
  struct exprlist *el;
  struct affectations *affectations;
  struct renamelist *renamelist;
}

%start pmfile

%type <pmentry>pmentry
%type <integer>pmtype
%type <constdef>constdef
%type <moduledef>moduledef
%type <moduledef>moduleinside
%type <formuladef>formdef
%type <expr>expr
%type <vardef>vardef
%type <rule>rule
%type <string>rulename
%type <probaff>probpart
%type <el>exprlist
%type <el>exprrange
%type <affectations>affectation
%type <affectations>detpart
%type <affectations>affectation_list
%type <renamelist>rename
%type <action>action

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


%nonassoc t_NEXT_AFF
%nonassoc t_PROBAND

%%

pmfile : 
  pmentry 
   { 
     switch($1->kind)
       {
       case PMENTRY_TYPE:
	 PMFILE->kind = $1->u.file_type;
	 break;
       case PMENTRY_CONST:
	 $1->next = PMFILE->constants;
	 if(PMFILE->constants)
	   PMFILE->constants->prev = $1;
	 $1->prev = NULL;
	 PMFILE->constants = $1;
	 break;
       case PMENTRY_MODULE:
	 $1->next = PMFILE->modules;
	 if(PMFILE->modules)
	   PMFILE->modules->prev = $1;
	 $1->prev = NULL;
	 PMFILE->modules = $1;
	 break;
       case PMENTRY_FORM:
	 $1->next = PMFILE->formulas;
	 if(PMFILE->formulas)
	   PMFILE->formulas->prev = $1;
	 $1->prev = NULL;
	 PMFILE->formulas = $1;
	 break;
       }
   } pmfile
   | {}
;

pmentry:
  pmtype
  {
    $$ = new(struct pmentry);
    $$->kind = PMENTRY_TYPE;
    $$->u.file_type = $1;
  }
| constdef
  {
    $$ = new(struct pmentry);
    $$->kind = PMENTRY_CONST;
    $$->u.constant = $1;
  }
| moduledef  
  {
    $$ = new(struct pmentry);
    $$->kind = PMENTRY_MODULE;
    $$->u.module = $1;
  }
| formdef   
  {
    $$ = new(struct pmentry);
    $$->kind = PMENTRY_FORM;
    $$->u.formula = $1;
  }
;

pmtype:
  t_PROBABILISTIC { $$ = PMFILE_PROBABILISTIC; }
  ;

constdef:
  t_CONST t_ID t_EQUAL expr t_SC
{
  $$ = new(struct constdef);
  $$->name = $2;
  $$->kind = CONST_INT;
  $$->u.intvalue = evaluate_intexpr($4, PMFILE->constants);
  icall(free_expr, $4);
}
| t_RATE t_ID t_EQUAL expr t_SC
{
  if( ($4->ekind != CST) && ($4->etype != FLOAT) )
    {
      fprintf(stderr, "bug : in constdef, expr kind = %d not float or cst\n",
	      $4->ekind);
      exit(1);
    }

  $$ = new(struct constdef);
  $$->name = $2;
  $$->kind = CONST_FLOAT;
  $$->u.floatvalue = $4->efloat_value;
  icall(free_expr, $4);
}
  ;

moduledef: t_MODULE t_ID 
{
  CURRENT_MODULE = new(struct moduledef);
  CURRENT_MODULE->modulename = $2;
} 
  moduleinside 
{
  $$ = CURRENT_MODULE;
}
;

moduleinside:
 t_EQUAL t_ID t_LBRACKET rename t_RBRACKET t_ENDMODULE
{
  struct pmentry *m;
  struct renamelist *rl;

  for(m = PMFILE->modules; m; m = m->next)
    if(m->kind == PMENTRY_MODULE)
      if(!strcmp(m->u.module->modulename, $2))
	{
	  CURRENT_MODULE->rules = clone_rules(m->u.module->rules, $4);
	  break;
	}

  for(rl = $4; rl; rl = rl->next)
    if(rl->is_var)
      {
	if( var_is_undef(rl->u.var.into) && !var_is_undef(rl->u.var.what) )
	  {
	    rl->u.var.into->min = rl->u.var.what->min;
	    rl->u.var.into->max = rl->u.var.what->max;
	    rl->u.var.into->initial_value = rl->u.var.what->initial_value;
	    rl->u.var.into->current_value = rl->u.var.what->current_value;	    
	  }
      }

  icall(free_rl, $4);

  if(m)
    {
      $$ = CURRENT_MODULE;
    }
  else
    {
      char msg[128+strlen($2)];
      sprintf(msg, "module %s is used but not defined", $2);
      rm_error(msg);
      YYABORT;
    }
}
|  var_or_rules t_ENDMODULE
{
  $$ = CURRENT_MODULE;
}
;

var_or_rules:
  /* empty */
{

}
|
  vardef var_or_rules 
{   
}
| rule var_or_rules 
{ 
 $1->next = CURRENT_MODULE->rules;
 CURRENT_MODULE->rules = $1;
}
;

vardef:
  t_ID t_DP t_LBRACKET expr t_TO expr t_RBRACKET t_SC
{
  $$ = lookup_or_create_var($1);
  ifree($1);
  $$->min = evaluate_intexpr($4, PMFILE->constants);
  icall(free_expr, $4);
  $$->max = evaluate_intexpr($6, PMFILE->constants);
  icall(free_expr, $6);
  $$->initial_value = $$->min;
  $$->current_value = $$->min;
}
| t_ID t_DP t_LBRACKET expr t_TO expr t_RBRACKET t_INIT expr t_SC
{
  $$ = lookup_or_create_var($1);
  ifree($1);
  $$->min = evaluate_intexpr($4, PMFILE->constants);
  icall(free_expr, $4);
  $$->max = evaluate_intexpr($6, PMFILE->constants);
  icall(free_expr, $6);
  $$->initial_value = evaluate_intexpr($9, PMFILE->constants);
  icall(free_expr, $9);
  $$->current_value = $$->initial_value;
}
;

rule:
  rulename expr t_ARROW action
{
  $$ = new(struct rule);
  $$->stateofrule = $1;
  $$->guard    = $2;

  $$->act      = $4;
}
;

action :  
  probpart
{
  $$ = new(struct action);
  $$->probabilistic = 1;
  $$->u.prob = $1;
}
| detpart
{
  $$ = new(struct action);
  $$->probabilistic = 0;
  $$->u.det = $1;  
}
;

rulename :
  t_LBRACKET t_RBRACKET
{
  $$ = NULL;
}
| t_LBRACKET t_ID t_RBRACKET
{
  $$ = $2;
}
;

probpart:
  expr t_DP affectation_list t_SC
{
  $$ = new(struct probaff);
  $$->proba = $1;
  $$->det   = $3;
}
| expr t_DP affectation_list t_PROBAND probpart
{
  $$ = new(struct probaff);
  $$->proba = $1;
  $$->det   = $3;
  $$->next  = $5;
}
;

affectation_list:
  affectation
{
  $$ = $1;
}
| affectation t_AND affectation_list
{
  $$ = $1;
  $$->next = $3;
}
;

detpart:
  affectation_list t_SC
{
  $$ = $1;
}
;

affectation:
  t_LPAR affectation t_RPAR
{
  $$ = $2;
}
| t_ID t_NEXT_AFF expr
{
  $$ = new(struct affectations);
  $$->id = new_expr_by_id($1, SEARCH_IN_VARIABLES);
  if(!$$->id)
    {
      char msg[128+strlen($1)];
      sprintf(msg, "identifier %s is used but not defined as a variable", $1);
      rm_error(msg);
      ifree($1);
      YYABORT;
    }
  else
    ifree($1);
  $$->exp = $3;
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


rename:
  t_ID t_EQUAL t_ID
{
  $$ = new(struct renamelist);
  if(id_is_synchro($1))
    {
      $$->is_var = 0;
      $$->u.synchro.what = $1;
      $$->u.synchro.into = $3;
    }
  else
    {
      $$->is_var = 1;
      $$->u.var.what = lookup_or_create_var($1);
      free($1);
      $$->u.var.into = lookup_or_create_var($3);
      free($3);
    }
}
|
  t_ID t_EQUAL t_ID t_COMMA rename
{
  $$ = new(struct renamelist);
  if(id_is_synchro($1))
    {
      $$->is_var = 0;
      $$->u.synchro.what = $1;
      $$->u.synchro.into = $3;
    }
  else
    {
      $$->is_var = 1;
      $$->u.var.what = lookup_or_create_var($1);
      free($1);
      $$->u.var.into = lookup_or_create_var($3);
      free($3);
    }
  $$->next = $5;
}
;

formdef:
  t_FORMULA t_ID t_EQUAL expr t_SC
{
  $$ = new(struct formuladef);
  $$->name = $2;
  $$->exp  = $4;
}
;

%%

#include <stdio.h>
int rm_parse();
int rm_lex(void);
extern FILE *rm_in;

int rm_error(char *s) {
  fprintf(stderr, "error in MODEL at line %d : %s\n", rm_lineno, s);
  return 0;
}
