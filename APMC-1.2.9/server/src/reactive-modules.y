%{

extern int rm_lineno;

#include "reactive-modules.h"
#include "rm_free.h"
#include <stdlib.h>
#include <string.h>

int rm_lex(void);
int rm_error(char *error);
extern struct pmfile *PMFILE;
struct moduledef *CURRENT_MODULE;

%}

%token CONST EQUAL SC DP COMMA MODULE ENDMODULE LBRACKET RBRACKET RATE
%token LPAR RPAR PLUS TIMES PROBAND NEXT ARROW MINUS AND OR NOT PROBABILISTIC 
%token TO FORMULA LESS GREATER LEQ GEQ DIV NEQ MIN MAX INIT
%token <integer>INTEGER
%token <string>ID
%token <fl>FLOAT

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
  struct boolexpr *boolexpr;
  struct action *action;
  struct probaff *probaff;
  struct value_list *vl;
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
%type <fl>floatexp
%type <vardef>vardef
%type <rule>rule
%type <string>rulename
%type <probaff>probpart
%type <boolexpr>boolexpr
%type <vl>valuelist
%type <vl>value
%type <affectations>affectation
%type <affectations>detpart
%type <affectations>affectation_list
%type <expr>expr_or_vl
%type <renamelist>rename

%left NEXT
%left EQUAL NEQ
%left DIV
%left PLUS MINUS
%left TIMES
%left DP
%left OR
%left AND
%left NOT
%left LESS GREATER LEQ GEQ

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
  PROBABILISTIC { $$ = PMFILE_PROBABILISTIC; }
  ;

constdef:
  CONST ID EQUAL expr SC
{
  $$ = new(struct constdef);
  $$->name = $2;
  $$->kind = CONST_INT;
  $$->u.intvalue = evaluate_expression($4, PMFILE->constants);
  icall(free_expression, $4);
}
| RATE ID EQUAL floatexp SC
{
  $$ = new(struct constdef);
  $$->name = $2;
  $$->kind = CONST_FLOAT;
  $$->u.floatvalue = $4;
}
  ;

moduledef: MODULE ID 
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
 EQUAL ID LBRACKET rename RBRACKET ENDMODULE
{
  struct pmentry *m;
  struct vardef *v, *vp;
  struct renamelist *rl;
  for(m = PMFILE->modules; m; m = m->next)
    if(m->kind == PMENTRY_MODULE)
      if(!strcmp(m->u.module->modulename, $2))
	{
	  CURRENT_MODULE->rules = clone_rules(m->u.module->rules, $4);
	  break;
	}
  for(rl = $4; rl; rl = rl->next)
    {
      for(v = PMFILE->variables; v; v = v->next)
	if( !strcmp(rl->into, v->name) )
	  if( (v->min == 0) && (v->max == -1) )
	    {
	      for(vp = PMFILE->variables; vp; vp = vp->next)
		if( !strcmp(vp->name, rl->what) )
		  {
		    v->min = vp->min;
		    v->max = vp->max;
		    v->initial_value = vp->initial_value;
		  }
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
|  var_or_rules ENDMODULE
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
  /*
  $1->next = PMFILE->variables;
  PMFILE->variables = $1;
  */
}
| rule var_or_rules 
{ 
 $1->next = CURRENT_MODULE->rules;
 CURRENT_MODULE->rules = $1;
}
;

vardef:
  ID DP LBRACKET expr TO expr RBRACKET SC
{
  struct identifier *id;
  id = new_id_by_name($1, 0);
  if(id && (id->kind = ID_VAR) && (id->u.var->min == 0) && (id->u.var->max == -1))
    {
      $$ = id->u.var;
      id->u.var->min = evaluate_expression($4, PMFILE->constants);
      id->u.var->max = evaluate_expression($6, PMFILE->constants);
      id->u.var->initial_value = id->u.var->min;
    }
  else
    {
      $$ = new(struct vardef);
      $$->name = $1;
      $$->min = evaluate_expression($4, PMFILE->constants);
      $$->max = evaluate_expression($6, PMFILE->constants);
      $$->initial_value = $$->min;
      $$->next = PMFILE->variables;
      PMFILE->variables = $$;
    }
  ifree($1);
  icall(free_expression, $4);
  icall(free_expression, $6);
  ifree(id);
}
| ID DP LBRACKET expr TO expr RBRACKET INIT expr SC
{
  struct identifier *id;
  id = new_id_by_name($1, 0);
  if(id && (id->kind = ID_VAR) && (id->u.var->min == 0) && (id->u.var->max == -1))
    {
      $$ = id->u.var;
      id->u.var->min = evaluate_expression($4, PMFILE->constants);
      id->u.var->max = evaluate_expression($6, PMFILE->constants);
      id->u.var->initial_value = evaluate_expression($9, PMFILE->constants);
    }
  else
    {
      $$ = new(struct vardef);
      $$->name = $1;
      $$->min = evaluate_expression($4, PMFILE->constants);
      $$->max = evaluate_expression($6, PMFILE->constants);
      $$->initial_value = evaluate_expression($9, PMFILE->constants);
      $$->next = PMFILE->variables;
      PMFILE->variables = $$;
    }
  ifree($1);
  icall(free_expression, $4);
  icall(free_expression, $6);
  icall(free_expression, $9);
  ifree(id);
}
;

rule:
  rulename boolexpr ARROW probpart
{
  $$ = new(struct rule);
  $$->stateofrule = $1;
  $$->guard    = $2;
  $$->act      = new(struct action);
  $$->act->probabilistic = 1;
  $$->act->u.prob = $4;
}
| rulename boolexpr ARROW detpart
{
  $$ = new(struct rule);
  $$->stateofrule = $1;
  $$->guard    = $2;
  $$->act      = new(struct action);
  $$->act->probabilistic = 0;
  $$->act->u.det = $4;
}
;

rulename :
  LBRACKET RBRACKET
{
  $$ = NULL;
}
| LBRACKET ID RBRACKET
{
  $$ = $2;
}
;

probpart:
  floatexp DP affectation_list SC
{
  $$ = new(struct probaff);
  $$->proba = $1;
  $$->det   = $3;
}
| floatexp DP affectation_list PROBAND probpart
{
  $$ = new(struct probaff);
  $$->proba = $1;
  $$->det   = $3;
  $$->next  = $5;
}
;

floatexp:
  FLOAT
{
  $$ = $1;
}
| ID
{
  struct pmentry *c;
  for(c = PMFILE->constants; c; c=c->next)
    if( c->kind == PMENTRY_CONST)
      if( !strcmp(c->u.constant->name, $1) ) 
      {
	if(c->u.constant->kind == CONST_FLOAT)
	  $$ = c->u.constant->u.floatvalue;
	else
	  $$ = (double)c->u.constant->u.intvalue;
	break;
      }
  if(!c)
    {
      char msg[128+strlen($1)];
      sprintf(msg, "float expression error - %s is not defined\n", $1);
      rm_error(msg);
      ifree($1);
      YYABORT;
    }
  else
    ifree($1);
}
| INTEGER
{
  $$ = (double)$1;
}
| floatexp DIV floatexp
{
  $$ = $1 / $3;
}
;

affectation_list:
  affectation
{
  $$ = $1;
}
| affectation AND affectation_list
{
  $$ = $1;
  $$->next = $3;
}
;

detpart:
  affectation_list SC
{
  $$ = $1;
}
;

affectation:
  LPAR affectation RPAR
{
  $$ = $2;
}
| ID NEXT expr
{
  $$ = new(struct affectations);
  $$->id = new_id_by_name($1, 0);
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
  INTEGER 
{
  $$ = new(struct expr);
  $$->kind = E_CSTE;
  $$->u.cste = $1;
}
| ID 
{
  $$ = new(struct expr);
  $$->kind = E_ID;
  $$->u.id = new_id_by_name($1, 1);
  ifree($1);
}
| LPAR expr RPAR
{
  $$ = $2;
}
| expr PLUS expr
{
  $$ = new(struct expr);
  $$->kind = E_BINARY;
  $$->u.binary.op = E_BIN_PLUS;
  $$->u.binary.left = $1;
  $$->u.binary.right = $3;
}
| MIN LPAR expr COMMA expr RPAR
{
  $$ = new(struct expr);
  $$->kind = E_BINARY;
  $$->u.binary.op = E_BIN_MIN;
  $$->u.binary.left = $3;
  $$->u.binary.right = $5;
}
| MAX LPAR expr COMMA expr RPAR
{
  $$ = new(struct expr);
  $$->kind = E_BINARY;
  $$->u.binary.op = E_BIN_MAX;
  $$->u.binary.left = $3;
  $$->u.binary.right = $5;
}
| expr TIMES expr
{
  $$ = new(struct expr);
  $$->kind = E_BINARY;
  $$->u.binary.op = E_BIN_TIMES;
  $$->u.binary.left = $1;
  $$->u.binary.right = $3;  
}
| expr MINUS expr
{
  $$ = new(struct expr);
  $$->kind = E_BINARY;
  $$->u.binary.op = E_BIN_MINUS;
  $$->u.binary.left = $1;
  $$->u.binary.right = $3;
}
;

expr_or_vl:
value COMMA valuelist
{
  $$ = new(struct expr);
  $$->kind = E_VL;
  $$->u.vl = vl_append($1, $3);
}
|
INTEGER TO INTEGER
{
  if($1 > $3)
    {
      char msg[256];
      sprintf(msg, "value range is not coherent [%d..%d]\n", $1, $3);
      rm_error(msg);
      YYABORT;
    }
  else
    {
      $$ = new(struct expr);
      $$->kind = E_VL;
      $$->u.vl = vl_build($1, $3);
    }
}
|
expr
{
  $$ = $1;
}
;

boolexpr:
  NOT boolexpr
{
  $$ = new(struct boolexpr);
  $$->kind = BE_UNARY;
  $$->u.unary.op = BE_UNARY_NOT;
  $$->u.unary.exp = $2;
}
| boolexpr AND boolexpr
{
  $$ = new(struct boolexpr);
  $$->kind = BE_LOG_BINARY;
  $$->u.binary.op = BE_BIN_AND;
  $$->u.binary.left = $1;
  $$->u.binary.right = $3;
}
| boolexpr OR boolexpr
{
  $$ = new(struct boolexpr);
  $$->kind = BE_LOG_BINARY;
  $$->u.binary.op = BE_BIN_OR;
  $$->u.binary.left = $1;
  $$->u.binary.right = $3;
}
| ID
{
  struct pmentry *c;  
 
  for(c = PMFILE->formulas; c; c=c->next)
    if(c->kind == PMENTRY_FORM)
      if(!strcmp(c->u.formula->name, $1))
	{
	  $$ = new(struct boolexpr);
	  $$->kind=BE_FORMULA;
	  $$->u.formula=c->u.formula;
	  break;
	}
  if(!c)
    {
      char msg[128+strlen($1)];
      sprintf(msg, "%s is not the ID of a formula", $1);
      rm_error(msg);
      ifree($1);
      YYABORT;
    }
  else
    ifree($1);
}
| expr EQUAL expr_or_vl
{
  if( $3->kind == E_VL)
    {
      struct value_list *vl;
      struct boolexpr *n;

      $$ =  new(struct boolexpr);
      $$->kind = BE_EXP_BINARY;
      $$->u.exp_binary.op = BE_EBIN_EQ;
      $$->u.exp_binary.left = clone_expression($1, NULL);
      $$->u.exp_binary.right = new_exp_from_int($3->u.vl->value);
      for(vl = $3->u.vl->next; vl; vl = vl->next)
	{
	  n = new(struct boolexpr);
	  n->kind = BE_LOG_BINARY;
	  n->u.binary.op   = BE_BIN_OR;
	  n->u.binary.left = $$;
	  n->u.binary.right = new(struct boolexpr);
	  n->u.binary.right->kind = BE_EXP_BINARY;
	  n->u.binary.right->u.exp_binary.op = BE_EBIN_EQ;
	  n->u.binary.right->u.exp_binary.left = clone_expression($1, NULL);
	  n->u.binary.right->u.exp_binary.right = new_exp_from_int(vl->value);
	  $$ = n;
	}
      icall(free_expression, $3);
    }
  else
    {  
      $$ = new(struct boolexpr);
      $$->kind = BE_EXP_BINARY;
      $$->u.exp_binary.op = BE_EBIN_EQ;
      $$->u.exp_binary.left = $1;
      $$->u.exp_binary.right = $3;
    }
}
| expr NEQ expr
{
  $$ = new(struct boolexpr);
  $$->kind = BE_EXP_BINARY;
  $$->u.exp_binary.op = BE_EBIN_NEQ;
  $$->u.exp_binary.left = $1;
  $$->u.exp_binary.right = $3;
}
| expr LESS expr
{
  $$ = new(struct boolexpr);
  $$->kind = BE_EXP_BINARY;
  $$->u.exp_binary.op = BE_EBIN_LESSER;
  $$->u.exp_binary.left = $1;
  $$->u.exp_binary.right = $3;
}
| expr GREATER expr
{
  $$ = new(struct boolexpr);
  $$->kind = BE_EXP_BINARY;
  $$->u.exp_binary.op = BE_EBIN_GREATER;
  $$->u.exp_binary.left = $1;
  $$->u.exp_binary.right = $3;
}
| expr LEQ expr
{
  $$ = new(struct boolexpr);
  $$->kind = BE_EXP_BINARY;
  $$->u.exp_binary.op = BE_EBIN_LEQ;
  $$->u.exp_binary.left = $1;
  $$->u.exp_binary.right = $3;
}
| expr GEQ expr
{
  $$ = new(struct boolexpr);
  $$->kind = BE_EXP_BINARY;
  $$->u.exp_binary.op = BE_EBIN_GEQ;
  $$->u.exp_binary.left = $1;
  $$->u.exp_binary.right = $3;
}
| LPAR boolexpr RPAR
{
  $$ = $2;
}
;

valuelist:
value
{
  $$ = $1;
}
| value COMMA valuelist
{
  $$ = vl_append($1, $3);
}
;

value:
  INTEGER
{
  $$ = new(struct value_list);
  $$->value = $1;
}
| INTEGER TO INTEGER
{
  if($1 > $3)
    {
      char msg[256];
      sprintf(msg, "value range is not coherent [%d..%d]", $1, $3);
      rm_error(msg);
      YYABORT;
    }
  else
    $$ = vl_build($1, $3);
}
;

rename:
  ID EQUAL ID
{
  $$ = new(struct renamelist);
  $$->what = $1;
  $$->into = $3;
}
|
  ID EQUAL ID COMMA rename
{
  $$ = new(struct renamelist);
  $$->what = $1;
  $$->into = $3;
  $$->next = $5;
}
;

formdef:
  FORMULA ID EQUAL boolexpr SC
{
  $$ = new(struct formuladef);
  $$->name = $2;
  $$->expr = $4;
}
  ;

%%

#include <stdio.h>
int rm_parse();
int rm_lex(void);
extern FILE *rm_in;

int rm_error(char *s) {
  fprintf(stderr, "error at line %d : %s\n", rm_lineno, s);
  return 0;
}
