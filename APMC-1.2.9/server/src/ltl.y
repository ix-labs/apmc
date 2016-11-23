%{
#include <string.h>    
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <stdlib.h>
    
#include "path.h"
#include "reactive-modules.h"             

extern int ltl_lineno;

  struct ltl_expr * new_binary( char op, struct ltl_expr *left, struct ltl_expr *right)
    {
      struct ltl_expr *n = (struct ltl_expr *)calloc(1, sizeof(struct ltl_expr));
      n->kind = LTL_BINARY;
      n->u.binary.op = op;
      n->u.binary.left = left;
      n->u.binary.right = right;
      return n;
    }

  struct ltl_expr * new_unary( char op, struct ltl_expr *exp)
    {
      struct ltl_expr *n = (struct ltl_expr *)calloc(1, sizeof(struct ltl_expr));
      n->kind = LTL_UNARY;
      n->u.unary.op = op;
      n->u.unary.exp = exp;
      return n;
    }
  
  struct ltl_expr * new_id( char *name )
    {
      struct ltl_expr *n = (struct ltl_expr *)calloc(1, sizeof(struct ltl_expr));
      n->kind = LTL_VARIABLE;
      n->u.id.index=-1;
      n->u.id.name = strdup(name);
      return n;
    }

  struct ltl_expr * new_const( int value )
    {
      struct ltl_expr *n = (struct ltl_expr *)calloc(1, sizeof(struct ltl_expr));
      n->kind = LTL_CONSTANT;
      n->u.cst.value = value;
      return n;
    }

 extern struct ltl_expr *LTL;

%}

%token TRUE FALSE EQUAL LPAR RPAR PLUS LESS GREATER LEQ GEQ MINUS
%token AND OR UNTIL
%token <integer>INTEGER
%token <string>ID


%left LESS 
%left GREATER 
%left LEQ 
%left GEQ
%token NEXT 
%left UNTIL
%token NOT
%left AND
%left OR 
%left PLUS 
%left MINUS 

%union{
  char *string;
  int   integer;
  struct ltl_expr *exp;
}

%type <exp>prop 
%type <exp>prop_atom 
%type <exp>ltl_expr

%start pre_prop

%%

pre_prop : prop { LTL = $1; }
;

prop : 
prop_atom          { $$ = $1; }
|  prop OR prop    { $$ = new_binary('|', $1, $3); }
|  prop AND prop   { $$ = new_binary('&', $1, $3); }
|  NOT  prop       { $$ = new_unary ('!', $2    ); }
|  prop UNTIL prop { $$ = new_binary('U', $1, $3); }
|  NEXT prop       { $$ = new_unary ('N', $2    ); }
|  LPAR prop RPAR  { $$ = $2; } 
;


prop_atom:
  LPAR ltl_expr EQUAL ltl_expr RPAR   { $$ = new_binary('=', $2, $4); }
| LPAR ltl_expr GREATER ltl_expr RPAR { $$ = new_binary('>', $2, $4); }
| LPAR ltl_expr LESS ltl_expr RPAR    { $$ = new_binary('<', $2, $4); }
| LPAR ltl_expr GEQ ltl_expr RPAR     { $$ = new_binary('g', $2, $4); }
| LPAR ltl_expr LEQ ltl_expr RPAR     { $$ = new_binary('l', $2, $4); }
| TRUE                                { $$ = new_const( 1 ); }
| FALSE                               { $$ = new_const( 0 ); }
;

ltl_expr:
INTEGER                   { $$ = new_const( $1 ); }
| ID                      { $$ = new_id( $1 ); }
| ltl_expr PLUS ltl_expr  { $$ = new_binary('+', $1, $3); }
| ltl_expr MINUS ltl_expr { $$ = new_binary('-', $1, $3); }
| LPAR ltl_expr RPAR      { $$ = $2; }
;

%%

int ltl_error(char *s) {
  printf("error at line %d : %s\n", ltl_lineno, s);
  return 0;
}

void display_ltl_expression(struct ltl_expr *e, int level)
{
  int i;
  
  switch(e->kind) {
  case LTL_BINARY:
    display_ltl_expression(e->u.binary.left, level+1);
    for(i = 0; i < level; i++) printf("  "); 
    printf("%c\n", e->u.binary.op);
    display_ltl_expression(e->u.binary.right, level+1);
    break;
  case LTL_UNARY:
    for(i = 0; i < level; i++) printf("  ");
    printf("%c\n", e->u.unary.op);
    display_ltl_expression(e->u.unary.exp, level+1);
    break;
  case LTL_CONSTANT:
    for(i = 0; i < level; i++) printf("  ");
    printf("%d\n", e->u.cst.value);
    break;
  case LTL_VARIABLE:
    for(i = 0; i < level; i++) printf("  ");
    printf("%s\n", e->u.id.name);
    break;
  default:
    for(i = 0; i < level; i++) printf("  ");
    printf("unknown kind (%x)\n", e->kind);
  }
}

static void free_ltl(struct ltl_expr *e)
{
  switch(e->kind) {
  case LTL_BINARY:
    icall(free_ltl, e->u.binary.left);
    icall(free_ltl, e->u.binary.right);
    break;
  case LTL_UNARY:
    icall(free_ltl, e->u.unary.exp);
    break;
  default:
    break;
  }
}

void free_LTL()
{
  icall(free_ltl, LTL);
}

void display_flat_ltl_expression(struct ltl_expr *e)
{
  switch(e->kind) {
  case LTL_BINARY:
    printf("(");
    display_flat_ltl_expression(e->u.binary.left);
    printf("%c", e->u.binary.op);
    display_flat_ltl_expression(e->u.binary.right);
    printf(")");
    break;
  case LTL_UNARY:
    printf("%c", e->u.unary.op);
    printf("(");
    display_flat_ltl_expression(e->u.unary.exp);
    printf(")");
    break;
  case LTL_CONSTANT:
    printf("%d", e->u.cst.value);
    break;
  case LTL_VARIABLE:
    printf("%s", e->u.id.name);
    break;
  default:
    fprintf(stderr, "unknown kind (%x)\n", e->kind);
  }
}

void decore_tree(path *s,struct ltl_expr *e)
{
  int i;
  switch(e->kind) 
    {
    case LTL_BINARY:
      decore_tree(s,e->u.binary.left);
      decore_tree(s,e->u.binary.right);
      break;
    case LTL_UNARY:
      decore_tree(s,e->u.unary.exp);
      break;
    case LTL_CONSTANT:
      break;
    case LTL_VARIABLE:
      for (i=0;i<s->nb_vars;i++)
	if (!strcmp(s->variables[i],e->u.id.name))
	  {
	    e->u.id.index=i;
	    break;
	  }
      break;
    }
}

int decore_tree2(struct vardef *v, struct ltl_expr *e)
{
  int i;
  struct vardef *p;

  switch(e->kind) 
    {
    case LTL_BINARY:
      return decore_tree2(v, e->u.binary.left) &&
	decore_tree2(v, e->u.binary.right);
    case LTL_UNARY:
      return decore_tree2(v, e->u.unary.exp);
    case LTL_CONSTANT:
      return 1;
    case LTL_VARIABLE:
      for (p = v, i = 0; p; p = p->next, i++)
	{
	  if (!strcmp(p->name, e->u.id.name))
	    {
	      e->u.id.index=i;
	      return 1;
	    }
	}
      return 0;
    }
  return 0;
}

static int ltl_function_number;

char *generate_ltl_expr(FILE *out, ltl_expr *e)
{
  char *v = NULL;
  char *l, *r;

  switch(e->kind) 
    {
    case LTL_BINARY:
      l = generate_ltl_expr(out, e->u.binary.left);
      r = generate_ltl_expr(out, e->u.binary.right);
      if(!l || !r)
	{
	  if(l) free(l);
	  if(r) free(r);
	  return NULL;
	}
      v = (char *)malloc(12+strlen(l)+strlen(r));
      switch(e->u.binary.op)
	{
	case '+':
	  sprintf(v, "(%s)+(%s)", l, r);
	  break;
	case '-':
	  sprintf(v, "(%s)-(%s)", l, r);
	  break;
	case '=':
	  sprintf(v, "(%s)==(%s)", l, r);
	  break;
	case '&':
	  sprintf(v, "(%s)&&(%s)", l, r);
	  break;
	case '|':
	  sprintf(v, "(%s)||(%s)", l, r);
	  break;
	case '>':
	  sprintf(v, "(%s)>(%s)", l, r);
	  break;
	case '<':
	  sprintf(v, "(%s)<(%s)", l, r);
	  break;
	case 'g':
	  sprintf(v, "(%s)>=(%s)", l, r);
	  break;
	case 'l':
	  sprintf(v, "(%s)<=(%s)", l, r);
	  break;
	case 'U':
	  fprintf(out, "static int ltl_%d(conf *c)\n{\n  if(!c) return 0;\n  return %s;\n}\n\n", ltl_function_number++, l);
	  fprintf(out, "static int ltl_%d(conf *c)\n{\n  if(!c) return 0;\n  return %s;\n}\n\n", ltl_function_number++, r);
	  v = (char*)malloc(96);
	  sprintf(v, "until(ltl_%d, ltl_%d, c)", ltl_function_number-2, ltl_function_number-1);
	  break;
	default:
	  fprintf(stderr, "binary operator %c is not implemented yet\n",e->u.binary.op);
	}
      free(l); free(r);
      break;
    case LTL_UNARY:
      r = generate_ltl_expr(out, e->u.unary.exp);
      if(!r) return NULL;
      switch(e->u.unary.op)
	{
	case 'N':
	  fprintf(out, "static int ltl_%d(conf *c)\n{\n  if(!c) return 0;\n  return %s;\n}\n\n", ltl_function_number++, r);
	  v = (char*)malloc(64);
	  sprintf(v, "next(ltl_%d, c)", ltl_function_number-1);
	  break;
	case '!':
	  v = (char*)malloc(strlen(r)+6);
	  sprintf(v, "!(%s)", r);
	  break;
	default:
	  fprintf(stderr, "unary operator %c is not implemented yet\n",e->u.unary.op);
	}
      free(r);
      break;
    case LTL_CONSTANT:
      v = (char*)malloc(12);
      sprintf(v, "%d", e->u.cst.value);
      break;
    case LTL_VARIABLE:
      v = (char*)malloc(64);
      sprintf(v, "c->values[%d]", e->u.id.index);
      break;
    }
  return v;
}

int generate_verifier(FILE *out, struct vardef *v, ltl_expr *e)
{
  char *exp_str;

  if( !decore_tree2(v, e) )
    return -1;

  ltl_function_number = 0;
  exp_str = generate_ltl_expr(out, e);
  if(!exp_str)
    return -1;

  fprintf(out, "inline static int verify_path(conf *c)\n{\n  return (%s);\n}\n\n", exp_str);
  free(exp_str);
  return 0;
}

int verify_path(conf *c,ltl_expr *e)
{
  int cond;
#ifdef DEBUG_VERIF
  static int level = 0;
  int i;
#endif
  int res;
  if (c==NULL)
    return 0;

#ifdef DEBUG_VERIF
  for(i = 0; i < level; i++) printf(" ");
  printf("verifying :[");
  display_flat_ltl_expression(e);
  printf("\n");
  level++;
#endif

  switch(e->kind) 
    {
    case LTL_BINARY:
      switch(e->u.binary.op)
	{
	case '+':
	  res = verify_path(c,e->u.binary.left)+verify_path(c,e->u.binary.right);
	  goto ret;
	case '-':
	  res = verify_path(c,e->u.binary.left)-verify_path(c,e->u.binary.right);
	  goto ret;
	case '=':
	  res = ((verify_path(c,e->u.binary.left))==(verify_path(c,e->u.binary.right)));
	  goto ret;
	case '&':
	  res = verify_path(c,e->u.binary.left)&&verify_path(c,e->u.binary.right);
	  goto ret;
	case '|':
	  res = verify_path(c,e->u.binary.left)||verify_path(c,e->u.binary.right);
	  goto ret;
	case '>':
	  res = verify_path(c,e->u.binary.left)>verify_path(c,e->u.binary.right);
	  goto ret;
	case '<':
	  res = verify_path(c,e->u.binary.left)<verify_path(c,e->u.binary.right);
	  goto ret;
	case 'g':
	  res = verify_path(c,e->u.binary.left)>=verify_path(c,e->u.binary.right);
	  goto ret;
	case 'l':
	  res = verify_path(c,e->u.binary.left)<=verify_path(c,e->u.binary.right);
	  goto ret;
	case 'U':
	    /*print_conf(c);*/
	  cond=verify_path(c,e->u.binary.right);
	  if (cond)
	    {
	      res = 1;
	      goto ret;
	    }
	  cond=verify_path(c,e->u.binary.left);
	  if (!cond)
	    {
	      res = 0;
	      goto ret;
	    }
	  cond=verify_path(c->next,e->u.binary.right);
	  if (cond)
	    {
	      res = 1;
	      goto ret;
	    }
	  cond=verify_path(c->next,e);
	  res = cond;
	  goto ret;
	default:
	  fprintf(stderr, "binary operator %c is not implemented yet\n",e->u.binary.op);
	}
      break;
    case LTL_UNARY:
      switch(e->u.unary.op)
	{
	case 'N':
	  res = verify_path(c->next,e->u.unary.exp);
	  goto ret;
	case '!':
	  res = (!(verify_path(c,e->u.unary.exp)));
	  goto ret;
	default:
	  fprintf(stderr, "unary operator %c is not implemented yet\n",e->u.unary.op);
	}
      break;
    case LTL_CONSTANT:
      /*printf("constant : %d\n",e->u.cst.value);*/
      res = e->u.cst.value;
      goto ret;
    case LTL_VARIABLE:
      /*printf("id %s : %d\n",e->u.id.name,c->values[e->u.id.index]);*/
      res = c->values[e->u.id.index];
      goto ret;
    }
  return -1;
 ret:
#ifdef DEBUG_VERIF
  level--;
  for(i = 0; i < level; i++) printf(" ");
  printf("] = %d\n", res);
#endif
  return res;
}
