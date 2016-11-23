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

#include "rm_interp.h"
#include <assert.h>
#include <stdlib.h>

int interp_expr(int *state, int nbvar, struct expr *e)
{
  int a, b;
  switch(e->kind)
    {
    case E_ID:
      if(e->u.id->kind == ID_VAR)
	return e->u.id->u.var->current_value;
      else
	{
	  if(e->u.id->u.cst->kind == CONST_INT)
	    return e->u.id->u.cst->u.intvalue;
	  else
	    return (int)e->u.id->u.cst->u.floatvalue;
	}
    case E_BINARY:
      switch ( e->u.binary.op )
	{
	case E_BIN_PLUS:
	  return interp_expr(state, nbvar, e->u.binary.left) +
	    interp_expr(state, nbvar, e->u.binary.right);
	case E_BIN_MINUS:
	  return interp_expr(state, nbvar, e->u.binary.left) -
	    interp_expr(state, nbvar, e->u.binary.right);
	case E_BIN_MIN:
	  a = interp_expr(state, nbvar, e->u.binary.left);
	  b = interp_expr(state, nbvar, e->u.binary.right);
	  if(a < b) return a;
	  else return b;
	case E_BIN_TIMES:
	  return interp_expr(state, nbvar, e->u.binary.left) *
	    interp_expr(state, nbvar, e->u.binary.right);
	default:
	  fprintf(stderr, "binary operand %d is undefined!\n", e->u.binary.op);
	  exit(-1);
	}
    case E_CSTE:
      return e->u.cste;	  
    default:
      assert(0 /* unknown kind of expression */ );
      return 0;
    }
}

int interp_boolexpr(int *state, int nbvar, struct boolexpr *e)
{
  switch(e->kind)
    {
    case BE_UNARY:
      assert( e->u.unary.op == BE_UNARY_NOT );
      return !interp_boolexpr(state, nbvar, e->u.unary.exp);
    case BE_LOG_BINARY:
      if(e->u.binary.op == BE_BIN_AND)
	return interp_boolexpr(state, nbvar, e->u.binary.left)&&
	  interp_boolexpr(state, nbvar, e->u.binary.right);
      else
	{
	  assert( e->u.binary.op == BE_BIN_OR);
	  return interp_boolexpr(state, nbvar, e->u.binary.left)||
	    interp_boolexpr(state, nbvar, e->u.binary.right);
	}
    case BE_EXP_BINARY:
      switch(e->u.exp_binary.op)
	{
	case BE_EBIN_EQ:
	  return interp_expr(state, nbvar, e->u.exp_binary.left) ==
	    interp_expr(state, nbvar, e->u.exp_binary.right);
	case BE_EBIN_NEQ:
	  return interp_expr(state, nbvar, e->u.exp_binary.left) !=
	    interp_expr(state, nbvar, e->u.exp_binary.right);
	case BE_EBIN_LESSER:
	  return interp_expr(state, nbvar, e->u.exp_binary.left) <
	    interp_expr(state, nbvar, e->u.exp_binary.right);
	case BE_EBIN_GREATER:
	  return interp_expr(state, nbvar, e->u.exp_binary.left) >
	    interp_expr(state, nbvar, e->u.exp_binary.right);
	case BE_EBIN_LEQ:
	  return interp_expr(state, nbvar, e->u.exp_binary.left) <=
	    interp_expr(state, nbvar, e->u.exp_binary.right);
	case BE_EBIN_GEQ:
	  return interp_expr(state, nbvar, e->u.exp_binary.left) >=
	    interp_expr(state, nbvar, e->u.exp_binary.right);
	default:
	  assert(0 /* unknown operator */);
	  return 0;
	}
    case BE_FORMULA:
      return interp_boolexpr(state, nbvar, e->u.formula->expr);
    default:
      assert(0 /* unknown kind of boolexpr */);
      return 0;
    }
}
