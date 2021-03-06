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

public class Updates
{
	Vector probs;
	Vector updates;
	
	public Updates()
	{
		probs = new Vector();
		updates = new Vector();
	}
	
	// add a probability/update pair
	
	public void addUpdate(Expression p, Update u)
	{
		probs.addElement(p);
		updates.addElement(u);
	}

	// set methods

	public void setUpdate(int i, Update u)
	{
		updates.setElementAt(u, i);
	}

	public void setProbability(int i, Expression p)
	{
		probs.setElementAt(p, i);
	}
	
	// get methods
	
	public int getNumUpdates()
	{
		return updates.size();
	}

	public Update getUpdate(int i)
	{
		return (Update)updates.elementAt(i);
	}

	public Expression getProbability(int i)
	{
		return (Expression)probs.elementAt(i);
	}
	
	// find all formulas (i.e. locate idents which are formulas)
	
	public void findAllFormulas(FormulaList formulaList) throws ParserException
	{
		int i, n;
		
		n = getNumUpdates();
		for (i = 0; i < n; i++)  {
			setProbability(i, getProbability(i).findAllFormulas(formulaList));
			getUpdate(i).findAllFormulas(formulaList);
		}
	}
	
	// expand any formulas
		
	public void expandFormulas(FormulaList formulaList) throws ParserException
	{
		int i, n;
		
		n = getNumUpdates();
		for (i = 0; i < n; i++)  {
			setProbability(i, getProbability(i).expandFormulas(formulaList));
			getUpdate(i).expandFormulas(formulaList);
		}
	}
	
	// create and return a new Updates by renaming

	public Updates rename(RenamedModule rm) throws ParserException
	{
		int i, n;
		String s;
		Updates u;
		Object o;
		
		// create a new Updates object
		u = new Updates();
		// go thru all updates, rename them and
		// add them to the new Updates
		n = getNumUpdates();
		for (i = 0; i < n; i++)  {
			u.addUpdate(getProbability(i).rename(rm), getUpdate(i).rename(rm));
		}
		
		return u;
	}

	// find all constants (i.e. locate idents which are constants)
	
	public void findAllConstants(ConstantList constantList) throws ParserException
	{
		int i, n;
		
		n = getNumUpdates();
		for (i = 0; i < n; i++)  {
			setProbability(i, getProbability(i).findAllConstants(constantList));
			getUpdate(i).findAllConstants(constantList);
		}
	}
	
	// find all variables (i.e. locate idents which are variables)
	
	public void findAllVars(Vector varIdents, Vector varTypes) throws ParserException
	{
		int i, n;
		
		n = getNumUpdates();
		for (i = 0; i < n; i++)  {
			setProbability(i, getProbability(i).findAllVars(varIdents, varTypes));
			getUpdate(i).findAllVars(varIdents, varTypes);
		}
	}
		
	// check everything is ok
	
	public void check() throws ParserException
	{
		int i, n;
		Expression e;
		
		// go thru updates
		n = getNumUpdates();
		for (i = 0; i < n; i++) {
			e = getProbability(i);
			// check probability/rate expression is ok
			e.check();
			// check probability/rate type is int/double
			if (e.getType() == Expression.BOOLEAN) {
				throw new ParserException("Probability/rate \"" + e + "\" cannot be of type boolean");
			}
			// check update
			getUpdate(i).check();
		}
	}

	// convert to string
	
	public String toString()
	{
		String s = "";
		int i, n;
		
		n = updates.size();
		for (i = 0; i < n-1; i++) {
			s += probs.elementAt(i) + " : " + updates.elementAt(i) + " + ";
		}
		s += probs.elementAt(n-1) + " : ";
		s += updates.elementAt(n-1);
		
		return s;
	}
}

//------------------------------------------------------------------------------
