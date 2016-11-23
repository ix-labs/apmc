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

#include <string.h>
#include <stdlib.h>
#include "rm_clone.h"

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

static struct vardef *target_var(struct vardef *w, struct renamelist *rl)
{
  struct renamelist *p;
  if(!w)  
    return NULL;
  for(p = rl; p; p = p->next)
      if(p->is_var)
	{
	  if(p->u.var.what == w)
	    {
	      p->u.var.into->nbref++;
	      //	      printf("%p(%s) -> %p(%s) : %d ref\n", w, w->name, p->u.var.into, p->u.var.into->name, p->u.var.into->nbref);
	      return p->u.var.into;
	    }
	}
  w->nbref++;
  //  printf("%p(%s) : %d ref\n", w, w->name, w->nbref);
  return w;
}

static char *target_synchro(char *w, struct renamelist *rl)
{
  struct renamelist *p;
  if(!w)  
    return NULL;
  for(p = rl; p; p = p->next)
      if(!p->is_var)
	{
	  if(!strcmp(p->u.synchro.what, w))
	    {
	      return strdup(p->u.synchro.into);
	    }
	}
  return NULL;
}

struct expr *clone_expression(struct expr *e, struct renamelist *rl)
{
  expr *r;

  if(!e) return NULL;

  r = new(expr);
  r->ekind = e->ekind;
  r->etype = e->etype;

  if(is_unary(e->ekind))
    {
      r->eexp = clone_expression(e->eexp, rl);
    }
  else if(is_binary(e->ekind))
    {
      r->eleft  = clone_expression(e->eleft, rl);
      r->eright = clone_expression(e->eright, rl);
    }
  else if(is_ternary(e->ekind))
    {
      r->eif    = clone_expression(e->eif, rl);
      r->ethen  = clone_expression(e->ethen, rl);
      r->eelse  = clone_expression(e->eelse, rl);
    }
  else if(e->ekind == ID)
    {
      r->evar = target_var(e->evar, rl);
    }
  else if(e->ekind == CST)
    {
      if(e->etype == INT)
	r->eint_value = e->eint_value;
      else
	r->efloat_value = e->efloat_value;
    }
  return r;
}

static struct affectations *clone_affectations(struct affectations *a, struct renamelist *rl)
{
  struct affectations *n;
  if(!a) return NULL;
  
  n = new(struct affectations);
  n->exp = clone_expression(a->exp, rl);
  n->next = clone_affectations(a->next, rl);
  n->id = clone_expression(a->id, rl);
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

  if( (t = target_synchro(r->stateofrule, rl)) )
    n->stateofrule = t;
  else
    {
      if(r->stateofrule)
	n->stateofrule = strdup(r->stateofrule);
      else
	n->stateofrule = NULL;
    }

  n->act   = clone_action(r->act, rl);
  n->guard = clone_expression(r->guard, rl);

  return n;
}
