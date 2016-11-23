#include <stdlib.h>
#include <string.h>

#include "compilers.h"
#include "reactive-modules.h"

static const char *CODE_BEFORE_STRAT3 = 
"typedef void (*action_t)(void);\n"
"typedef int  (*guard_t)(void);\n"
"\n"
"struct rule {\n"
"  guard_t guard;\n"
"  action_t action;\n"
"};\n"
;

static const char *CODE_AFTER_STRAT3 =
"void atomic_step(void)\n"
"{\n"
"  int choice;\n"
"  \n"
"  do\n"
"   {\n"
"     choice = get_random(0, NBRULES-1);\n"
"   } while(!rules[choice].guard());\n"
"  rules[choice].action();\n"
"}\n"
;

struct syncname_list {
  char *sync_name;
  struct syncname_list *next;
};

static int sname_is_member(char *v, struct syncname_list *l)
{
  struct syncname_list *sl;
  for(sl = l ; sl; sl = sl->next)
    if(!strcmp(sl->sync_name, v))
      return 1;
  return 0;
}

static struct syncname_list *sname_add_member(struct syncname_list *sl, char *v)
{
  struct syncname_list *s;
  if(!sl)
    {
      s = new(struct syncname_list);
      s->sync_name = v;
      return s;
    }
  for(s = sl; s->next; s = s->next) ;
  s->next = new(struct syncname_list);
  s->next->sync_name = v;
  return sl;
}

static void sname_free(struct syncname_list *s)
{
  if(!s) return;
  icall(sname_free, s->next);
}

struct rule_list {
  struct rule *r;
  struct rule_list *next;
};

struct rule_list_list {
  struct rule_list *rl;
  struct rule_list_list *next;
};

static struct rule_list_list *rll_append(struct rule_list_list *rll,
					 struct rule_list *rl)
{
  struct rule_list_list *Rll;
  if(!rll)
    {
      Rll = new(struct rule_list_list);
      Rll->rl = rl;
      return Rll;
    }
  for(Rll = rll; Rll->next; Rll = Rll->next) ;
  Rll->next = new(struct rule_list_list);
  Rll->next->rl = rl;
  return rll;
}

static struct rule_list *rl_append(struct rule_list *rl,
				   struct rule *r)
{
  struct rule_list *Rl;
  if(!rl)
    {
      Rl = new(struct rule_list);
      Rl->r = r;
      return Rl;
    }
  for(Rl = rl; Rl->next; Rl = Rl->next) ;
  Rl->next = new(struct rule_list);
  Rl->next->r = r;
  return rl;
}

static void rl_free(struct rule_list *al)
{
  if(!al) return;
  icall(rl_free, al->next);
}

static void rll_free(struct rule_list_list *all)
{
  if(!all) return;
  icall(rll_free, all->next);
  icall(rl_free, all->rl);
}

static int successor(struct rule_list **indexes,
		     struct rule_list **zeros,
		     int i)
{
  if (indexes[i]->next != NULL)
    {
      indexes[i] = indexes[i]->next;
      return 0;
    }
  indexes[i] = zeros[i];
  return 1;
}

static struct rule_list_list *combine_rule_list_lists(struct rule_list_list *rllpm)
{
  struct rule_list **indexes;
  struct rule_list **zeros;
  struct rule_list_list *rll;
  struct rule_list *rl;
  int i, nbactmod;
  struct rule_list_list *res = NULL;

  nbactmod = 0;
  for(rll = rllpm; rll; rll = rll->next) nbactmod++;

  indexes = (struct rule_list **)calloc(sizeof(struct rule_list*), nbactmod);
  zeros   = (struct rule_list **)calloc(sizeof(struct rule_list*), nbactmod);
  i = 0;
  for(rll = rllpm; rll; rll = rll->next)
    {
      indexes[i] = rll->rl;
      zeros[i] = rll->rl;
      i++;
    }

  do {
    rl = NULL;
    for(i = 0; i<nbactmod; i++)
      rl = rl_append(rl, indexes[i]->r);
    res = rll_append(res, rl);
    
    for(i = 0; i < nbactmod; i++)
      if( !successor(indexes, zeros, i) )
	break;
  } while(i != nbactmod);

  free(indexes);
  free(zeros);

  return res;
}

static struct rule_list *get_rule_list_with_syncname(struct rule *mrl, char *sync)
{
  struct rule *r;
  struct rule_list *rl = NULL;

  for(r = mrl; r; r = r->next)
    if( r->stateofrule && !strcmp(r->stateofrule, sync) )
      rl = rl_append(rl, r);
  return rl;
}

static struct rule_list_list *combine_with_syncname(struct pmentry *modules, char *sync)
{
  struct rule_list_list *rule_list_per_module_list = NULL;
  struct rule_list_list *res;
  struct rule_list *mrl;
  struct pmentry *m;

  for(m = modules; m; m = m->next)
    {
      mrl = get_rule_list_with_syncname(m->u.module->rules, sync);
      if(mrl != NULL)
	rule_list_per_module_list = rll_append(rule_list_per_module_list, mrl);
    }

  res = combine_rule_list_lists(rule_list_per_module_list);
  rll_free(rule_list_per_module_list);
  return res;
}

struct speed {
  char *g;
  char *a;
  struct speed *next;
};

/* CODE GENERATION */
static int generate_code_strategy3(FILE *out, struct pmfile *f)
{
  int nbrule;
  struct pmentry *e;

  struct rule *r;

  struct speed *s = NULL, *n;
  int nbspeed = 0;
  struct syncname_list *snl = NULL, *sync_elt;

  struct rule_list_list *crll, *rll = NULL;
  struct rule_list *rl;

  for(e = f->modules; e; e = e->next)
    {
      nbrule = 0;

      for(r = e->u.module->rules; r; r = r->next)
	{
	  if(r->stateofrule == NULL)
	    {
	      n = new(struct speed);

	      /* generate code for simple guard/action */
	      fprintf(out, "static int %s_g%d(void)\n{\n  return ", e->u.module->modulename,
		      nbrule);
	      generate_bool_expr(out, r->guard);
	      fprintf(out, ";\n}\n\nstatic void %s_a%d(void)\n{\n", e->u.module->modulename, nbrule);
	      if(r->act->probabilistic)
		  generate_probaff(out, r->act->u.prob);
	      else
		{
		  fprintf(out, "  ");
		  generate_aff(out, r->act->u.det);
		}
	      fprintf(out, "}\n\n");
	      
	      n->g = (char*)malloc(strlen(e->u.module->modulename)+12);
	      sprintf(n->g, "%s_g%d", e->u.module->modulename, nbrule);
	      n->a = (char*)malloc(strlen(e->u.module->modulename)+12);
	      sprintf(n->a, "%s_a%d", e->u.module->modulename, nbrule);
	      n->next = s;
	      s = n;
	      nbspeed++;
	    }
	  nbrule++;
	}
    }

  for(e = f->modules; e; e = e->next)
    {
      for(r = e->u.module->rules; r; r = r->next) {
	  if(r->stateofrule != NULL)
	    if(! sname_is_member(r->stateofrule, snl) )
	      snl = sname_add_member(snl, r->stateofrule);
      }
    }

  for(sync_elt = snl; sync_elt; sync_elt = sync_elt->next)
    {
      rll = combine_with_syncname(f->modules, sync_elt->sync_name);
      nbrule = 0;
      
      for(crll = rll; crll; crll = crll->next)
	{
	  fprintf(out, "static int %s_g%d(void)\n{\n", sync_elt->sync_name, nbrule);
	  fprintf(out, "  return\n");
	  for(rl = crll->rl; rl; rl = rl->next)
	    {
	      fprintf(out, "   (");
	      generate_bool_expr(out, rl->r->guard);
	      fprintf(out, ")");
	      if(rl->next)
		fprintf(out, "&&\n");
	      else
		fprintf(out, ";\n");
	    }
	  fprintf(out, "}\n\n");

	  fprintf(out, "static void %s_a%d(void)\n{\n", sync_elt->sync_name, nbrule);
	  for(rl = crll->rl; rl; rl = rl->next)
	    {
	      if(rl->r->act->probabilistic)
		{
		  fprintf(out, " {\n");
		  generate_probaff(out, rl->r->act->u.prob);
		  fprintf(out, " }\n");
		}
	      else
		{
		  fprintf(out, "  ");
		  generate_aff(out, rl->r->act->u.det);
		}
	    }
	  fprintf(out, "}\n\n");
	  
	  n = new(struct speed);
	  n->g = (char*)malloc(strlen(sync_elt->sync_name)+12);
	  sprintf(n->g, "%s_g%d", sync_elt->sync_name, nbrule);
	  n->a = (char*)malloc(strlen(sync_elt->sync_name)+12);
	  sprintf(n->a, "%s_a%d", sync_elt->sync_name, nbrule);
	  n->next = s;
	  s = n;
	  nbspeed++;

	  nbrule++;	  
	}
      rll_free(rll);
      rll = NULL;
    }

  sname_free(snl);

  fprintf(out, "#define NBRULES %d\n\n", nbspeed);
  fprintf(out, "static struct rule rules[%d] =\n  {\n", nbspeed);

  for(n = s; n; n = n ->next)
    {
      fprintf(out, "   { %s, %s }%s\n",
	      n->g, n->a, n->next?",":"");
      free(n->g);
      free(n->a);
      if(n != s)
	{
	  free(s);
	  s = n;
	}
    }
  free(s);

  fprintf(out, "};\n\n");

  return 1;
}

register( "sync at compile-time (PSoR)", generate_code_strategy3, CODE_BEFORE_STRAT3, CODE_AFTER_STRAT3 );
