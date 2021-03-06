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

public class ExpressionOr extends ExpressionNary
{
	// create and return a new expression by renaming

	public Expression rename(RenamedModule rm) throws ParserException
	{
		int i, n;
		ExpressionOr e;
		
		e = new ExpressionOr();		
		n = getNumOperands();
		for (i = 0; i < n; i++) {
			e.addOperand(getOperand(i).rename(rm));
		}
		
		return e;
	}
		
	// create and return a new expression by expanding constants

	public Expression expandConstants(ConstantList constantList) throws ParserException
	{
		int i, n;
		ExpressionOr e;
		
		e = new ExpressionOr();		
		n = getNumOperands();
		for (i = 0; i < n; i++) {
			e.addOperand(getOperand(i).expandConstants(constantList));
		}
		
		return e;
	}

	// type check
	
	public void typeCheck() throws ParserException
	{
		int i, n;
		
		// make sure that all operands are booleans
		n = getNumOperands();
		for (i = 0; i < n; i++) {
			if (getOperand(i).getType() != Expression.BOOLEAN) {
				throw new ParserException("Type error in expression \"" + toString() + "\"");
			}
		}
		
		// result is always boolean
		setType(Expression.BOOLEAN);
	}

	// evaluate
	
	public Object evaluate(Values constantValues, Values varValues) throws ParserException
	{
		int i, n;
		
		n = getNumOperands();
		for (i = 0; i < n; i++) {
			if (getOperand(i).evaluateBoolean(constantValues, varValues)) {
				return new Boolean(true);
			}
		}
		
		return new Boolean(false);
	}

	// convert to string
	
	public String toString()
	{
		int i, n;
		String s = "";
		
		n = getNumOperands();
		for (i = 0; i < n-1; i++) {
			s = s + getOperand(i) + "|";
		}
		if (n > 0) {
			s = s + getOperand(n-1);
		}
		
		return s;
	}
}

//------------------------------------------------------------------------------
