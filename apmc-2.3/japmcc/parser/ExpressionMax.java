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

public class ExpressionMax extends ExpressionNary
{
	// create and return a new expression by renaming

	public Expression rename(RenamedModule rm) throws ParserException
	{
		int i, n;
		ExpressionMax e;
		
		e = new ExpressionMax();		
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
		ExpressionMax e;
		
		e = new ExpressionMax();		
		n = getNumOperands();
		for (i = 0; i < n; i++) {
			e.addOperand(getOperand(i).expandConstants(constantList));
		}
		
		return e;
	}

	// type check
	
	public void typeCheck() throws ParserException
	{
		int i, n, types[];
		
		// compute types of operands
		n = getNumOperands();
		types = new int[n];
		for (i = 0; i < n; i++) {
			types[i] = getOperand(i).getType();
		}
		
		// make sure operands are ints or doubles
		for (i = 0; i < n; i++) {
			if (types[i] == Expression.BOOLEAN) {
				throw new ParserException("Type error in expression \"" + toString() + "\"");
			}
		}
		
		// determine type: int if all ints, double otherwise
		for (i = 0; i < n; i++) {
			if (types[i] == Expression.DOUBLE) {
				setType(Expression.DOUBLE);
				return;
			}
		}
		setType(Expression.INT);
	}

	// evaluate
	
	public Object evaluate(Values constantValues, Values varValues) throws ParserException
	{
		int i, j, n, iMax;
		double d, dMax;
		Object o[];
		boolean allInts;
		
		// evaluate operands
		n = getNumOperands();
		o = new Object[n];
		for (i = 0; i < n; i++) {
			o[i] = getOperand(i).evaluate(constantValues, varValues);
		}
		
		// see if they're all ints
		allInts = true;
		for (i = 0; i < n; i++) {
			if (!(o[i] instanceof Integer)) {
				allInts = false;
			}
		}
				
		// case where all are ints
		if (allInts) {
			iMax = ((Integer)o[0]).intValue();
			n = getNumOperands();
			for (i = 1; i < n; i++) {
				j = ((Integer)o[i]).intValue();
				iMax = (j > iMax) ? j : iMax;
			}
			return new Integer(iMax);
		}
		// case where at least one is a double
		else {
			if (o[0] instanceof Double) {
				dMax = ((Double)o[0]).doubleValue();
			}
			else {
				dMax = ((Integer)o[0]).intValue();
			}
			n = getNumOperands();
			for (i = 1; i < n; i++) {
				if (o[0] instanceof Double) {
					d = ((Double)o[i]).doubleValue();
				}
				else {
					d = ((Integer)o[i]).intValue();
				}
				dMax = (d > dMax) ? d : dMax;
			}
			return new Double(dMax);
		}
	}

	// convert to string
	
	public String toString()
	{
		int i , n;
		String s = "max(";
		
		n = operands.size();
		for (i = 0; i < n-1; i++) {
			s = s + getOperand(i) + ",";
		}
		if (n > 0) {
			s = s + getOperand(n-1);
		}
		s += ")";
		
		return s;
	}
}

//------------------------------------------------------------------------------
