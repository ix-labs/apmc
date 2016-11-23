#include <stdlib.h>
#include <string.h>

#include "compilers.h"
#include "reactive-modules.h"

static const char *CODE_BEFORE_STRAT2 =
"typedef void (*action_t)(void);\n"
"typedef int  (*guard_t)(void);\n"
"\n"
"struct rule {\n"
"  guard_t guard;\n"
"  action_t action;\n"
"  unsigned int sync;\n"
"  unsigned int module;\n"
"};\n"
;

static const char *CODE_AFTER_STRAT2 =
"\n"
"/*\n"
" * Combinatory product\n"
" */\n"
"\n"
"struct intlist {\n"
"  unsigned int nbact;\n"
"  unsigned int nballoc;\n"
"  int *indexes;\n"
"};\n"
"\n"
"static int succ_pm(struct intlist **trpm, int *indexes, int i)\n"
"{\n"
"  if (indexes[i] < trpm[i]->nbact-1)\n"
"    {\n"
"      indexes[i]++;\n"
"      return 0;\n"
"    }\n"
"  indexes[i] = 0;\n"
"  return 1;\n"
"}\n"
"\n"
"#define free_intlist(a) "
"do { "
"  if(a) { "
"    if(a->indexes) free(a->indexes); "
"    free(a); "
"    a = NULL; "
"  } "
"} while(0)\n"
"\n"
"static struct intlist* simple_action(int i)\n"
"{\n"
"  struct intlist *r;\n"
"  r = (struct intlist*)malloc(sizeof(struct intlist));\n"
"  r->nbact = 1;\n"
"  r->nballoc = 1;\n"
"  r->indexes = (int*)malloc(sizeof(int));\n"
"  r->indexes[0] = i;\n"
"  return r;\n"
"}\n"
"\n"
"static struct intlist *add_int(struct intlist *il, int i)\n"
"{\n"
"  if(il == NULL)\n"
"    return simple_action(i);\n"
"  if(il->nbact < il->nballoc)\n"
"    {\n"
"      il->indexes[il->nbact++] = i;\n"
"      return il;\n"
"    }\n"
"  il->indexes = (int*)realloc(il->indexes, 2*il->nballoc * sizeof(int));\n"
"  il->nballoc = 2*il->nballoc;\n"
"  il->indexes[il->nbact++] = i;\n"
"  return il;\n"
"}\n"
"\n"
"static int ieme(struct intlist *il, int i)\n"
"{\n"
"  return il->indexes[i];\n"
"}\n"
"\n"
"static struct intlist *super_combi(struct intlist **trpm, int *indexes, int *z)\n"
"{\n"
"  int i;\n"
"  struct intlist *na = NULL;\n"
"\n"
"  for(i = 0; i < NBMODULES; i++)\n"
"    if(trpm[i] != NULL)\n"
"      na = add_int(na, ieme(trpm[i], indexes[i]));\n"
"  \n"
"  i = 0;\n"
"  for(i = 0; i < NBMODULES; i++)\n"
"    if(trpm[i] != NULL)\n"
"      {\n"
"	if(!succ_pm(trpm, indexes, i))\n"
"	  break;\n"
"      }\n"
"\n"
"  *z = (i == NBMODULES);\n"
"\n"
"  return na;\n"
"}\n"
"\n"
"void atomic_step(void)\n"
"{\n"
"  int i, j, m, choice;\n"
"  static struct intlist **fireable   = NULL;\n"
"  struct intlist *na;\n"
"  static int maxrules = 0;\n"
"  int nbrules;\n"
"  struct intlist *truerules_per_module[NBMODULES] = {NULL, };\n"
"  int index_combi[NBMODULES];\n"
"  int z;\n"
"\n"
"#define add_action(rule) do {"
"  if(nbrules+1 >= maxrules) {"
"    maxrules+=128; "
"    fireable = (struct intlist**)realloc(fireable, maxrules*sizeof(struct intlist*)); "
"  } "
"  fireable[nbrules++] = (rule); "
"} while(0)\n"
"  \n"
"#define add_int(il, i) do {"
"  if(il == NULL) il=(struct intlist*)calloc(sizeof(struct intlist), 1); "
"  if(il->nbact + 1 > il->nballoc) il->indexes = (int*)realloc(il->indexes, (il->nballoc += 2)*sizeof(int)); "
"  il->indexes[il->nbact++] = i; "
"} while(0)\n"
"\n"
"  nbrules = 0;\n"
"  for(i = 0; i < NBRULESNOSYNC; i++)\n"
"    {\n"
"      if(rules[i].guard())\n"
"	add_action( simple_action(i) );\n"
"    }\n"
"\n"
"  for(j = 1; j < MAXSYNC; j++)\n"
"    {\n"
"      i = FIRSTSYNCRULE[j];\n"
"      m = rules[i].module;\n"
"\n"
"      for(i = FIRSTSYNCRULE[j]; i < FIRSTSYNCRULE[j+1]; i++)\n"
"	{\n"
"	  if( (rules[i].module != m) && (truerules_per_module[m] == NULL) )\n"
"	    break;\n"
"\n"
"	  if(m != rules[i].module)\n"
"	    m = rules[i].module;\n"
"\n"
"	  if(rules[i].guard())\n"
"	    add_int( truerules_per_module[m], i );\n"
"	}\n"
"\n"
"      if( (i == FIRSTSYNCRULE[j+1]) && ( truerules_per_module[m] != NULL) )\n"
"	{\n"
"	  for(i=0; i < NBMODULES; i++)\n"
"	    index_combi[i] = 0;\n"
"\n"
"	  do {\n"
"	    na = super_combi(truerules_per_module, index_combi, &z);\n"
"	    add_action(na);\n"
"	  } while( !z );\n"
"	}\n"
"\n"
"      for(m = 0; m < NBMODULES; m++)\n"
"	free_intlist(truerules_per_module[m]);\n"
"    }\n"
"  \n"
"  choice = get_random(0, nbrules-1);\n"
"  for(i = 0; i < fireable[choice]->nbact; i++)\n"
"    rules[fireable[choice]->indexes[i]].action();\n"
"  for(i = 0; i < nbrules; i++)\n"
"    free_intlist(fireable[i]);\n"
"  }\n";


struct speed {
  char *g;
  char *a;
  unsigned int sync;
  unsigned int module;
  struct speed *next;
};

static struct speed *insert_sorted(struct speed *list, struct speed *elt)
{

  if( list==NULL )
    {
      elt->next = NULL;
      return elt;
    }
  if( elt->sync < list->sync )
    {
      elt->next = list;
      return elt;
    }
  if( (elt->sync == list->sync) && (elt->module <= list->module) )
    {
      elt->next = list;
      return elt;
    }
  list->next = insert_sorted(list->next, elt);
  return list;
}

static unsigned int statetoint(char *name)
{
  static char **states = NULL;
  static int nbstates  = 0;
  static int nballoc   = 0;
  unsigned int i;

  if(name == NULL)
    {
      if(states) free(states);
      i = nbstates;
      nbstates = 0;
      nballoc  = 0;
      return i;
    }
  for(i = 0; i < nbstates; i++)
    if(!strcmp(states[i], name))
      return i+1;
  if( nbstates+1 >= nballoc )
    states = (char**)realloc(states, sizeof(char*)*(nballoc = 2*nballoc + 1));
  states[nbstates++] = name;
  return nbstates;
}

static int sumof(int *nbrulespersync, int max)
{
  int s = 0;
  int i;
  for(i = 0; i <= max; i++)
    s += nbrulespersync[i];
  return s;
}

int generate_code_strategy2(FILE *out, struct pmfile *f)
{
  struct speed *s = NULL, *n, *sorted = NULL;
  int nbrule = 0;
  struct pmentry *e;
  struct rule *r;
  int nbspeed = 0;
  int nbmodules = 0;
  int *nbrulespersync;
  int nbsync = 0;
  int i;
  char *expr;

  statetoint(NULL);
  for(e = f->modules; e; e = e->next)
    {
      nbrule = 0;

      /* We produce every guard/action */
      for(r = e->u.module->rules; r; r = r->next)
	{
	  n = new(struct speed);

	  fprintf(out, "static int %s_g%d(void)\n{\n  return ", e->u.module->modulename,
		  nbrule);
	  expr = generate_expr(out, r->guard, "(void)");
	  fprintf(out, "%s;\n}\n\nstatic void %s_a%d(void)\n{\n", expr,
		  e->u.module->modulename, nbrule);
	  free(expr);
	  if(r->act->probabilistic)
	    generate_probaff(out, r->act->u.prob, f);
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
	  if( r->stateofrule == NULL ) n->sync = 0;
	  else n->sync = statetoint(r->stateofrule);
	  n->module = nbmodules;
	  n->next = s;
	  s = n;
	  nbspeed++;
	  nbrule++;
	}
      nbmodules++;
    }

  /* Now, sort the speed list, with the following order :
   *    1. [0..NBRULESNOSYNC[ only the non-synced rules, second key : module index
   *    2. For i = 1 to MAXSYNC, [FIRSTSYNCRULE[i]..LASTSYNCRULE[i][ : all synced rules on
   *       sync tag i, ordered by module index
   * Use this to define all these needed variables
   */

  fprintf(out, "#define NBRULES %d\n", nbspeed);
  fprintf(out, "#define NBMODULES %d\n", nbmodules);
  /* Hack : free the memory AND returns the number of sync defined */
  fprintf(out, "#define MAXSYNC %d\n", (nbsync = statetoint(NULL))+1);

  nbrulespersync = (int*)calloc(sizeof(int), nbsync+1);
  for(n = s; n; n = s)
    {
      s = n->next;
      nbrulespersync[n->sync]++;
      sorted = insert_sorted(sorted, n);
    }
  fprintf(out, "#define NBRULESNOSYNC %d\n", nbrulespersync[0]);

  fprintf(out, "static int FIRSTSYNCRULE[MAXSYNC+1] = { 0, ");
  for(i = 0; i < nbsync; i++)
    fprintf(out, "%d, ", sumof(nbrulespersync, i));
  fprintf(out, "%d };\n", nbspeed);
  free(nbrulespersync);

  fprintf(out, "static struct rule rules[%d] =\n  {\n", nbspeed);

  for(n = sorted; n; n = n ->next)
    {
      fprintf(out, "   { %s, %s, %d, %d }%s\n",
	      n->g, n->a, n->sync, n->module, n->next?",":"");
      free(n->g);
      free(n->a);
      if(n != sorted)
	{
	  free(sorted);
	  sorted = n;
	}
    }
  free(sorted);

  fprintf(out, "};\n\n");

  return 1;
}

void init_strategy2(void)
{
  register_new_compiler( "sync at run-time", generate_code_strategy2, CODE_BEFORE_STRAT2, CODE_AFTER_STRAT2 );
}
