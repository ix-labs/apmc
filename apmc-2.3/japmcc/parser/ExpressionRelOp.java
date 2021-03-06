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

public class ExpressionRelOp extends ExpressionBinary
{
	String relOp;
	
	// constructors
	
	public ExpressionRelOp()
	{
	}
	
	public ExpressionRelOp(Expression e1, String r, Expression e2)
	{
		super(e1, e2);
		relOp = r;
	}
	
	// extra set method
	
	public void setRelOp(String r)
	{
		relOp = r;
	}
	
	// extra get method
	
	public String getRelOp()
	{
		return relOp;
	}
			
	// create and return a new expression by renaming

	public Expression rename(RenamedModule rm) throws ParserException
	{
		ExpressionRelOp e;
		
		e = new ExpressionRelOp();		
		e.setRelOp(relOp);
		e.setOperand1(operand1.rename(rm));
		e.setOperand2(operand2.rename(rm));
		
		return e;
	}
	

	// create and return a new expression by expanding constants

	public Expression expandConstants(ConstantList constantList) throws ParserException
	{
		ExpressionRelOp e;
		
		e = new ExpressionRelOp();		
		e.setRelOp(relOp);
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
		
		// if one operand is boolean,
		// both operands must be boolean and rel op must be = or !=
		if (t1==Expression.BOOLEAN) {
			if (t2!=Expression.BOOLEAN || !(relOp.equals("=") || relOp.equals("!="))) {
				throw new ParserException("Type error in expression \"" + toString() + "\"");
			}
		}
		if (t2==Expression.BOOLEAN) {
			if (t1!=Expression.BOOLEAN || !(relOp.equals("=") || relOp.equals("!="))) {
				throw new ParserException("Type error in expression \"" + toString() + "\"");
			}
		}
		
		// type is always boolean
		setType(Expression.BOOLEAN);
	}

	// evaluate
	
	public Object evaluate(Values constantValues, Values varValues) throws ParserException
	{
		Object o1, o2;
		double d1, d2;
		boolean b;
		
		// evaluate operands
		o1 = operand1.evaluate(constantValues, varValues);
		o2 = operand2.evaluate(constantValues, varValues);
		
		// if they're booleans...
		if (o1 instanceof Boolean) {
			b = (((Boolean)o1).booleanValue() == ((Boolean)o2).booleanValue());
		}
		// otherwise they're doubles/ints...
		else {
		
			// convert both to doubles before the comparison
			if (o1 instanceof Double) {
				d1 = ((Double)o1).doubleValue();
			}
			else {
				d1 = ((Integer)o1).intValue();
			}
			if (o2 instanceof Double) {
				d2 = ((Double)o2).doubleValue();
			}
			else {
				d2 = ((Integer)o2).intValue();
			}
			
			// compare
			if (relOp.equals("=")) {
				b = (d1 == d2);
			}
			else if (relOp.equals("!=")) {
				b = (d1 != d2);
			}
			else if (relOp.equals(">")) {
				b = (d1 > d2);
			}
			else if (relOp.equals(">=")) {
				b = (d1 >= d2);
			}
			else if (relOp.equals("<")) {
				b = (d1 < d2);
			}
			else if (relOp.equals("<=")) {
				b = (d1 <= d2);
			}
			else {
				throw new ParserException("Invalid operator in \"" + this + "\"");
			}
		}
		
		return new Boolean(b);
	}

	// convert to string
		
	public String toString()
	{
		return operand1 + relOp + operand2;
	}
}

//------------------------------------------------------------------------------
