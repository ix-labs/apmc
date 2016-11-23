/* APMC - Approximate Model Checker
 * Copyright (C) 2003 Thomas Hérault, Frédéric Magniett and Sylvain Peyronnet
 *
 * This software is free software; you can redistributed it and/or
 * modify it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This software is distributed in the hope that it will be useful, but 
 * WIHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this software; if not, write to the Free Software Foundation, Inc., 
 * 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "reactive-modules.h"

 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "double.h"

int rm_lineno = 1;
struct pmfile *PMFILE = NULL;

/** functions used in reactive-modules.y **/

int evaluate_expression(struct expr *e, struct pmentry *consts)
{
  char *msg;
  int v1, v2;
  switch(e->kind)
    {
    case E_ID:
      if( (e->u.id->kind == ID_CST) )
	{
	  if(e->u.id->u.cst->kind == CONST_INT)
	    return e->u.id->u.cst->u.intvalue;
	  msg = (char*)malloc(128+strlen(e->u.id->u.cst->name));
	  sprintf(msg, "%s is defined as a rate and used in a constant definition",
		  e->u.id->u.cst->name);
	  rm_error(msg);
	  free(msg);
	  return 0;
	}
      else
	{
	  msg = (char*)malloc(128+strlen(e->u.id->u.var->name));
	  sprintf(msg, "%s is defined as a variable and used in a constant definition",
		  e->u.id->u.var->name);
	  rm_error(msg);
	  free(msg);
	  return 0;
	}
      break;
    case E_BINARY:
      v1 = evaluate_expression(e->u.binary.left, consts);
      v2 = evaluate_expression(e->u.binary.right, consts);
      switch(e->u.binary.op)
	{
	case E_BIN_PLUS:
	  return v1+v2;
	case E_BIN_MINUS:
	  return v1-v2;
	case E_BIN_MIN:
	  if(v1 > v2) return v2;
	  else return v1;
	case E_BIN_MAX:
	  if(v1 < v2) return v2;
	  else return v1;	  
	case E_BIN_TIMES:
	  return v1*v2;
	default:
	  fprintf(stderr, "binary operand %d is undefined!\n", e->u.binary.op);
	  exit(-1);
	}
    case E_CSTE:
      return e->u.cste;
    }
  rm_error("Internal parser error");
  return -1;
}

struct expr *new_exp_from_int(int v)
{
  struct expr *e = new(struct expr);
  e->kind = E_CSTE;
  e->u.cste = v;
  return e;
}

struct value_list *vl_append(struct value_list *v1, struct value_list *v2)
{
  struct value_list *v;
  if(!v1)
    return v2;
  if(!v1->next)
    v1->next = v2;
  else
    {
      for(v = v1; v->next; v=v->next) ;
      v->next = v2;
    }
  return v1;
}

struct value_list *vl_build(int from, int to)
{
  struct value_list *v, *p, *vl;
  int i;

  v = new(struct value_list);
  i = from;
  v->value = i;
  p = v;
  while( i < to ) {
    i++;
    vl = new(struct value_list);
    vl->value = i;
    p->next = vl;
    p = vl;
  } 

  return v;
}

struct identifier *new_id_by_name(char *name, 
				  unsigned char may_be_constant)
{
  struct pmentry *c;
  struct vardef  *v;
  struct identifier *n;

  if(may_be_constant)
    {
      for(c = PMFILE->constants; c; c = c->next)
	if( c->kind == PMENTRY_CONST )
	  if(!strcmp(c->u.constant->name, name))
	    {
	      n = new(struct identifier);
	      n->kind = ID_CST;
	      n->u.cst = c->u.constant;
	      return n;
	    }
    }

  for(v = PMFILE->variables; v; v = v->next)
    if(!strcmp(v->name, name))
      {
	n = new(struct identifier);
	n->kind = ID_VAR;
	n->u.var = v;
	return n;
      }
  
  n = new(struct identifier);
  n->kind = ID_VAR;
  n->u.var = new(struct vardef);
  n->u.var->name = strdup(name);
  n->u.var->min = 0;
  n->u.var->max = -1;
  n->u.var->next = PMFILE->variables;
  PMFILE->variables = n->u.var;

  return n;
}

/** Generation functions **/

static void generate_expr(FILE *out, struct expr *e)
{
  fprintf(out, "(");
  switch(e->kind)
    {
    case E_ID:
      if(e->u.id->kind == ID_VAR)
	fprintf(out, "%s", e->u.id->u.var->name);
      else
	{
	  if(e->u.id->u.cst->kind == CONST_INT)
	    fprintf(out, "%d", e->u.id->u.cst->u.intvalue);
	  else
	    fprint_double(out,e->u.id->u.cst->u.floatvalue);
	}
      break;
    case E_BINARY:
      switch( e->u.binary.op )
	{
	case E_BIN_PLUS:
	  generate_expr(out, e->u.binary.left);
	  fprintf(out, "+");
	  generate_expr(out, e->u.binary.right);
	  break;
	case E_BIN_MINUS:
	  generate_expr(out, e->u.binary.left);
	  fprintf(out, "-");
	  generate_expr(out, e->u.binary.right);
	  break;
	case E_BIN_MIN:
	  fprintf(out, "MIN(");
	  generate_expr(out, e->u.binary.left);
	  fprintf(out, ",");
	  generate_expr(out, e->u.binary.right);
	  fprintf(out, ")");
	  break;
	case E_BIN_MAX:
	  fprintf(out, "MAX(");
	  generate_expr(out, e->u.binary.left);
	  fprintf(out, ",");
	  generate_expr(out, e->u.binary.right);
	  fprintf(out, ")");
	  break;
	case E_BIN_TIMES:
	  generate_expr(out, e->u.binary.left);
	  fprintf(out, "*");
	  generate_expr(out, e->u.binary.right);
	  break;
	default:
	  fprintf(stderr, "binary operand %d is undefined!\n", e->u.binary.op);
	  exit(-1);
	}
      break;
    case E_CSTE:
      fprintf(out, "%d", e->u.cste);
      break;
    case E_VL:
      break;
    }
  fprintf(out, ")");
}

void generate_bool_expr(FILE *out, struct boolexpr *b)
{
  static char *BE_OP[] = { NULL, "!", "&&", "||" };
  static char *BE_EXP_OP[] = { NULL, "==", "!=", "<", ">", "<=", ">=" };
  fprintf(out, "(");
  switch(b->kind)
    {
    case BE_UNARY:
      fprintf(out, "%s", BE_OP[(int)b->u.unary.op]);
      generate_bool_expr(out, b->u.unary.exp);
      break;
    case BE_LOG_BINARY:
      generate_bool_expr(out, b->u.binary.left);
      fprintf(out, "%s", BE_OP[(int)b->u.binary.op]);
      generate_bool_expr(out, b->u.binary.right);
      break;
    case BE_FORMULA:
      fprintf(out,"__form_%s()",b->u.formula->name);
      //generate_bool_expr(out, b->u.formula->expr);
      break;
    case BE_EXP_BINARY:
      generate_expr(out, b->u.exp_binary.left);
      fprintf(out, "%s", BE_EXP_OP[(int)b->u.exp_binary.op]);
      generate_expr(out, b->u.exp_binary.right);
      break;
    }
  fprintf(out, ")");
}

void generate_aff(FILE *out, struct affectations *a)
{
  for(; a; a = a->next)
    {
      fprintf(out, "%s = ", a->id->u.var->name);
      generate_expr(out, a->exp);
      fprintf(out, ";\n");
    }
}

void generate_probaff(FILE *out, struct probaff *p)
{
  double r = 0.0;
  double sum=0.0;
  struct probaff *iter;

  fprintf(out, "  double r;\n  r = probability();\n");
  //printf("goto in loop\n");
  for(iter=p; iter; iter = iter->next)
    {
      sum=iter->proba+r;
      //printf("sum=%lf p->proba=%lf r=%lf\n",sum,iter->proba,r);
      fprintf(out, "  if( r <= ");
      fprint_double(out,sum);
      fprintf(out," )\n    {\n     ");
      generate_aff(out, iter->det);
      if(iter->next)
	fprintf(out, "    }\n  else");
      else
	fprintf(out, "    }\n");
      r += iter->proba;
    } 
}

//generate all variables declarations
int generate_variables(FILE *out,struct pmfile *f)
{
  int nbvar=0;
  struct vardef *v;
  for(v = f->variables; v; v = v->next)
    {
      nbvar++;
      fprintf(out, "static int %s = %d;\n",
	      v->name, v->initial_value);
    }
  
  fprintf(out, "\n");

  #ifdef EBUG
  fprintf(out, "static void print_state(void)\n{\n");
  for(v = f->variables; v; v = v->next)
    {
      if(v==f->variables)
	fprintf(out, "  printf(\"[%s=%%d%s\", %s);\n", v->name, v->next?",":"]", v->name);
      else
	fprintf(out, "  printf(\"%s=%%d%s\", %s);\n", v->name, v->next?",":"]", v->name);
    }
  fprintf(out, "}\n\n");
#endif  

  return nbvar;
}

//generate all formulas functions
int generate_formulas(FILE *out,struct pmfile *f)
{
  int nbform=0;
  struct pmentry *e;
  //prototypes
  for(e=f->formulas;e;e=e->next)
    {
      nbform++;
      fprintf(out,"static int __form_%s();\n",e->u.formula->name);
    }
  fprintf(out,"\n");
  //formulas functions
  for(e=f->formulas;e;e=e->next)
    {
      fprintf(out,"static int __form_%s() {\n return ",e->u.formula->name);
      generate_bool_expr(out,e->u.formula->expr);
      fprintf(out,";\n}\n");
    }
  fprintf(out,"\n");
  return nbform;
}

void generate_handle_state(FILE *out,struct pmfile *f, int nbvar)
{
  struct vardef *v;
  int i;
  static const char *append_state_string="   if(p->first == NULL)\n"
"       p->first = p->last = n;\n"
"    else\n"
"     {\n"
"        n->prev = p->last;\n"
"        p->last->next = n;\n"
"        p->last = n;\n"
"     }\n"
"  }\n";

  fprintf(out, "static void append_state(path *p)\n{\n  conf *n;\n");
  fprintf(out, "  n = new(conf);\n");
  fprintf(out, "  n->values = (int*)malloc(%d * sizeof(int));\n", nbvar);

  for(i=0, v=f->variables; v; i++, v=v->next)  
    fprintf(out, "  n->values[%d] = %s;\n", i, v->name);
  fprintf(out,append_state_string);


  fprintf(out, "static void init_state(void)\n{\n");
  for(v = f->variables; v; v = v->next)
    fprintf(out, "  %s=%d;\n", v->name, v->initial_value);
  fprintf(out, "}\n\n");

}
