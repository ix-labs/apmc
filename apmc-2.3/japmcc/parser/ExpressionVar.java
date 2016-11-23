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

public class ExpressionVar extends Expression
{
	String name;
	
	// constructors
	
	public ExpressionVar()
	{
	}
	
	public ExpressionVar(String n, int t)
	{
		setType(t);
		name = n;
	}
			
	// set method
	
	public void setName(String n) 
	{
		name = n;
	}
	
	// get method
	
	public String getName()
	{
		return name;
	}
		
	// find all formulas (i.e. locate idents which are formulas)
	
	public Expression findAllFormulas(FormulaList formulaList) throws ParserException
	{
		// n/a
		return this;
	}
	
	// get all formulas (put into vector)
	
	public void getAllFormulas(Vector v) throws ParserException
	{
		// n/a
		return;
	}

	// expand any formulas
	
	public Expression expandFormulas(FormulaList formulaList) throws ParserException
	{
		// n/a
		return this;
	}
	
	// create and return a new expression by renaming

	public Expression rename(RenamedModule rm) throws ParserException
	{
		// these aren't created until after renaming so this should never be called
		// but just in case...

		return new ExpressionVar(name, type);
	}
		
	// find all constants (i.e. locate idents which are constants)
	
	public Expression findAllConstants(ConstantList constantList) throws ParserException
	{
		// n/a
		return this;
	}

	// get all constants (put into vector)
	
	public void getAllConstants(Vector v) throws ParserException
	{
		// n/a
	}

	// create and return a new expression by expanding constants

	public Expression expandConstants(ConstantList constantList) throws ParserException
	{
		return new ExpressionVar(name, type);
	}

	// find all variables (i.e. locate idents which are variables)
	
	public Expression findAllVars(Vector varIdents, Vector varTypes) throws ParserException
	{
		// n/a: ExpressionVar objects are never created until _after_ the findAllVars phase
		return this;
	}
	
	// get all vars (put into vector)
	
	public void getAllVars(Vector v) throws ParserException
	{
		if (!v.contains(name)) {
			v.addElement(name);
		}
	}

	// type check
	
	public void typeCheck() throws ParserException
	{
		// never any probs
		return;
	}

	// is expression constant?
	
	public boolean isConstant()
	{
		return false;
	}
	
	// check expression is ok
	
	public void check() throws ParserException
	{
		// it's ok
		return;
	}
	
	// evaluate
	
	public Object evaluate(Values constantValues, Values varValues) throws ParserException
	{
		int i;
		
		if (varValues == null) {
			throw new ParserException("Could not evaluate variable \"" + name +  "\"");
		}
		
		i = varValues.getIndexOf(name);
		if (i == -1) {
			throw new ParserException("Could not evaluate variable \"" + name +  "\"");
		}
		
		return varValues.getValue(i);
	}

	// convert to string
	
	public String toString()
	{
		return name;
	}
}

//------------------------------------------------------------------------------
