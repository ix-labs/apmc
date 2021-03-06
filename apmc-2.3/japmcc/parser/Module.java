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

public class Module
{
	private String name;
	private Vector decls;
	private Vector commands;
	private Vector allSynchs;

	// constructor
	
	public Module(String n)
	{
		name = n;
		decls = new Vector();
		commands = new Vector();
		allSynchs = new Vector();
	}

	// set methods
	
	public void setName(String n)
	{
		name = n;
	}
	
	public void addDeclaration(Declaration d)
	{
		decls.addElement(d);
	}
	
	public void addCommand(Command c)
	{
		String s;
		
		commands.addElement(c);
		s = c.getSynch();
		if (!s.equals("")) if (!allSynchs.contains(s)) allSynchs.add(s);
	}

	// get methods
	
	public String getName()
	{
		return name;
	}
	
	public int getNumDeclarations()
	{
		return decls.size();
	}
	
	public int getNumCommands()
	{
		return commands.size();
	}
	
	public Declaration getDeclaration(int i)
	{
		return (Declaration)decls.elementAt(i);
	}
	
	public Command getCommand(int i)
	{
		return (Command)commands.elementAt(i);
	}
	
	public Vector getAllSynchs()
	{
		return allSynchs;
	}
	
	public boolean usesSynch(String s)
	{
		return allSynchs.contains(s);
	}

	// find all formulas (i.e. locate idents which are formulas)
	
	public void findAllFormulas(FormulaList formulaList) throws ParserException
	{
		int i, n;
		
		// go thru var declarations
		n = decls.size();
		for (i = 0; i < n; i++) {
			getDeclaration(i).findAllFormulas(formulaList);
		}
		// go thru commands
		n = commands.size();
		for (i = 0; i < n; i++) {
			getCommand(i).findAllFormulas(formulaList);
		}
	}

	// expand any formulas
	
	public void expandFormulas(FormulaList formulaList) throws ParserException
	{
		int i, n;
		
		// go thru var declarations
		n = decls.size();
		for (i = 0; i < n; i++) {
			getDeclaration(i).expandFormulas(formulaList);
		}
		// go thru commands
		n = commands.size();
		for (i = 0; i < n; i++) {
			getCommand(i).expandFormulas(formulaList);
		}
	}

	// create and return a new Module by renaming

	public Module rename(RenamedModule rm) throws ParserException
	{
		int i, n;
		Module m;
		
		// create new module and name it
		m = new Module(rm.getName());
		// create new declarations
		n = decls.size();
		for (i = 0; i < n; i++) {
			m.addDeclaration(getDeclaration(i).rename(rm));
		}
		// create new commands
		n = commands.size();
		for (i = 0; i < n; i++) {
			m.addCommand(getCommand(i).rename(rm));
		}
		
		return m;
	}

	// find all constants (i.e. locate idents which are constants)
	
	public void findAllConstants(ConstantList constantList) throws ParserException
	{
		int i, n;
		
		// go thru var declarations
		n = decls.size();
		for (i = 0; i < n; i++) {
			getDeclaration(i).findAllConstants(constantList);
		}
		// go thru commands
		n = commands.size();
		for (i = 0; i < n; i++) {
			getCommand(i).findAllConstants(constantList);
		}
	}

	// find all variables (i.e. locate idents which are variables)
	
	public void findAllVars(Vector varIdents, Vector varTypes) throws ParserException
	{
		int i, n;
		
		// go thru var declarations
		n = decls.size();
		for (i = 0; i < n; i++) {
			getDeclaration(i).findAllVars(varIdents, varTypes);
		}
		// go thru commands
		n = commands.size();
		for (i = 0; i < n; i++) {
			getCommand(i).findAllVars(varIdents, varTypes);
		}
	}

	// check everything is ok
	
	public void check() throws ParserException
	{
		int i, n;
		
		// check declarations
		n = decls.size();
		for (i = 0; i < n; i++) {
			getDeclaration(i).check();
		}
		// check commands
		n = commands.size();
		for (i = 0; i < n; i++) {
			getCommand(i).check();
		}
	}

	// convert to string
	
	public String toString()
	{
		String s = "";
		int i;
		
		s = s + "module " + name + "\n\n";
		for (i = 0; i < decls.size(); i++) {
			s = s + "\t" + decls.elementAt(i) + ";\n";
		}
		s = s + "\n";
		for (i = 0; i < commands.size(); i++) {
			s = s + "\t" + commands.elementAt(i) + ";\n";
		}
		s = s + "\nendmodule";
		
		return s;
	}
}

//------------------------------------------------------------------------------
