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

#include "rm_display.h"
#include <stdio.h>
#include <math.h>

static void fprint_double(FILE *f,double d)
{
  int up,down;
  up=(int)floor(d);
  down=(int)((d-floor(d))*1000000.0);
  fprintf(f,"%d.%06d",up,down);
}   

void display_PMFILE_variables()
{
  struct vardef *v;
  int i;
  for(i = 0, v = PMFILE->variables; v; v = v->next)
    printf("  (%d) %s : [%d, %d]\n", i++, v->name, v->min, v->max);
}

void display_constant(struct constdef *c)
{
  if(c->kind == CONST_INT)
    printf("  CONST %s = %d\n", c->name, c->u.intvalue);
  else
    {
      printf("  CONST %s = ", c->name);
      fprint_double(stdout,c->u.floatvalue);
      printf("\n");
    }
  fflush(stdout);
}

void display_expression(struct expr *e)
{
  printf("(");
  switch(e->kind)
    {
    case E_ID:
      if(e->u.id->kind == ID_VAR)
	printf("%s", e->u.id->u.var->name);
      else
	printf("%s", e->u.id->u.cst->name);
      break;
    case E_BINARY:
      display_expression(e->u.binary.left);
      printf("%c", e->u.binary.op);
      display_expression(e->u.binary.right);
      break;
    case E_CSTE:
      printf("%d", e->u.cste);
      break;
    case E_VL:
      printf("!!!!!!VL STILL EXISTING!!!!!!!!\n");
      break;
    }
  printf(")");
  fflush(stdout);
}

void display_act(struct affectations *aff)
{
  if(aff->id->kind == ID_VAR)
    printf("%s = ", aff->id->u.var->name);
  else
    printf("??? Constant affected ??? %s = ", aff->id->u.cst->name);
  display_expression(aff->exp);
  if(aff->next) 
    {
      printf("&");
      display_act(aff->next);
    }
  fflush(stdout);
}

void display_probact(struct probaff *aff)
{
  printf("%f:", aff->proba);
  display_act(aff->det);
  if(aff->next)
    {
      printf("+");
      display_probact(aff->next);
    }
  fflush(stdout);
}

void display_action(struct action *act)
{
  printf("   ");
  if(act->probabilistic)
    display_probact(act->u.prob);
  else
    display_act(act->u.det);
  fflush(stdout);
}

void display_boolexpr(struct boolexpr *b)
{
  printf("(");
  switch(b->kind)
    {
    case BE_UNARY:
      printf("%c", b->u.unary.op); fflush(stdout);
      display_boolexpr(b->u.unary.exp);
      break;
    case BE_LOG_BINARY:
      display_boolexpr(b->u.binary.left);
      printf("%c", b->u.binary.op); fflush(stdout);
      display_boolexpr(b->u.binary.right);
      break;
    case BE_FORMULA:
      printf("%s{", b->u.formula->name); fflush(stdout);
      display_boolexpr(b->u.formula->expr);
      printf("}");
      break;
    case BE_EXP_BINARY:
      display_expression(b->u.exp_binary.left);
      printf("%c", b->u.exp_binary.op); fflush(stdout);
      display_expression(b->u.exp_binary.right);
      break;
    }
  printf(")");
  fflush(stdout);
}

void display_rule(struct rule *r)
{
  if(r->stateofrule)
    printf("  [%s]", r->stateofrule);
  else
    printf("  []");
  display_boolexpr(r->guard);
  printf("->\n");
  display_action(r->act);
  printf("\n");
}

void display_module(struct moduledef *m)
{
  struct rule *r;
  printf(" Module %s {\n", m->modulename);
  for(r = m->rules; r; r = r->next)
    display_rule(r);
  printf(" }\n");
}

void display_pmentries(struct pmentry *p)
{
  while(p) {
    switch(p->kind)
      {
      case PMENTRY_TYPE:
	break;
      case PMENTRY_CONST:
	display_constant(p->u.constant);
	break;
      case PMENTRY_MODULE:
	display_module(p->u.module);
	break;
      case PMENTRY_FORM:
	printf("  %s = {", p->u.formula->name);
	display_boolexpr(p->u.formula->expr);
	printf("}\n");
	break;
      }
    p = p->next;
  }
}

void display_pmfile(struct pmfile *pm)
{
  static char *PMKINDS[] = { "PROBABILISTIC" };
  printf("PMFILE (%d:%s)\n", pm->kind, PMKINDS[(unsigned char)pm->kind-1]);
  printf(" Constants :\n");
  display_pmentries(pm->constants);
  printf(" Formulae :\n");
  display_pmentries(pm->formulas);
  printf(" Modules :\n");
  display_pmentries(pm->modules);
}

void display_list_action(struct action_list *al)
{
  if(!al) return;
  display_action(al->act);
  if(al->next) {
    printf(", ");
    display_list_action(al->next);
  }
}

void display_applicable_actions(struct action_list_list *all)
{
  if(!all)
    return;
  printf("[");
  display_list_action(all->al);
  printf("]\n");
  display_applicable_actions(all->next);
}
