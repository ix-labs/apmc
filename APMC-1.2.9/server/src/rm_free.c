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

#include "rm_free.h"
#include <stdlib.h>

static void free_value_list(struct value_list *vl)
{
  if(!vl) return;
  icall(free_value_list, vl->next);
}

void free_expression(struct expr *e)
{
  if(!e) return;

  switch(e->kind)
    {
    case E_ID:
      ifree(e->u.id);
      break;
    case E_BINARY:
      icall(free_expression, e->u.binary.left);
      icall(free_expression, e->u.binary.right);
      break;
    case E_VL:
      icall(free_value_list, e->u.vl);
    }
}

void free_rl(struct renamelist *rl)
{
  if(!rl) return;
  icall(free_rl, rl->next);
  ifree(rl->what);
  ifree(rl->into);
}

static void free_constant(struct constdef *c)
{
  ifree(c->name);
}

static void free_variables(struct vardef *v)
{
  if(!v) return;
  icall(free_variables, v->next);
  ifree(v->name);
}



static void free_boolexpr(struct boolexpr *b)
{
  if(!b) return;
  switch(b->kind)
    {
    case BE_UNARY:
      icall(free_boolexpr, b->u.unary.exp);
      break;
    case BE_LOG_BINARY:
      icall(free_boolexpr, b->u.binary.left);
      icall(free_boolexpr, b->u.binary.right);
      break;
    case BE_FORMULA:
      break;
    case BE_EXP_BINARY:
      icall(free_expression, b->u.exp_binary.left);
      icall(free_expression, b->u.exp_binary.right);
      break;
    }
}

static void free_formulas(struct pmentry *e)
{
  if(!e) return;
  icall(free_formulas, e->next);
  ifree(e->u.formula->name);
  icall(free_boolexpr,e->u.formula->expr);
  ifree(e->u.formula);
}

static void free_affectations(struct affectations *a)
{
  if(!a) return;
  icall(free_affectations, a->next);
  ifree(a->id);
  icall(free_expression, a->exp);
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
  icall(free_boolexpr, r->guard);
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
}

