#include <stdlib.h>
#include <string.h>

#include "compilers.h"

struct compiler *COMPILERS = NULL;

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
"#ifdef HAVE_SYS_FILIO_H\n"
"# include <sys/filio.h>\n"
"#endif\n"
"#include <unistd.h>\n"
"#include <stdlib.h>\n"
"#include <stdio.h>\n"
"#include <string.h>\n"
"#include <time.h>\n"
"#include <sys/time.h>\n"
"#include <sys/ioctl.h>\n"
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
"  conf *actual;\n"
"} path;\n"
"\n"
"typedef int (*tester_t)(const conf *);\n"
"\n"
"static int until(tester_t left, tester_t right, const conf *c)\n"
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
"static int next(tester_t w, const conf *c)\n"
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
"static void format_data(char *type, long int *nb)\n"
"{\n"
"  static char buf[25];\n"
"  static char buf_res[25];\n"
"  int  n;\n"
"  sprintf(buf, \"%lx\", *nb);\n"
"  sprintf(buf_res, \"%s:0x\", type);\n"
"  n = 20 - strlen(buf_res) - strlen(buf);\n"
"  while (n-- > 0)\n"
"    strcat(buf_res, \"0\");\n"
"  printf(\"%s%s\", buf_res, buf);\n"
"}\n"
"int main(int argc, char *argv[])\n"
"{  \n"
"  int i;\n"
"  struct timeval tv;\n"
"  path p = { NULL, NULL };\n"
"  int path_len;\n"
"  long int nb[2*NB_VERIF_GOAL];\n"
"  time_t t1, t2, t0;\n"
"\n"
"  if(argc != 2)\n"
"    return -1;\n"
"  path_len = atoi(argv[1]);\n"
"\n"
"  gettimeofday(&tv, NULL);\n"
"  srand(tv.tv_sec);\n"
"  \n"
"  memset(nb, 0, sizeof(int)*2*NB_VERIF_GOAL);\n"
"  t1 = t0 = time(NULL);\n"
"  init_state(&p);\n"
"  append_state(&p, 1);\n"
"  for (i = 0; i < path_len; i++)\n"
"    append_state(&p, 1);\n"
"  for(;;)\n"
"    {\n"
"      init_state(&p);\n"
"      append_state(&p, 0);\n"
"      for(i = 0; i < path_len; i++)\n"
"	{\n"
"	  atomic_step();\n"
"	  append_state(&p, 0);\n"
"         p.actual = p.actual->next;\n"
"	}\n"
"      for(i = 0; i < NB_VERIF_GOAL; i++)\n"
"        {\n"
"           if( VERIF_GOAL[i](p.first) )\n"
"              nb[2*i]++;\n"
"           else\n"
"	       nb[2*i+1]++;\n"
"        }\n"
"      /*free_path(&p);*/\n"
"      t2 = time(NULL);\n"
"      if( t2 - t1 >= 1 )\n"
"	{\n"
"	  t1 = t2;\n"
"	  format_data(\"OK\", &(nb[0]));\n"
"	  format_data(\"KO\", &(nb[1]));\n"
"	  fflush(stdout);\n"
//"	  if(write(1, nb, 2*sizeof(int)*NB_VERIF_GOAL) != 2*sizeof(int)*NB_VERIF_GOAL)\n"
//"	    return -2;\n"
"         memset(nb, 0, sizeof(int)*2*NB_VERIF_GOAL);\n"
"	}\n"
"      if (t2 - t0 > 30)\n"
"       {\n"
"         int n_read;\n"
"         char buf[1024];\n"
"         t0 = t2;\n"
"         ioctl(STDIN_FILENO, FIONREAD, &n_read);\n"
"         if (n_read == 0)\n"
"           exit(2);\n"
"         read(STDIN_FILENO, buf, n_read > 1023 ? 1023 : n_read);\n"
"       }\n"
"    }\n"
"  return 0;\n"
"}\n";

static int decore_tree(vardef *v, expr *e)
{
  int i;
  vardef *p;

  if( is_binary(e->ekind) )
    {
      return decore_tree(v, e->eleft) && decore_tree(v, e->eright);
    }
  else if(is_unary(e->ekind))
    {
      return decore_tree(v, e->eexp);
    }
  else if(is_ternary(e->ekind))
    {
      return decore_tree(v, e->eif) &&
	decore_tree(v, e->ethen) &&
	decore_tree(v, e->eelse);
    }
  else if(e->ekind == ID)
    {
      for (p = v, i = 0; p; p = p->next, i++)
	{
	  if (!strcmp(p->name, e->evar->name))
	    {
	      e->evar->name = (char*)realloc(e->evar->name, 24);
	      sprintf(e->evar->name, "c->values[%d]", i);
	      return 1;
	    }
	}
      return 0;
    }
  return 1;
}

static int generate_verifier(FILE *out, struct vardef *v, exprlist *le)
{
  char *exp_str;
  expr *e;
  int i, j;
  int r;
  struct vardef *d;

  r = 0;
  i = 0;

  for(e = le->e; le; le = le->next)
    {
      if( !decore_tree(v, e) )
	{
	  r = -1;
	  continue;
	}

      exp_str = generate_expr(out, e, "(const conf *c)");
      if(!exp_str)
	{
	  r = -1;
	  continue;
	}

      fprintf(out, "static int verify_path_%d(const conf *c)\n{\n  return (%s);\n}\n\n", i, exp_str);
      free(exp_str);
      i++;
    }

  fprintf(out, "#define NB_VERIF_GOAL %d\n", i);
  fprintf(out, "typedef int (*verifier_func_t)(const conf *c);\n");
  fprintf(out, "verifier_func_t VERIF_GOAL[] = {\n");
  for(j = 0; j < i; j++)
    fprintf(out, "  verify_path_%d%s\n", j, j<i-1?",":"");
  fprintf(out, "};\n\n");
  return r;
}

int generate_code_with_compiler( FILE *f, exprlist *le, struct pmfile *pf,
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

  if(generate_verifier(f, pf->variables, le) < 0)
    return -2;

  fprintf(f, "%s\n", comp->closing);
  fprintf(f, "%s\n", GENERIC_CLOSING);
  return 0;
}

void init_library_apmc(void)
{
  init_strategy1();
  init_strategy2();
  init_strategy3();
}
