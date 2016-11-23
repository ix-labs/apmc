//==============================================================================
//	
//	Copyright (c) 2002-2004, Dave Parker
//	
//	This file is part of PRISM.
//	
//	PRISM is free software; you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation; either version 2 of the License, or
//	(at your option) any later version.
//	
//	PRISM is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//	
//	You should have received a copy of the GNU General Public License
//	along with PRISM; if not, write to the Free Software Foundation,
//	Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//	
//==============================================================================

package parser;

import java.util.Vector;

public class PCTLBoundedUntil extends PCTLFormulaBinary
{
	Expression lBound = null;  	// none if null, i.e. zero
	Expression uBound = null;	// none if null, i.e. infinity
	String probRelOp;
	Expression prob;
	PCTLFormula filter;
	
	// constructor
	
	public PCTLBoundedUntil(PCTLFormula f1, PCTLFormula f2, Expression l, Expression u, String pr, Expression p)
	{
		super(f1, f2);
		lBound = l;
		uBound = u;
		probRelOp = pr;
		prob = p;
		filter = null;
	}

	public void setFilter(PCTLFormula f)
	{
		filter = f;
	}
		
	public Expression getLowerBound()
	{
		return lBound;
	}

	public Expression getUpperBound()
	{
		return uBound;
	}

	public String getProbRelOp()
	{
		return probRelOp;
	}
	
	public Expression getProb()
	{
		return prob;
	}

	public PCTLFormula getFilter()
	{
		return filter;
	}

	// check all labels (make sure the referred labels exist)
	
	public void checkLabelIdents(LabelList labelList) throws ParserException
	{
		// call superclass (binary)
		super.checkLabelIdents(labelList);
		// also do filter
		if (filter != null) filter.checkLabelIdents(labelList);
	}

	// find all constants (i.e. locate idents which are constants)
	
	public PCTLFormula findAllConstants(ConstantList constantList) throws ParserException
	{
		// call superclass (binary)
		super.findAllConstants(constantList);
		// also do prob/tim expressions
		if (lBound != null) lBound = lBound.findAllConstants(constantList);
		if (uBound != null) uBound = uBound.findAllConstants(constantList);
		if (prob != null) prob = prob.findAllConstants(constantList);
		// also do filter
		if (filter != null) filter = filter.findAllConstants(constantList);
		
		return this;
	}
	
	// find all variables (i.e. locate idents which are variables)
	
	public PCTLFormula findAllVars(Vector varIdents, Vector varTypes) throws ParserException
	{
		// call superclass (binary)
		super.findAllVars(varIdents, varTypes);
		// also do prob/time expressions
		if (lBound != null) lBound = lBound.findAllVars(varIdents, varTypes);
		if (uBound != null) uBound = uBound.findAllVars(varIdents, varTypes);
		if (prob != null) prob = prob.findAllVars(varIdents, varTypes);
		// also do filter
		if (filter != null) filter = filter.findAllVars(varIdents, varTypes);
		
		return this;
	}
	
	// type check
	
	public void typeCheck() throws ParserException
	{
		// call superclass (binary)
		super.typeCheck();
		// check prob is double
		if (prob != null) if (!Expression.canAssignTypes(Expression.DOUBLE, prob.getType())) {
			throw new ParserException("Probability \"" + prob + "\" is the wrong type");
		}
		// check any time bounds are of type int/double
		if (lBound != null) if (!(lBound.getType() == Expression.INT || lBound.getType() == Expression.DOUBLE)) {
			throw new ParserException("Time bound \"" + lBound + "\" is the wrong type");
		}
		if (uBound != null) if (!(uBound.getType() == Expression.INT || uBound.getType() == Expression.DOUBLE)) {
			throw new ParserException("Time bound \"" + uBound + "\" is the wrong type");
		}
		// check filter is boolean
		if (filter != null) if (filter.getType() != Expression.BOOLEAN) {
			throw new ParserException("Expression \"" + filter + "\" must be Boolean");
		}
		// set type if necesary (default of Boolean already assigned by superclass)
		if (prob == null) setType(Expression.DOUBLE);
	}

	// check everything is ok
	
	public void check() throws ParserException
	{
		// call superclass (binary)
		super.check();
		
		// check prob is ok and constant
		if (prob != null) {
			prob.check();
			if (!prob.isConstant()) {
				throw new ParserException("Probability \"" + prob + "\" is not constant");
			}
		}
		// check any time bounds are ok and constant
		if (lBound != null) {
			lBound.check();
			if (!lBound.isConstant()) {
				throw new ParserException("Time bound \"" + lBound + "\" is not constant");
			}
		}
		if (uBound != null) {
			uBound.check();
			if (!uBound.isConstant()) {
				throw new ParserException("Time bound \"" + uBound + "\" is not constant");
			}
		}
		// check filter
		if (filter != null) filter.check();
	}

	// check if formula is valid pctl
	
	public void checkValidPCTL() throws ParserException
	{
		// must have upper bound only
		if (lBound != null) throw new ParserException("PCTL bounded until formulas must have bounds of the form \"<=k\"");
		// and it must be an integer
		if (uBound.getType() != Expression.INT) throw new ParserException("Bounds in PCTL bounded until formulas must be of type integer");
	}

	// check if formula is valid csl
	
	public void checkValidCSL() throws ParserException
	{
		// ok
	}

	// compute the max depth of prob operator nestings
	
	public int computeMaxNested()
	{
		return 1 + super.computeMaxNested();
	}

	// convert to string
	
	public String toString()
	{
		String s = "";
		
		s += "P" + probRelOp;
		s += (prob==null) ? "?" : prob.toString();
		s += " [ " + operand1 + " U";
		if (lBound == null) {
			s += "<=" + uBound;
		}
		else if (uBound == null) {
			s += ">=" + lBound;
		}
		else {
			s += "[" + lBound + "," + uBound + "]";
		}
		s += " " + operand2;
		if (filter != null) s+= " {" + filter + "}";
		s += " ]";
		
		return s;
	}
}

//------------------------------------------------------------------------------
