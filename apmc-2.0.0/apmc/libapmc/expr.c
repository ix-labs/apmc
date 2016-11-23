#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "expr.h"

#ifdef DEBUG
#define debug(toto...) printf(toto)
#else
#define debug(toto...) do {} while(0)
#endif

#ifdef OUTPUT_VCG
FILE *VCG_OUTPUT;
#endif

static int expr_error_number;
static int expression_number;

static char *snappend(char *s, int *size, char *format, ...)
{
  va_list ap;
  char *sprime;
  int sprimesize;
  int r;
  int slen;

  slen = strlen(s);
  sprime = s+slen;
  sprimesize = (*size) - slen;

  va_start(ap, format);
  r = vsnprintf(sprime, sprimesize, format, ap);
  va_end(ap);

  if(r >= sprimesize)
    {
      *size += r + 1;
      s = (char*)realloc(s, *size);

      sprime = s+slen;
      sprimesize = (*size) - slen;

      va_start(ap, format);
      vsnprintf(sprime, sprimesize, format, ap);
      va_end(ap);
    }

  return s;
}

char *generate_expr(FILE *stream, expr *e, char *prototype)
{
  static const char *binary_operands[] = 
    { "&&", "||", "==", "!=" ,"<", ">", "<=", ">=", "+", "-", "*", "/" };
  char *ce = (char*)calloc(1, 1);
  char *op1 = NULL, *op2 = NULL, *op3 = NULL;
  char  funcname[64+strlen(prototype)];
  int cesize = 0;

  ce = snappend(ce, &cesize, "(", e);

  if( is_unary(e->ekind) )
    {
      vcg_edge(e, e->eexp, "%s", "");
      op1 = generate_expr(stream, e->eexp, prototype);
    }
  else if( is_binary(e->ekind) )
    {
      vcg_edge(e, e->eleft, "%s", "");
      vcg_edge(e, e->eright, "%s", "");
      op1 = generate_expr(stream, e->eleft, prototype);
      op2 = generate_expr(stream, e->eright, prototype);
    }
  else if( is_ternary(e->ekind) )
    {
      vcg_edge(e, e->eif, "%s", "");
      vcg_edge(e, e->ethen, "%s", "");
      vcg_edge(e, e->eelse, "%s", "");
      op1 = generate_expr(stream, e->eif, prototype);
      op2 = generate_expr(stream, e->ethen, prototype);
      op3 = generate_expr(stream, e->eelse, prototype);
    }

  switch(e->ekind)
    {
    case CST:
      switch(e->etype)
	{
	case INT:
	  vcg_node(e, "cst: %d", e->eint_value);
	  ce = snappend(ce, &cesize, "%d", e->eint_value);
	  break;
	case FLOAT:
	  vcg_node(e, "cst: %f", e->efloat_value);
	  ce = snappend(ce, &cesize, "%f", e->efloat_value);
	  break;
	default:
	  fprintf(stderr, "expr error #%d : malformed expression (constant of unknown type %d)\n", expr_error_number, e->etype);
	  ce = snappend(ce, &cesize, "expr#%d", expr_error_number);
	  expr_error_number++;
	}
      break;
    case ID:
      vcg_node(e, "id: %p<->%s", e->evar, e->evar->name);
      ce = snappend(ce, &cesize, "%s", e->evar->name);
      break;
    case NOT:
      ce = snappend(ce, &cesize, "!%s", op1);
      vcg_node(e, "%s", "not");
      break;
    case NEXT:
      vcg_node(e, "%s", "next");
      sprintf(funcname, "exp_%d", expression_number);
      fprintf(stream, "static int %s%s\n{\n  if(!c) return 0;\n return %s;\n}\n\n", 
	      funcname, prototype, op1);
      ce = snappend(ce, &cesize, "next(%s, c)", funcname);
      expression_number++;
      break;
    case CEIL:
      vcg_node(e, "%s", "ceil");
      ce = snappend(ce, &cesize, "ceil(%s)", op1);
      break;
    case FLOOR:
      vcg_node(e, "%s", "floor");
      ce = snappend(ce, &cesize, "floor(%s)", op1);
      break;
    case AND: case OR: case EQUAL: case NEQ: case LESS: case GREATER:
    case LEQ: case GEQ: case PLUS: case MINUS: case TIMES: 
      vcg_node(e, "%s", binary_operands[e->ekind-AND]);
      ce = snappend(ce, &cesize, "%s %s %s", op1, binary_operands[e->ekind-AND], op2);
      break;
    case DIV:
      vcg_node(e, "%s", "/");
      ce = snappend(ce, &cesize, "(double)%s / (double)%s", op1, op2);
      break;
    case UNTIL:
      vcg_node(e, "%s", "until");
      sprintf(funcname, "exp_%d", expression_number);
      fprintf(stream, "static int %s%s\n{\n  if(!c) return 0;\n  return %s;\n}\n\n", 
	      funcname, prototype, op1);
      ce = snappend(ce, &cesize, "until(%s, ", funcname);
      expression_number++;
      sprintf(funcname, "exp_%d", expression_number);
      fprintf(stream, "static int %s%s\n{\n  if(!c) return 0;\n  return %s;\n}\n\n", 
	      funcname, prototype, op2);
      ce = snappend(ce, &cesize, "%s, c)", funcname);
      expression_number++;
      break;
    case MIN:
      vcg_node(e, "%s", "min");
      ce = snappend(ce, &cesize, "MIN(%s, %s)", op1, op2);
      break;
    case MAX:
      vcg_node(e, "%s", "max");
      ce = snappend(ce, &cesize, "MAX(%s, %s)", op1, op2);
      break;
    case ITE:
      vcg_node(e, "%s", "ite");
      ce = snappend(ce, &cesize, "%s?%s:%s", op1, op2, op3);
      break;
    default:
      fprintf(stderr, "expr error #%d : malformed expression (unknown kind of operand %d)\n", expr_error_number, e->ekind);
      ce = snappend(ce, &cesize, "expr#%d", expr_error_number);
      expr_error_number++;
    }

  ce = snappend(ce, &cesize, ")");

  if(op1)
    free(op1);
  if(op2)
    free(op2);
  if(op3)
    free(op3);

  return ce;
}

double evaluate_doubleexpr(expr *e, pmentry *consts)
{
  double v1, v2;

  switch(e->ekind)
    {
    case ID:
      return e->evar->current_value;
    case CST:
      if(e->etype == INT)
	return (double)e->eint_value;
      else
	return (double)e->efloat_value;
    case NOT:
      return !evaluate_intexpr(e->eexp, consts);
    case NEXT:
      fprintf(stderr, "evaluate_intexpr error : unable to evaluate value of NEXT at compile-time\n");
      return -1.0;
    case CEIL:
      return ceil(evaluate_doubleexpr(e->eexp, consts));
    case FLOOR:
      return floor(evaluate_doubleexpr(e->eexp, consts));
    case AND:
      return evaluate_intexpr(e->eleft, consts) && evaluate_intexpr(e->eright, consts);
    case OR:
      return evaluate_intexpr(e->eleft, consts) || evaluate_intexpr(e->eright, consts);
    case EQUAL:
      return evaluate_doubleexpr(e->eleft, consts) == evaluate_doubleexpr(e->eright, consts);
    case NEQ:
      return evaluate_doubleexpr(e->eleft, consts) != evaluate_doubleexpr(e->eright, consts);
    case LESS:
      return evaluate_doubleexpr(e->eleft, consts) < evaluate_doubleexpr(e->eright, consts);
    case GREATER:
      return evaluate_doubleexpr(e->eleft, consts) > evaluate_doubleexpr(e->eright, consts);
    case LEQ:
      return evaluate_doubleexpr(e->eleft, consts) <= evaluate_doubleexpr(e->eright, consts);
    case GEQ:
      return evaluate_doubleexpr(e->eleft, consts) >= evaluate_doubleexpr(e->eright, consts);
    case PLUS:
      return evaluate_doubleexpr(e->eleft, consts) + evaluate_doubleexpr(e->eright, consts);
    case MINUS:
      return evaluate_doubleexpr(e->eleft, consts) - evaluate_doubleexpr(e->eright, consts);
    case TIMES:
      return evaluate_doubleexpr(e->eleft, consts) * evaluate_doubleexpr(e->eright, consts);
    case DIV:
      return evaluate_doubleexpr(e->eleft, consts) / evaluate_doubleexpr(e->eright, consts);
    case MIN:
      v1 = evaluate_doubleexpr(e->eleft, consts);
      v2 = evaluate_doubleexpr(e->eright, consts);
      return v1<v2 ? v1 : v2;
    case MAX:
      v1 = evaluate_doubleexpr(e->eleft, consts);
      v2 = evaluate_doubleexpr(e->eright, consts);
      return v1>v2 ? v1 : v2;
    case UNTIL:
      fprintf(stderr, "evaluate_intexpr error : unable to evaluate value of UNTIL at compile-time\n");
      return -1.0;
    case ITE:
      if(evaluate_intexpr(e->eif, consts))
	return evaluate_doubleexpr(e->ethen, consts);
      else
	return evaluate_doubleexpr(e->eelse, consts);
    default:
      fprintf(stderr, "evaluate_intexpr error : malformed expression (unknown operator %d)\n", e->ekind);
      return -1.0;
    }
}

int evaluate_intexpr(expr *e, pmentry *consts)
{
  int v1, v2;

  switch(e->ekind)
    {
    case ID:
      return e->evar->current_value;
    case CST:
      return e->eint_value;
    case NOT:
      return !evaluate_intexpr(e->eexp, consts);
    case NEXT:
      fprintf(stderr, "evaluate_intexpr error : unable to evaluate value of NEXT at compile-time\n");
      return -1;
    case CEIL:
      return ceil(evaluate_intexpr(e->eexp, consts));
    case FLOOR:
      return floor(evaluate_intexpr(e->eexp, consts));
    case AND:
      return evaluate_intexpr(e->eleft, consts) && evaluate_intexpr(e->eright, consts);
    case OR:
      return evaluate_intexpr(e->eleft, consts) || evaluate_intexpr(e->eright, consts);
    case EQUAL:
      return evaluate_intexpr(e->eleft, consts) == evaluate_intexpr(e->eright, consts);
    case NEQ:
      return evaluate_intexpr(e->eleft, consts) != evaluate_intexpr(e->eright, consts);
    case LESS:
      return evaluate_intexpr(e->eleft, consts) < evaluate_intexpr(e->eright, consts);
    case GREATER:
      return evaluate_intexpr(e->eleft, consts) > evaluate_intexpr(e->eright, consts);
    case LEQ:
      return evaluate_intexpr(e->eleft, consts) <= evaluate_intexpr(e->eright, consts);
    case GEQ:
      return evaluate_intexpr(e->eleft, consts) >= evaluate_intexpr(e->eright, consts);
    case PLUS:
      return evaluate_intexpr(e->eleft, consts) + evaluate_intexpr(e->eright, consts);
    case MINUS:
      return evaluate_intexpr(e->eleft, consts) - evaluate_intexpr(e->eright, consts);
    case TIMES:
      return evaluate_intexpr(e->eleft, consts) * evaluate_intexpr(e->eright, consts);
    case DIV:
      return evaluate_intexpr(e->eleft, consts) / evaluate_intexpr(e->eright, consts);
    case MIN:
      v1 = evaluate_intexpr(e->eleft, consts);
      v2 = evaluate_intexpr(e->eright, consts);
      return v1<v2 ? v1 : v2;
    case MAX:
      v1 = evaluate_intexpr(e->eleft, consts);
      v2 = evaluate_intexpr(e->eright, consts);
      return v1>v2 ? v1 : v2;
    case UNTIL:
      fprintf(stderr, "evaluate_intexpr error : unable to evaluate value of UNTIL at compile-time\n");
      return -1;
    case ITE:
      if(evaluate_intexpr(e->eif, consts))
	return evaluate_intexpr(e->ethen, consts);
      else
	return evaluate_intexpr(e->eelse, consts);
    default:
      fprintf(stderr, "evaluate_intexpr error : malformed expression (unknown operator %d)\n", e->ekind);
      return -1;
    }
}

expr *new_expr_by_intcst(int cst)
{
  expr *e;
  e = new(expr);
  e->ekind = CST;
  e->etype = INT;
  e->eint_value = cst;
  return e;
}

expr *new_expr_by_floatcst(float cst)
{
  expr *e;
  e = new(expr);
  e->ekind = CST;
  e->etype = FLOAT;
  e->efloat_value = cst;
  return e;
}

struct vardef *lookup_or_create_var(char *name)
{
  struct vardef  *v;
  
  for(v = PMFILE->variables; v; v = v->next)
    {
      debug("comparing %s with %s\n", name, v->name);
      if(!strcmp(v->name, name))
	{
	  v->nbref++;
	  return v;
	}
    }

  v = new(struct vardef);
  v->name = strdup(name);
  v->min  = -1;
  v->max  = -1;
  v->initial_value = -1;
  v->current_value = -1;
  v->nbref = 1;
  v->next = PMFILE->variables;
  PMFILE->variables = v;
  
  return v;
}

struct expr *new_expr_by_id(char *name, 
			    unsigned char where_to_search)
{
  struct pmentry *c;
  struct expr *n;
  struct vardef *v;

  if(where_to_search & SEARCH_IN_FORMULAE)
    {
      debug("searching for %s in formulas\n", name);
      for(c = PMFILE->formulas; c; c = c->next)
	if(!strcmp(c->u.formula->name, name))
	  {
	    n = clone_expression(c->u.formula->exp, NULL);
	    goto out;
	  }
    }

  if(where_to_search & SEARCH_IN_CONSTANTS)
    {
      debug("searching for %s in constants\n", name);
      for(c = PMFILE->constants; c; c = c->next)
	if(!strcmp(c->u.constant->name, name))
	  {
	    if( c->u.constant->kind == CONST_INT )
	      n = new_expr_by_intcst(c->u.constant->u.intvalue);
	    else
	      n = new_expr_by_floatcst(c->u.constant->u.floatvalue);
	    goto out;
	  }
    }

  if(where_to_search & SEARCH_IN_VARIABLES)
    {
      debug("searching for %s in variables\n", name);
      v = lookup_or_create_var(name);
      n = new(expr);
      n->ekind = ID;
      n->evar = v;
      goto out;
    }

  return NULL;

 out:
  return n;
}

expr *new_expr_by_unary(int operand, expr *exp)
{
  expr *e;
  e = new(expr);
  e->ekind = operand;
  switch(operand)
    {
    case NOT:
    case NEXT:
    case CEIL:
    case FLOOR:
      e->etype = INT;
      break;
    default:
      e->etype = exp->etype;
    }
  e->eexp = exp;
  return e;
}

expr *new_expr_by_binary(expr *left, int operand, expr *right)
{
  expr *e;
  e = new(expr);
  e->ekind = operand;
  e->etype = ((left->etype == INT) && (right->etype == INT)) ? INT : FLOAT;
  e->eleft = left;
  e->eright = right;
  return e;
}

expr *new_expr_by_ternary(int operand, expr *one, expr *two, expr *three)
{
  expr *e;
  e = new(expr);
  e->ekind = operand;
  if(operand == ITE)
    e->etype = (two->etype == INT) && (three->etype == INT) ? INT : FLOAT;
  else
    e->etype = INT; /**< NO OTHER TERNARY OPERAND THAN ITE NOW */

  e->eif = one;
  e->ethen = two;
  e->eelse = three;
  return e;
}

void free_expr(struct expr *e)
{
  if(!e) return;

  if( is_unary(e->ekind) )
    {
      icall(free_expr, e->eexp);
    }
  else if(is_binary(e->ekind))
    {
      icall(free_expr, e->eleft);
      icall(free_expr, e->eright);
    }
  else if(is_ternary(e->ekind))
    {
      icall(free_expr, e->eif);
      icall(free_expr, e->ethen);
      icall(free_expr, e->eelse);
      }
  else if (e->ekind == ID)
    {
      e->evar->nbref--;
      if(e->evar->nbref == 0)
	icall(free_var, e->evar);
    }
}

expr *new_equal_el(expr *a, exprlist *v)
{
  expr *e, *r, *f;
  
  if(v->next)
    {
      r = new_expr_by_binary(clone_expression(a, NULL), EQUAL, v->e);
      e = new_equal_el(a, v->next);
      f = new_expr_by_binary(r, OR, e);
    }
  else
    {
      f = new_expr_by_binary(a, EQUAL, v->e);
    }
  free(v);
  
  return f;   
}

struct exprlist *new_exprlist_range(expr *a, expr *b)
{
  int v1, v2;
  char msg[256];
  struct exprlist *el;
  
  el = NULL;

  if( (a->ekind != CST) || (a->etype != INT) )
    {
      sprintf(msg, "when defining a range, left expression MUST be constant integer");
      rm_error(msg);
      return NULL;
    }
  if( (b->ekind != CST) || (b->etype != INT) )
    {
      sprintf(msg, "when defining a range, right expression MUST be constant integer");
      rm_error(msg);
      return NULL;
    }
  v1 = a->eint_value;
  icall(free_expr, a);
  v2 = b->eint_value;
  icall(free_expr, b);

  if(v1 > v2)
    {
      sprintf(msg, "value range is not coherent [%d..%d]", v1, v2);
      rm_error(msg);
      return NULL;
    }
  else
    {
      int i;
      struct exprlist *v;

      el = NULL;
      for(i = v2; i > v1; i--)
	{
	  v = new(struct exprlist);
	  v->e = new_expr_by_intcst(i);
	  v->next = el;
	  el = v;
	}
      v = new(struct exprlist);
      v->e = new_expr_by_intcst(i);
      v->next = el;
      el = v;
    }

  return el;
}
