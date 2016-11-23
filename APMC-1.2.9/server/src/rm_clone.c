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

#include "rm_clone.h"
#include <string.h>
#include <stdlib.h>

static struct value_list *clone_vl(struct value_list *v)
{
  struct value_list *l;
  if(!v)
    return NULL;
  l = new(struct value_list);
  l->value = v->value;
  l->next = clone_vl(v->next);
  return l;
}

static char *target(char *w, struct renamelist *rl)
{
  if(!rl) return NULL;
  if(!w)  return NULL;
  if(!strcmp(rl->what, w))
    return rl->into;
  return target(w, rl->next);
}

static struct identifier *clone_identifier(struct identifier *i, struct renamelist *rl)
{
  char *t;
  struct identifier *n;

  if(i->kind == ID_VAR)
    {
      if( (t = target(i->u.var->name, rl)) )
	return new_id_by_name(t, 0);
      else
	return new_id_by_name(i->u.var->name, 0);
    }
  else
    {
      n = new(struct identifier);
      n->kind = ID_CST;
      n->u.cst = i->u.cst;
      return n;
    }
}

struct expr *clone_expression(struct expr *e, struct renamelist *rl)
{
  struct expr *r;
  if(!e) return NULL;

  r = new(struct expr);
  r->kind = e->kind;
  switch(e->kind)
    {
    case E_ID:
      r->u.id = clone_identifier(e->u.id, rl);
      break;
    case E_BINARY:
      r->u.binary.op = e->u.binary.op;
      r->u.binary.left = clone_expression(e->u.binary.left, rl);
      r->u.binary.right = clone_expression(e->u.binary.right, rl);
      break;
    case E_CSTE:
      r->u.cste = e->u.cste;
      break;
    case E_VL:
      r->u.vl = clone_vl(e->u.vl);
      break;
    }
  return r;
}

static struct formuladef *clone_formula(struct formuladef *d, struct renamelist *rl)
{
  struct formuladef *n = new(struct formuladef);
  n->name = strdup(d->name);
  n->expr = d->expr;
  return n;
}

static struct boolexpr *clone_boolexpr(struct boolexpr *b, struct renamelist *rl)
{
  struct boolexpr *n = new(struct boolexpr);
  n->kind = b->kind;
  switch(b->kind)
    {
    case BE_UNARY:
      n->u.unary.op = b->u.unary.op;
      n->u.unary.exp = clone_boolexpr(b->u.unary.exp, rl);
      break;
    case BE_LOG_BINARY:
      n->u.binary.op = b->u.binary.op;
      n->u.binary.left = clone_boolexpr(b->u.binary.left, rl);
      n->u.binary.right = clone_boolexpr(b->u.binary.right, rl);
      break;
    case BE_FORMULA:
      n->u.formula = clone_formula(b->u.formula, rl);
      break;
    case BE_EXP_BINARY:
      n->u.exp_binary.op = b->u.exp_binary.op;
      n->u.exp_binary.left = clone_expression(b->u.exp_binary.left, rl);
      n->u.exp_binary.right = clone_expression(b->u.exp_binary.right, rl);
      break;
    }
  
  return n;
}

static struct affectations *clone_affectations(struct affectations *a, struct renamelist *rl)
{
  struct affectations *n;
  if(!a) return NULL;
  
  n = new(struct affectations);
  n->exp = clone_expression(a->exp, rl);
  n->next = clone_affectations(a->next, rl);
  n->id = clone_identifier(a->id, rl);
  return n;
}

static struct probaff *clone_probaff(struct probaff *p, struct renamelist *rl)
{
  struct probaff *n;
  if(!p) return NULL;
  n = new(struct probaff);
  n->proba = p->proba;
  n->next = clone_probaff(p->next, rl);
  n->det  = clone_affectations(p->det, rl);
  return n;
}

static struct action *clone_action(struct action *act, struct renamelist *rl)
{
  struct action *n = new(struct action);
  n->probabilistic = act->probabilistic;
  if(n->probabilistic)
    n->u.prob = clone_probaff(act->u.prob, rl);    
  else
    n->u.det = clone_affectations(act->u.det, rl);
  return n;
}

struct rule *clone_rules(struct rule *r, struct renamelist *rl)
{
  char *t;
  struct rule *n;
  
  if(!r) return NULL;
  
  n = new(struct rule);
  n->next = clone_rules(r->next, rl);

  if( (t = target(r->stateofrule, rl)) )
    n->stateofrule = strdup(t);
  else
    {
      if(r->stateofrule)
	n->stateofrule = strdup(r->stateofrule);
      else
	n->stateofrule = NULL;
    }

  n->act   = clone_action(r->act, rl);
  n->guard = clone_boolexpr(r->guard, rl);

  return n;
}
