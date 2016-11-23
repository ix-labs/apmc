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

#include <stdlib.h>
#include "rm_free.h"

static void free_value_list(struct value_list *vl)
{
  if(!vl) return;
  icall(free_value_list, vl->next);
}

static void free_variables(struct vardef *v)
{
  if(!v) return;
  icall(free_variables, v->next);
  ifree(v->name);
}

void free_var(struct vardef *v)
{
  free_variables(v);
}

void free_rl(struct renamelist *rl)
{
  if(!rl) return;
  icall(free_rl, rl->next);
  if(rl->is_var)
    {
      if(--rl->u.var.what->nbref == 0 )
	icall(free_variables, rl->u.var.what);
      if(--rl->u.var.into->nbref == 0 )
	icall(free_variables, rl->u.var.into);
    }
  else
    {
      ifree(rl->u.synchro.what);
      ifree(rl->u.synchro.into);
    }
}

static void free_constant(struct constdef *c)
{
  ifree(c->name);
}

static void free_formulas(struct pmentry *e)
{
  if(!e) return;
  ifree(e->u.formula->name);
  icall(free_expr, e->u.formula->exp);
  ifree(e->u.formula);
  icall(free_formulas, e->next);
}

static void free_affectations(struct affectations *a)
{
  if(!a) return;
  icall(free_affectations, a->next);
  ifree(a->id);
  icall(free_expr, a->exp);
}

static void free_probaff(struct probaff *p)
{
  if(!p) return;
  icall(free_probaff, p->next);
  icall(free_affectations, p->det);
}

static void free_action(struct action *a)
{
  if(a->probabilistic)
    icall(free_probaff, a->u.prob);
  else
    icall(free_affectations, a->u.det);
}

static void free_rules(struct rule *r)
{
  if(!r)
    return;
  icall(free_rules, r->next);
  ifree(r->stateofrule);
  icall(free_expr, r->guard);
  icall(free_action, r->act);
}

static void free_module(struct moduledef *m)
{
  ifree(m->modulename);
  icall(free_rules, m->rules);
}

static void free_pmentry(struct pmentry *p)
{
  if(!p) return;
  icall(free_pmentry ,p->next);
  switch(p->kind)
    {
    case PMENTRY_TYPE:
      break;
    case PMENTRY_CONST:
      icall(free_constant, p->u.constant);
      break;
    case PMENTRY_MODULE:
      icall(free_module, p->u.module);
      break;
    case PMENTRY_FORM:
      break;
    }
}

void free_pmfile(struct pmfile *f)
{
  if(!f) return;
  icall(free_pmentry, f->modules);
  icall(free_formulas ,f->formulas);
  icall(free_pmentry, f->constants);
  icall(free_variables, f->variables);
}

void clean_PMFILE()
{
  rm_lineno=1;
  free_pmfile(PMFILE);
  ifree(PMFILE);
}

