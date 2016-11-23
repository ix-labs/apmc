/* APMC - Approximate Model Checker
 * Copyright (C) 2003, 2005 Thomas Hérault, Frédéric Magniett and Sylvain Peyronnet
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

#ifndef _RM_H_
#define _RM_H_

#include "expr.h"
#ifdef DMALLOC
#include <dmalloc.h>
#endif
#ifdef EFENCE
#include <efence.h>
#endif

typedef struct renamelist {
  unsigned char is_var;
  union {
    struct {
      struct vardef *what;
      struct vardef *into;
    } var;
    struct {
      char *what;
      char *into;
    } synchro;
  } u;
  struct renamelist *next;
} renamelist;

#define CONST_INT   1
#define CONST_FLOAT 2

typedef struct constdef {
  char *name;
  char kind;
  union {
    int    intvalue;
    double  floatvalue;
  } u;
} constdef;

typedef struct vardef {
  struct vardef *next;
  char *name;
  int min;
  int max;
  int initial_value;
  int current_value;
  int nbref;
} vardef;

#define var_is_undef(v) (((v)->min == (v)->max) && ((v)->min == (v)->initial_value) && ((v)->min == (v)->current_value) && ((v)->min == -1))

typedef struct value_list {
  int value;
  struct value_list *next;
} value_list;

typedef struct formuladef {
  char *name;
  struct expr *exp;
} formuladef;

typedef struct affectations {
  struct expr *id;
  struct expr *exp;
  struct affectations *next;
} affectations;

typedef struct probaff {
  struct expr *proba;
  affectations *det;
  struct probaff *next;
} probaff;

typedef struct action {
  char  probabilistic;
  union {
    affectations *det;
    probaff *prob;
  } u;
} action;

typedef struct rule {
  char *stateofrule;
  struct expr *guard;
  action *act;
  struct rule *next;
} rule;

typedef struct moduledef {
  char *modulename;
  rule *rules;
} moduledef;

#define PMENTRY_TYPE   1
#define PMENTRY_CONST  2
#define PMENTRY_MODULE 3
#define PMENTRY_FORM   4

typedef struct pmentry {
  char kind;
  union {
    int file_type;
    constdef   *constant;
    moduledef  *module;
    formuladef *formula;
  } u;
  struct pmentry *next;
  struct pmentry *prev;
} pmentry;

#define PMFILE_PROBABILISTIC 1

typedef struct pmfile {
  char kind;
  pmentry *constants;
  pmentry *formulas;
  pmentry *modules;
  vardef  *variables;
} pmfile;

typedef struct action_list {
  action *act;
  struct action_list *next;
} action_list;

typedef struct action_list_list {
  action_list *al;
  struct action_list_list *next;
} action_list_list;

#define new(a) (a*)calloc(1, sizeof(a))
#define ifree(a) if(a) do{ free(a); a = NULL; } while(0)
#define icall(f, a)  do { f(a); ifree(a); } while(0)

struct expr *new_exp_from_int(int v);
struct value_list *vl_build(int from, int to);
struct value_list *vl_append(struct value_list *v1, struct value_list *v2);
int    id_is_synchro(char *name);
int    change_initial_value(struct pmfile *f, char *name, int value);

//int isblank(char);
int rm_error(char *);

extern struct pmfile *PMFILE;
extern FILE *rm_in;

int rm_parse();
extern int rm_lineno;

#include "rm_free.h"
#include "rm_clone.h"
#include "rm_display.h"

int generate_variables(FILE *out,struct pmfile *f);
int generate_formulas(FILE *out,struct pmfile *f);
void generate_handle_state(FILE *out,struct pmfile *f, int nbvar);
void generate_probaff(FILE *out, struct probaff *p, struct pmfile *f);
void generate_aff(FILE *out, struct affectations *a);

#endif
