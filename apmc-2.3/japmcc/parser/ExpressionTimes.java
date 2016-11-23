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

public class ExpressionTimes extends ExpressionBinary
{
	// create and return a new expression by renaming

	public Expression rename(RenamedModule rm) throws ParserException
	{
		ExpressionTimes e;
		
		e = new ExpressionTimes();		
		e.setOperand1(operand1.rename(rm));
		e.setOperand2(operand2.rename(rm));
		
		return e;
	}
	
	// create and return a new expression by expanding constants

	public Expression expandConstants(ConstantList constantList) throws ParserException
	{
		ExpressionTimes e;
		
		e = new ExpressionTimes();		
		e.setOperand1(operand1.expandConstants(constantList));
		e.setOperand2(operand2.expandConstants(constantList));
		
		return e;
	}

	// type check
	
	public void typeCheck() throws ParserException
	{
		int t1, t2;
		
		t1 = operand1.getType();
		t2 = operand2.getType();
		
		// make sure operands are ints or doubles
		if (t1==Expression.BOOLEAN || t2==Expression.BOOLEAN) {
			throw new ParserException("Type error in expression \"" + toString() + "\"");
		}
		
		// determine type
		if (t1==Expression.DOUBLE || t2==Expression.DOUBLE) {
			setType(Expression.DOUBLE);
		}
		else {
			setType(Expression.INT);
		}
	}

	// evaluate
	
	public Object evaluate(Values constantValues, Values varValues) throws ParserException
	{
		Object o1, o2, res;
		double d;
		
		// evaluate operands
		o1 = operand1.evaluate(constantValues, varValues);
		o2 = operand2.evaluate(constantValues, varValues);
		
		// case where both are ints
		if (o1 instanceof Integer && o2 instanceof Integer) {
			res = new Integer(((Integer)o1).intValue() * ((Integer)o2).intValue());
		}
		// case where at least one is a double
		else {
			if (o1 instanceof Double) {
				d = ((Double)o1).doubleValue();
			}
			else {
				d = ((Integer)o1).intValue();
			}
			if (o2 instanceof Double) {
				d *= ((Double)o2).doubleValue();
			}
			else {
				d *= ((Integer)o2).intValue();
			}
			res = new Double(d);
		}
		
		return res;
	}

	public String toString()
	{
		return operand1 + "*" + operand2;
	}
}

//------------------------------------------------------------------------------
