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

#ifndef _path_h_
#define _path_h_

#include <stdio.h>

 int ltl_error(char *);
 int ltl_lex();

typedef struct ltl_expr {
    char kind;
    union {
      struct exp_binary {
	char op;
	struct ltl_expr *left;
	struct ltl_expr *right;
      } binary;
      struct exp_unary {
	char op;
	struct ltl_expr *exp;
      } unary;
      struct exp_id {
	int index;
	char *name;
      } id;
      struct exp_const {
	int value;
      } cst;
    } u;
  } ltl_expr;

#define LTL_BINARY   1
#define LTL_UNARY    2
#define LTL_VARIABLE 3
#define LTL_CONSTANT 4

typedef struct conf {
  int *values;
  struct conf *next;
  struct conf *prev;
} conf;


typedef struct path {
  int nb_vars;
  char ** variables;
  conf * first;
  conf * last;
} path;

struct vardef;

path * parsepath_fromfile(int fd);
void free_path(path *p);
void print_path(path *p);
void print_conf(path *p, conf *c);
void decore_tree(path *s,struct ltl_expr *e);
int decore_tree2(struct vardef *v, struct ltl_expr *e);
int verify_path(conf *c,ltl_expr *e);
void display_ltl_expression(struct ltl_expr *e, int level);
void free_LTL();
int generate_verifier(FILE *out, struct vardef *v, ltl_expr *e);

extern struct ltl_expr *LTL;
extern FILE *ltl_in;
int ltl_parse();
extern int ltl_lineno;

#endif
