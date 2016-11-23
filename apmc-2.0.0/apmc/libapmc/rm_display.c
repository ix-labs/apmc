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

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "rm_display.h"

static void fprint_double(FILE *f,double d)
{
  int up,down;
  up=(int)floor(d);
  down=(int)((d-floor(d))*1000000.0);
  fprintf(f,"%d.%06d",up,down);
}   

void display_rename_list(struct renamelist *rl)
{
  struct renamelist *p;
  for(p = rl; p; p = p->next)
    if(p->is_var)
      {
	printf("var : %s->%s%s", p->u.var.what->name, p->u.var.into->name, p->next?", ":"\n");
      }
    else
      {
	printf("synchro : %s->%s%s", p->u.synchro.what, p->u.synchro.into, p->next?", ":"\n");
      }
}

void display_PMFILE_variables()
{
  struct vardef *v;
  int i;
  for(i = 0, v = PMFILE->variables; v; v = v->next)
    printf("  (%d) %s : [%d, %d] = %d\n", i++, v->name, v->min, v->max, v->current_value);
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

void display_act(struct affectations *aff)
{
  char *expr;

  printf("%s = ", aff->id->evar->name);
  expr = generate_expr(stdout, aff->exp, "(void)");
  printf("%s", expr);
  free(expr);
  if(aff->next) 
    {
      printf("&");
      display_act(aff->next);
    }
  fflush(stdout);
}

void display_probact(struct probaff *aff)
{
  char *e = generate_expr(stdout, aff->proba, "(void)");
  printf("%s:", e);
  free(e);
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

void display_rule(struct rule *r)
{
  char *expr;

  if(r->stateofrule)
    printf("  [%s]", r->stateofrule);
  else
    printf("  []");
  expr = generate_expr(stdout, r->guard, "(void)");
  printf("%s->\n", expr);
  free(expr);
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
  char *expr;
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
	expr = generate_expr(stdout, p->u.formula->exp, "(void)");
	printf("%s}\n", expr);
	free(expr);
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
