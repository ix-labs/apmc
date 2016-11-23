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



public class PCTLLabel extends PCTLFormula
{
	String name;

	// constructor
	
	public PCTLLabel(String s)
	{
		name = s;
	}

	// accessor
	
	public String getName()
	{
		return name;
	}

	// check all labels (make sure the referred labels exist)
	
	public void checkLabelIdents(LabelList labelList) throws ParserException
	{
		if (labelList.getLabelIndex(name) == -1) {
			throw new ParserException("Undeclared label \"" + name + "\"");
		}
	}

	// find all constants (i.e. locate idents which are constants)
	
	public PCTLFormula findAllConstants(ConstantList constantList) throws ParserException
	{
		return this;
	}

	// find all variables (i.e. locate idents which are variables)
	
	public PCTLFormula findAllVars(Vector varIdents, Vector varTypes) throws ParserException
	{
		return this;
	}

	// type check
	
	public void typeCheck() throws ParserException
	{
		// set type
		setType(Expression.BOOLEAN);
	}

	// convert to string
	
	public String toString()
	{
		return "\"" + name + "\"";
	}
}

//------------------------------------------------------------------------------
