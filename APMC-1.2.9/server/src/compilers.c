#include <stdlib.h>
#include <string.h>

#include "compilers.h"
#include "support.h" /*for debug*/

static struct compiler *COMPILERS = NULL;

void register_new_compiler( char *n, compiler_func c, const char *o, const char *l)
{
  struct compiler *comp = (struct compiler *)calloc(sizeof(struct compiler), 1);
  comp->name = n;
  comp->comp = c;
  comp->opening = o;
  comp->closing = l;
  comp->next = COMPILERS;
  COMPILERS = comp;
}

struct compiler *get_compiler_from_name( char *name )
{
  struct compiler *r;
  if( name == NULL )
    return COMPILERS;

  for(r = COMPILERS; r; r = r->next)
    if( !strcmp(r->name, name) )
      return r;
  return NULL;
}

static char GENERIC_OPENING[] = "\n"
"#include <stdlib.h>\n"
"#include <stdio.h>\n"
"#include <sys/time.h>\n"
"\n"
"#define new(a)  (a*)calloc(1, sizeof(a))\n"
"\n"
"static inline int MIN(int a, int b)\n"
"{\n"
"  if(a<b) return a;\n"
"  else return b;\n"
"}\n"
"\n"
"static inline int MAX(int a, int b)\n"
"{\n"
"  if(a>b) return a;\n"
"  else return b;\n"
"}\n"
"\n"
"static unsigned int get_random(unsigned int min, unsigned int max)\n"
"{\n"
"  max++;\n"
"  return min + (unsigned int)( (double)(max-min)*rand()/(RAND_MAX+(double)min));\n"
"}\n"
"\n"
"static double probability()\n"
"{\n"
"  double r = (double)((unsigned int)-2);\n"
"  double R = get_random(0, (unsigned int)-2);\n"
"  r = ((double)R) / r;\n"
"  return r;\n"
"}\n"
"\n"
"typedef struct conf {\n"
"  int *values;\n"
"  struct conf *next;\n"
"  struct conf *prev;\n"
"} conf;\n"
"\n"
"typedef struct path {\n"
"  conf * first;\n"
"  conf * last;\n"
"} path;\n"
"\n"
"typedef int (*tester_t)(conf *);\n"
"\n"
"static int until(tester_t left, tester_t right, conf *c)\n"
"{\n"
"  int cond;\n"
"\n"
"  if(!c) return 0;\n"
"\n"
"  cond = right(c);\n"
"  if (cond)\n"
"    return 1;\n"
"  cond=left(c);\n"
"  if (!cond)\n"
"    return 0;\n"
"  if(!c->next)\n"
"    return 0;\n"
"  cond=right(c->next);\n"
"  if (cond)\n"
"    return 1;\n"
"  return until(left, right, c->next);\n"
"}\n"
"\n"
"static int next(tester_t w, conf *c)\n"
"{\n"
"  if(!c) return 0;\n"
"  if(!c->next) return 0;\n"
"  return w(c->next);\n"
"}\n";

static char GENERIC_CLOSING[] = "\n"
"void free_path(path *p)\n"
"{\n"
"  conf *c, *o = NULL;\n"
"\n"
"  for(c = p->first; c; c = c->next)\n"
"    {\n"
"      if(o)\n"
"	{\n"
"	  free(o->values);\n"
"	  free(o);\n"
"	}\n"
"      o = c;\n"
"    }\n"
"  if(o)\n"
"    {\n"
"      free(o->values);\n"
"      free(o);\n"
"    }\n"
"  p->first = p->last = NULL;\n"
"}\n"
"\n"
"int main(int argc, char *argv[])\n"
"{  \n"
"  int i;\n"
"  int j;\n"
"  struct timeval tv;\n"
"  path p = { NULL, NULL };\n"
"  int path_len;\n"
"  int nb[2];\n"
"  time_t t1, t2;\n"
"\n"
"  if(argc != 2)\n"
"    return -1;\n"
"  path_len = atoi(argv[1]);\n"
"\n"
"  gettimeofday(&tv, NULL);\n"
"  srand(tv.tv_sec);\n"
"  \n"
"  nb[0] = nb[1] = 0;\n"
"  t1 = time(NULL);\n"
"  for(;;)\n"
"    {\n"
"      init_state();\n"
"      append_state(&p);\n"
"      for(i = 0; i < path_len; i++)\n"
"	{\n"
"	  atomic_step();\n"
"	  append_state(&p);\n"
"	}\n"
"      if( verify_path(p.first) )\n"
"	nb[0]++;\n"
"      else\n"
"	nb[1]++;\n"
"      free_path(&p);\n"
"      t2 = time(NULL);\n"
"      if( t2 - t1 > 1 )\n"
"	{\n"
"	  t1 = t2;\n"
"	  if(write(1, nb, 2*sizeof(int))!=2*sizeof(int))\n"
"	    return -2;\n"
"	  nb[0] = nb[1] = 0;\n"
"	}\n"
"    }\n"
"  return 0;\n"
"}\n";

int generate_code_with_compiler( FILE *f, ltl_expr *e, struct pmfile *pf, 
                                 struct compiler *comp ) 
{ 
  int nbvar = 0;
  fprintf(f, "%s\n", GENERIC_OPENING);

  nbvar = generate_variables(f, pf);
  (void)generate_formulas(f, pf);
  generate_handle_state(f, pf, nbvar);

  fprintf(f, "%s\n", comp->opening);
  if( comp->comp(f, pf) < 0)
    return -1;

  if(generate_verifier(f, pf->variables, e) < 0)
    return -2;

  fprintf(f, "%s\n", comp->closing);
  fprintf(f, "%s\n", GENERIC_CLOSING);
  return 0;
}
