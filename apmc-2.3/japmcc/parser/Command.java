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

public class Command
{
	String synch;
	Expression guard;
	Updates updates;
	
	// constructor
	
	public Command()
	{
		synch = "";
	}
	
	// set methods
	
	public void setSynch(String s)
	{
		synch = s;
	}
	
	public void setGuard(Expression g)
	{
		guard = g;
	}
	
	public void setUpdates(Updates u)
	{
		updates = u;
	}

	// get methods

	public String getSynch()
	{
		return synch;
	}
	
	public Expression getGuard()
	{
		return guard;
	}
	
	public Updates getUpdates()
	{
		return updates;
	}
	
	// find all formulas (i.e. locate idents which are formulas)
	
	public void findAllFormulas(FormulaList formulaList) throws ParserException
	{
		guard = guard.findAllFormulas(formulaList);
		updates.findAllFormulas(formulaList);
	}
	
	// expand any formulas
	
	public void expandFormulas(FormulaList formulaList) throws ParserException
	{
		guard = guard.expandFormulas(formulaList);
		updates.expandFormulas(formulaList);
	}
	
	// create and return a new Command by renaming

	public Command rename(RenamedModule rm) throws ParserException
	{
		Command c = new Command();
		String s;
		
		// change synch if it has been renamed
		s = rm.getNewName(synch);
		c.setSynch((s == null) ? synch : s);
		// rename guard/updates
		c.setGuard(guard.rename(rm));
		c.setUpdates(updates.rename(rm));
		
		return c;
	}
	
	// find all constants (i.e. locate idents which are constants)
	
	public void findAllConstants(ConstantList constantList) throws ParserException
	{
		guard = guard.findAllConstants(constantList);
		updates.findAllConstants(constantList);
	}
	
	// find all variables (i.e. locate idents which are variables)
	
	public void findAllVars(Vector varIdents, Vector varTypes) throws ParserException
	{
		guard = guard.findAllVars(varIdents, varTypes);
		updates.findAllVars(varIdents, varTypes);
	}

	// check everything is ok
	
	public void check() throws ParserException
	{
		// check guard expression ok
		guard.check();
		// check guard is of type boolean
		if (guard.getType() != Expression.BOOLEAN) {
			throw new ParserException("Guard \"" + guard + "\" is not of type boolean");
		}
		// check updates
		updates.check();
	}

	// convert to string
	
	public String toString()
	{
		return "[" + synch + "] " + guard + " -> " + updates;
	}
}

//------------------------------------------------------------------------------
