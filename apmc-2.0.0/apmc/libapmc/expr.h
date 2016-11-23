#ifndef _expr_h_
#define _expr_h_

#include <stdio.h>

struct expr;

#include "reactive-modules.h"

typedef struct expr 
{
  unsigned char kind;
  unsigned char type;
  union {
    struct exp_ternary {
      struct expr *operand[3];
    } ternary;
    struct exp_binary {
      struct expr *left;
      struct expr *right;
    } binary;
    struct exp_unary {
      struct expr *exp;
    } unary;
    struct vardef *var;
    int    int_value;
    double float_value;
  } u;
} expr;

typedef struct exprlist {
  struct expr *e;
  struct exprlist *next;
} exprlist;

/* helpers */

#define ekind        kind
#define etype        type
#define eleft        u.binary.left
#define eright       u.binary.right
#define eif          u.ternary.operand[0]
#define ethen        u.ternary.operand[1]
#define eelse        u.ternary.operand[2]
#define eexp         u.unary.exp
#define evar         u.var
#define eint_value   u.int_value
#define efloat_value u.float_value

/* type definition */
#define INT   1
#define FLOAT 2

/* operators (kind) definition */

// CONSTANTS and VARIABLES
#define CST  1
#define ID   2

// UNARY verify MIN_UNARY < operator < MAX_UNARY
#define MIN_UNARY   10
#define NOT   11
#define NEXT  12
#define CEIL  13
#define FLOOR 14
#define MAX_UNARY 20
#define is_unary(a) ( ( MIN_UNARY < (a) ) && ( (a) < MAX_UNARY ) )

// BINARY : verify MIN_BINARY < operator < MAX_BINARY
#define MIN_BINARY 20
#define AND     21
#define OR      22
#define EQUAL   23
#define NEQ     24
#define LESS    25
#define GREATER 26
#define LEQ     27
#define GEQ     28
#define PLUS    29
#define MINUS   30
#define TIMES   31
#define DIV     32
#define UNTIL   33
#ifdef MIN
#undef MIN
#endif
#define MIN     34
#ifdef MAX
#undef MAX
#endif
#define MAX     35
#define MAX_BINARY 40
#define is_binary(a) ( ( MIN_BINARY < (a) ) && ( (a) < MAX_BINARY ) )

#define MIN_TERNARY 60
#define ITE     61
#define MAX_TERNARY 70
#define is_ternary(a) ( (MIN_TERNARY < (a) ) && ( (a) < MAX_TERNARY) )

char *generate_expr(FILE *stream, expr *e, char *prototype);
struct pmentry;
int    evaluate_intexpr(expr *e, struct pmentry *consts);
double evaluate_doubleexpr(expr *e, struct pmentry *consts);

expr *new_expr_by_intcst(int cst);
expr *new_expr_by_floatcst(float cst);
struct vardef *lookup_or_create_var(char *name);
#define SEARCH_IN_FORMULAE  (1<<0)
#define SEARCH_IN_CONSTANTS (1<<1)
#define SEARCH_IN_VARIABLES (1<<2)
expr *new_expr_by_id(char *id, unsigned char where_to_search);
expr *new_expr_by_unary(int operand, expr *exp);
expr *new_expr_by_binary(expr *left, int operand, expr *right);
expr *new_expr_by_ternary(int operand, expr *one, expr *two, expr *three);

#ifdef OUTPUT_VCG
extern FILE *VCG_OUTPUT;
#define vcg_node(title, label_format, param...) do {\
    if(VCG_OUTPUT) \
      fprintf(VCG_OUTPUT, \
	      " node: {\n"\
	      "   title: \"%p\"\n"\
	      "   label: \""label_format"\"\n"\
	      " }\n",\
	      title, param);\
  } while(0)
#define vcg_edge(s, d, label_format, param...) do {\
    if(VCG_OUTPUT) \
      fprintf(VCG_OUTPUT, \
	      " edge: {\n"\
	      "   sourcename: \"%p\"\n"\
	      "   targetname: \"%p\"\n"\
	      "   label: \""label_format"\"\n"\
	      " }\n",\
	      s, d, param);\
  } while(0)
#define vcg_printf(format...) do { if(VCG_OUTPUT) fprintf(VCG_OUTPUT, format); } while(0)
#define vcg_open(filename) do { VCG_OUTPUT = fopen(filename, "w"); } while(0)
#define vcg_close()  fclose(VCG_OUTPUT)
#else
#define vcg_node(title, label_format, param...) do {} while(0)
#define vcg_edge(s, d, label_format, param...) do {} while(0)
#define vcg_printf(format...) do {} while(0)
#define vcg_open(filename) do {} while(0)
#define vcg_close() do {} while(0)
#endif

void free_expr(expr *exp);
expr *new_equal_el(expr *a, exprlist *v);
struct exprlist *new_exprlist_range(expr *a, expr *b);

#endif
