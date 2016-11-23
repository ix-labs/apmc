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

#ifndef _RM_H_
#define _RM_H_

#include "path.h"

struct renamelist {
  char *what;
  char *into;
  struct renamelist *next;
};

#define CONST_INT   1
#define CONST_FLOAT 2

struct constdef {
  char *name;
  char kind;
  union {
    int    intvalue;
    double  floatvalue;
  } u;
};

#define ID_VAR 1
#define ID_CST 2

struct identifier {
  char kind;
  union {
    struct constdef *cst;
    struct vardef   *var;
  } u;
};

struct value_list {
  int value;
  struct value_list *next;
};

#define E_ID     1
#define E_BINARY 2
#define E_CSTE   3
#define E_VL     4

#define E_BIN_PLUS  1
#define E_BIN_MINUS 2
#define E_BIN_MIN   3
#define E_BIN_MAX   4
#define E_BIN_TIMES 5

struct expr {
  char kind;
  union {
    int cste;
    struct identifier *id;
    struct e_binary {
      char op;
      struct expr *left;
      struct expr *right;
    } binary;
    struct value_list *vl;
  } u;      
};

#define BE_UNARY      1
#define BE_LOG_BINARY 2
#define BE_FORMULA    3
#define BE_EXP_BINARY 4

#define BE_UNARY_NOT  1
#define BE_BIN_AND    2
#define BE_BIN_OR     3

#define BE_EBIN_EQ       1
#define BE_EBIN_NEQ      2
#define BE_EBIN_LESSER   3
#define BE_EBIN_GREATER  4
#define BE_EBIN_LEQ      5
#define BE_EBIN_GEQ      6

struct boolexpr {
  char kind;
  union {
    struct be_unary {
      char op;
      struct boolexpr *exp;
    } unary;
    struct be_binary {
      char op;
      struct boolexpr *left;
      struct boolexpr *right;
    } binary;
    struct be_exp_binary {
      char op;
      struct expr *left;
      struct expr *right;
    } exp_binary;
    struct formuladef *formula;
  } u;
};

struct formuladef {
  unsigned int nbref;
  char *name;
  struct boolexpr *expr;
};

struct vardef {
  struct vardef *next;
  char *name;
  int min;
  int max;
  int initial_value;
  int current_value;
};

struct affectations {
  struct identifier *id;
  struct expr *exp;
  struct affectations *next;
};

struct probaff {
  double proba;
  struct affectations *det;
  struct probaff *next;
};

struct action {
  char  probabilistic;
  union {
    struct affectations *det;
    struct probaff *prob;
  } u;
};

struct rule {
  char *stateofrule;
  struct boolexpr *guard;
  struct action *act;
  struct rule *next;
};

struct moduledef {
  char *modulename;
  struct rule   *rules;
};

#define PMENTRY_TYPE   1
#define PMENTRY_CONST  2
#define PMENTRY_MODULE 3
#define PMENTRY_FORM   4

struct pmentry {
  char kind;
  union {
    int file_type;
    struct constdef   *constant;
    struct moduledef  *module;
    struct formuladef *formula;
  } u;
  struct pmentry *next;
  struct pmentry *prev;
};

#define PMFILE_PROBABILISTIC 1

struct pmfile {
  char kind;
  struct pmentry *constants;
  struct pmentry *formulas;
  struct pmentry *modules;
  struct vardef  *variables;
};

struct action_list {
  struct action *act;
  struct action_list *next;
};

struct action_list_list {
  struct action_list *al;
  struct action_list_list *next;
};

#define new(a) (a*)calloc(1, sizeof(a))
#define ifree(a) if(a) do{ *(unsigned int*)a = __LINE__; free(a); a = NULL; } while(0)
#define icall(f, a)  do { f(a); ifree(a); } while(0)

int evaluate_expression(struct expr *e, struct pmentry *consts);
struct expr *new_exp_from_int(int v);
struct value_list *vl_build(int from, int to);
struct value_list *vl_append(struct value_list *v1, struct value_list *v2);

struct identifier *new_id_by_name(char *name, unsigned char may_be_constant);
int isblank(char);
int rm_error(char *);

extern struct pmfile *PMFILE;
extern FILE *rm_in;

int rm_parse();
extern int rm_lineno;

void generate_bool_expr(FILE *out, struct boolexpr *b);
void generate_aff(FILE *out, struct affectations *a);
void generate_probaff(FILE *out, struct probaff *p);
int generate_variables(FILE *out,struct pmfile *f);
int generate_formulas(FILE *out,struct pmfile *f);
void generate_handle_state(FILE *out,struct pmfile *f,int nbvar);

#include "rm_free.h" 
#include "rm_clone.h"
#include "rm_interp.h"
#include "rm_display.h"


#endif
