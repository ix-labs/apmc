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

public class Update
{
	Vector vars;
	Vector exprs;
	Vector types;
	
	// constructor
	
	public Update()
	{
		vars = new Vector();
		exprs = new Vector();
		types = new Vector();
	}
	
	// add element (variable/expression pair)
	
	public void addElement(String v, Expression e)
	{
		vars.addElement(v);
		exprs.addElement(e);
	}
	
	public void addElement(String v, Expression e, Integer t)
	{
		vars.addElement(v);
		exprs.addElement(e);
		types.addElement(t);
	}
	
	// get methods
	
	public int getNumElements()
	{
		return vars.size();
	}
	
	public String getVar(int i)
	{
		return (String)vars.elementAt(i);
	}
	
	public Expression getExpression(int i)
	{
		return (Expression)exprs.elementAt(i);
	}
	
	public int getType(int i)
	{
		return ((Integer)types.elementAt(i)).intValue();
	}
	
	// find all formulas (i.e. locate idents which are formulas)
	
	public void findAllFormulas(FormulaList formulaList) throws ParserException
	{
		int i, n;
		
		n = exprs.size();
		for (i = 0; i < n; i++) {
			exprs.setElementAt(getExpression(i).findAllFormulas(formulaList), i);
		}
	}
	
	// expand any formulas
		
	public void expandFormulas(FormulaList formulaList) throws ParserException
	{
		int i, n;
		
		n = exprs.size();
		for (i = 0; i < n; i++) {
			exprs.setElementAt(getExpression(i).expandFormulas(formulaList), i);
		}
	}
	
	// create and return a new Update by renaming

	public Update rename(RenamedModule rm) throws ParserException
	{
		int i, n;
		String s;
		Update u;
		
		// create new Update
		u = new Update();
		// copy all, changing variables
		n = getNumElements();
		for (i = 0; i < n; i++) {
			s = rm.getNewName(getVar(i));
			s = (s == null) ? getVar(i) : s;
			u.addElement(s, getExpression(i).rename(rm));
		}
		
		return u;
	}
	
	// find all constants (i.e. locate idents which are constants)
	
	public void findAllConstants(ConstantList constantList) throws ParserException
	{
		int i, n;
		
		n = exprs.size();
		for (i = 0; i < n; i++) {
			exprs.setElementAt(getExpression(i).findAllConstants(constantList), i);
		}
	}
	
	// find all variables (i.e. locate idents which are variables)
	
	public void findAllVars(Vector varIdents, Vector varTypes) throws ParserException
	{
		int i, j, n;
		String s;
		
		// go thru all update expressions to find vars
		n = exprs.size();
		for (i = 0; i < n; i++) {
			exprs.setElementAt(getExpression(i).findAllVars(varIdents, varTypes), i);
		}
		
		// while we're at it, check all the update vars are valid too
		// also, store their types for future type checking
		for (i = 0; i < n; i++) {
			j = varIdents.indexOf(getVar(i));
			if (j == -1) {
				s = "Unknown variable \"" + getVar(i) + "\" in update ";
				s += "\"(" + getVar(i) + "'=" + getExpression(i) + ")\"";
				throw new ParserException(s);
			}
			types.addElement(varTypes.elementAt(j));
		}
	}

	// check everything is ok
	
	public void check() throws ParserException
	{
		int i, n;
		Expression e;
		
		n = getNumElements();
		for (i = 0; i < n; i++) {
			e = getExpression(i);
			// check expression
			e.check();
			// check evaluates to correct type
			if (!Expression.canAssignTypes(getType(i), e.getType())) {
				throw new ParserException("Type error in update \"(" + getVar(i) + "'=" + getExpression(i) + ")\"");
			}
		}
	}

	// convert to string
	
	public String toString()
	{
		int i, n;
		String s = "";
		
		n = exprs.size();
		for (i = 0; i < n-1; i++) {
			s = s + "(" + vars.elementAt(i) + "'=" + exprs.elementAt(i) + ") & ";
		}
		s = s + "(" + vars.elementAt(n-1) + "'=" + exprs.elementAt(n-1) + ")";
		
		return s;
	}
}

//------------------------------------------------------------------------------
