/* APMC - Approximate Model Checker
 * Copyright (C) 2003, 2005 Guillaume Guirado, Thomas Hérault, Frédéric Magniett and Sylvain Peyronnet
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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "reactive-modules.h"

int rm_lineno = 1;
struct pmfile *PMFILE = NULL;

/** functions used in reactive-modules.y **/

/** Generation functions **/

void generate_aff(FILE *out, struct affectations *a)
{
  char *expr;
  for(; a; a = a->next)
    {
      vcg_node(a, "%s<-", a->id->u.var->name);
      if(a->next)
	vcg_edge(a, a->next, "%s", "next");
      vcg_edge(a, a->exp, "%s", "expression");
      fprintf(out, "%s = ", a->id->evar->name);
      expr = generate_expr(out, a->exp, "(void)");
      fprintf(out, "%s;\n", expr);
      free(expr);
    }
}

void generate_probaff(FILE *out, struct probaff *p, struct pmfile *f)
{
  double r = 0.0;
  double prob;
  double sum=0.0;
  struct probaff *iter;

  fprintf(out, "  double r;\n  r = probability();\n");
  //printf("goto in loop\n");
  for(iter=p; iter; iter = iter->next)
    {
      prob = evaluate_doubleexpr(iter->proba, f->constants);
      vcg_node(iter, "%s", "probaff");
      if(iter->next)
	vcg_edge(iter, iter->next, "%s", "next");
      vcg_edge(iter, iter->det, "%s(%f)", "aff", sum);
      sum = prob + r;
      //printf("sum=%lf p->proba=%lf r=%lf\n",sum,iter->proba,r);
      if(sum >= 1.0)
	fprintf(out, "  if ( r <= 1.0 )\n    {\n");
      else
	fprintf(out, "  if( r <= %g )\n    {\n", sum);
      generate_aff(out, iter->det);
      if(iter->next)
	fprintf(out, "    }\n  else");
      else
	fprintf(out, "    }\n");
      r += prob;
    }
}

//generate all variables declarations
int generate_variables(FILE *out, struct pmfile *f)
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
  char *expr;

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
      fprintf(out,"static int __form_%s(void) {\n return ",e->u.formula->name);
      expr = generate_expr(out, e->u.formula->exp, "(void)");
      fprintf(out,"%s;\n}\n", expr);
      free(expr);
    }
  fprintf(out,"\n");
  return nbform;
}

void generate_handle_state(FILE *out,struct pmfile *f, int nbvar)
{
  struct vardef *v;
  int i;
  static const char *append_state_string="if (is_new) {\n"
"   if(p->first == NULL)\n"
"       p->first = p->last = n;\n"
"    else\n"
"     {\n"
"        n->prev = p->last;\n"
"        p->last->next = n;\n"
"        p->last = n;\n"
"     }\n"
"   }\n"
"  }\n";

  fprintf(out, "static void append_state(path *p, int is_new)\n{\n  conf *n;\n");
  fprintf(out, "  if (is_new)\n");
  fprintf(out, "    {\n");
  fprintf(out, "      n = new(conf);\n");
  fprintf(out, "      n->values = (int*)malloc(%d * sizeof(int));\n", nbvar);
  fprintf(out, "    } else\n");
  fprintf(out, "    n = p->actual;\n");
  for(i=0, v=f->variables; v; i++, v=v->next)
    fprintf(out, "  n->values[%d] = %s;\n", i, v->name);
  fprintf(out,append_state_string);


  fprintf(out, "static void init_state(path *p)\n{\n");
  fprintf(out, "  p->actual = p->first;\n");
  for(v = f->variables; v; v = v->next)
    fprintf(out, "  %s=%d;\n", v->name, v->initial_value);
  fprintf(out, "}\n\n");

}

int id_is_synchro(char *name)
{
  struct pmentry *p;
  struct rule *r;

  for(p = PMFILE->modules; p; p = p->next)
    if( p->kind == PMENTRY_MODULE )
      for(r = p->u.module->rules; r; r = r->next)
	if(r->stateofrule && !strcmp(r->stateofrule, name))
	  return 1;
  return 0;
}

int change_initial_value(struct pmfile *f, char *name, int value)
{
  struct vardef *v;
  int found = -1;

  if(!f)
    {
      fprintf(stderr, "cannot change the state of %s if no variables where defined before!\n", name);
      return found;
    }

  for(v = f->variables; v; v = v->next)
    {
      if( !strcmp(v->name, name) )
	{
	  v->initial_value = value;
	  v->current_value = value;
	  found++;
	}
    }

  return found;
}
