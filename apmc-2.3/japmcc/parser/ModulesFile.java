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

// class to store representation of parsed modules file

public class ModulesFile
{
	// constants for types of system
	public static final int PROBABILISTIC = 1;
	public static final int NONDETERMINISTIC = 2;
	public static final int STOCHASTIC = 3;
	public static final String typeStrings[] = {"?", "Probabilistic (DTMC)", "Nondeterministic (MDP)", "Stochastic (CTMC)"};
	
	// formulas (macros)
	private FormulaList formulaList;
	
	// constants
	private ConstantList constantList;

	// basic components
	private int type;				// type: prob/nondet/stoch
	private Vector globals;			// global variables
	private Vector modules;			// modules (includes renamed modules)
	private SystemDefn systemDefn;	// system definition (process algebraic)
	
	// identifiers/etc.
	private Vector allIdentsUsed;
	private String[] moduleNames;
	private Vector synchs;
	private Vector varNames;
	private Vector varTypes;
	
	// actual values of constants
	private Values constantValues;
	
	// constructor
	
	public ModulesFile()
	{
		// initialise
		formulaList = new FormulaList(); // empty - will be overwritten
		constantList = new ConstantList(); // empty - will be overwritten
		type = NONDETERMINISTIC; // default type
		globals = new Vector();
		modules = new Vector();
		systemDefn = null;
		allIdentsUsed = new Vector();
		varNames = new Vector();
		varTypes = new Vector();
		constantValues = null;
	}
	
	// set up methods - these are called by the parser to create a ModulesFile object
	
	public void setFormulaList(FormulaList fl) { formulaList = fl; }
	
	public void setConstantList(ConstantList cl) { constantList = cl; }
	
	public void setType(int t) { type = t; }
	
	public void addGlobal(Declaration d) { globals.addElement(d); }
	
	public void addModule(Module m) { modules.addElement(m); }
	
	public void addRenamedModule(RenamedModule m) { modules.addElement(m); }
	
	public void setSystemDefn(SystemDefn s) { systemDefn = s; }
	
	// accessor methods

	public FormulaList getFormulaList() { return formulaList; }
	
	public ConstantList getConstantList() { return constantList; }
	
	public int getType() { return type; }
	
	public String getTypeString() { return typeStrings[type]; }
	
	public int getNumGlobals() { return globals.size(); }
	
	public Declaration getGlobal(int i) { return (Declaration)globals.elementAt(i); }
	
	public int getNumModules() { return modules.size(); }
	
	// get module by index
	// returns null if it is a RenamedModule
	// these will have been replaced with Modules after tidyUp()
	public Module getModule(int i)
	{
		Object o = modules.elementAt(i);
		return (o instanceof Module) ? (Module)o : null;
	}
	
	// get the index of a module by its name
	// (returns -1 if it does not exist)
	// (or is a RenamedModule and hasn't been turned into a normal Module yet)
	public int getModuleIndex(String s)
	{
		int i;
		
		for (i = 0; i < modules.size(); i++) {
			if (s.equals(getModule(i).getName())) {
				return i;
			}
		}
		
		return -1;
	}
	
	public SystemDefn getSystemDefn() { return systemDefn; }
	
	public Vector getAllIdentsUsed() { return allIdentsUsed; }
	
	// get individual module name
	public String getModuleName(int i) { return moduleNames[i]; }
	
	// get array of all module names
	public String[] getModuleNames() { return moduleNames; }
	
	public Vector getSynchs() { return synchs; }
	
	public Vector getVarNames() { return varNames; }
	
	public Vector getVarTypes() { return varTypes; }
	
	// method to tidy up
	// (called after parsing to do some checks and extract some information)
	
	public void tidyUp() throws ParserException
	{
		// check formula identifiers
		checkFormulaIdents();
		// find all instances of formulas
		// (i.e. locate idents which are formulas)
		// (n.b. can't determine other idents such as vars at the same time
		//       because this relies on module renaming which in turn
		//       must be done after formulas have been expanded
		findAllFormulas();
		// check formulas for cyclic dependencies
		formulaList.findCycles();
		// expand any formulas
		expandFormulas();
		
		// sort out any modules defined by renaming
		sortRenamings();
		
		// check module names
		checkModuleNames();
		
		// get synch names
		getSynchNames();
		// check system definition
		checkSystemDefn();
		
		// check constant identifiers
		checkConstantIdents();
		// find all instances of constants
		// (i.e. locate idents which are constants)
		findAllConstants();
		// check constants for cyclic dependencies
		constantList.findCycles();
		
		// check variable names
		checkVarNames();
		// find all instances of variables
		// (i.e. locate idents which are variables)
		findAllVars();
		
		// check everything is ok
		// (including type checking)
		check();
	}
	
	// check formula identifiers
	
	private void checkFormulaIdents() throws ParserException
	{
		int i, n;
		String s;

		n = formulaList.size();
		for (i = 0; i < n; i++) {
			s = formulaList.getFormulaName(i);
			if (allIdentsUsed.contains(s)) {
				throw new ParserException("Duplicated identifier \"" + s + "\"");
			}
			else {
				allIdentsUsed.addElement(s);
			}
		}
	}

	// find all formulas (i.e. locate idents which are formulas)
	
	private void findAllFormulas() throws ParserException
	{
		int i, n;
		Module module;
		
		// look in formula list
		formulaList.findAllFormulas();
		// look in constants
		constantList.findAllFormulas(formulaList);
		// look in globals
		n = globals.size();
		for (i = 0; i < n; i++) {
			getGlobal(i).findAllFormulas(formulaList);
		}
		// look in (non-renamed) modules
		n = modules.size();
		for (i = 0; i < n; i++) {
			module = getModule(i);
			if (module != null) {
				module.findAllFormulas(formulaList);
			}
		}
	}

	// expand any formulas
	
	private void expandFormulas() throws ParserException
	{
		int i, n;
		Module module;
		
		// look in formula list
		// (best to do this first - sorts out any linked formulas)
		formulaList.expandFormulas();
		// look in constants
		constantList.expandFormulas(formulaList);
		// look in globals
		n = globals.size();
		for (i = 0; i < n; i++) {
			getGlobal(i).expandFormulas(formulaList);
		}
		// look in (non-renamed) modules
		n = modules.size();
		for (i = 0; i < n; i++) {
			module = getModule(i);
			if (module != null) {
				module.expandFormulas(formulaList);
			}
		}
	}
		
	// sort out modules defined by renaming
	
	private void sortRenamings() throws ParserException
	{
		int i, j, n;
		RenamedModule module;
		Module baseModule;
		String s;
		Object o;
		
		// go thru modules and find ones which are defined by renaming
		n = modules.size();
		for (i = 0; i < n; i++) {
			o = modules.elementAt(i);
			if (o instanceof Module) continue;
			module = (RenamedModule)o;
			// check base module exists
			j = getModuleIndex(module.getBaseModule());
			if (j == -1) {
				s = "No such module " + module.getBaseModule();
				s += " in rename \"" + module.getName() + " = ...\"";
				throw new ParserException(s);
			}
			baseModule = getModule(j);
			// then do renaming and replace with new module
			modules.setElementAt(baseModule.rename(module), i);
		}
	}
	
	// check module names
	
	private void checkModuleNames() throws ParserException
	{
		int i, j, n;
		String s;
		
		// check we have at least one module
		n = modules.size();
		if (n == 0) {
			throw new ParserException("There must be at least one module");
		}
		
		// compile list of all module names
		// and check as we go through
		moduleNames = new String[n];
		for (i = 0; i < n; i++) {
			s = getModule(i).getName();
			for (j = 0; j < i; j++) {
				if (s.equals(moduleNames[j])) {
					throw new ParserException("Duplicated module name \"" + s + "\"");
				}
			}
			moduleNames[i] = s;
		}
	}

	// get all synch names
	
	private void getSynchNames() throws ParserException
	{
		Vector v;
		String s;
		int i, j, n, m;
		
		// create vector to store names
		synchs = new Vector();
		
		// go thru modules and extract names which appear in their commands
		n = modules.size();
		for (i = 0; i < n; i++) {
			v = getModule(i).getAllSynchs();
			m = v.size();
			for (j = 0; j < m; j++) {
				s = (String)v.elementAt(j);
				if (!synchs.contains(s)) {
					synchs.addElement(s);
				}
			}
		}
		
		// then extract any which are introduced in system construct (i.e. by renaming)
		if (systemDefn != null) {
			systemDefn.getSynchs(synchs);
		}
	}

	// check system definition (if present)
	
	private void checkSystemDefn() throws ParserException
	{
		int i, n;
		Vector v;
		
		if (systemDefn != null) {
		
			// check that all modules appear exactly once
			systemDefn.getModules(v = new Vector());
			if (v.size() != modules.size()) {
				throw new ParserException("All modules must appear in the \"system\" construct exactly once");
			}
			n = modules.size();
			for (i = 0; i < n; i++) {
				if (!(v.contains(getModule(i).getName()))) {
					throw new ParserException("All modules must appear in the \"system\" construct exactly once");
				}
			}
			
			// do dome other checks (recursively)
			// nb: need to pass in set of synchronising action names
			systemDefn.check(synchs);
		}
	}

	// check constant identifiers
	
	private void checkConstantIdents() throws ParserException
	{
		int i, n;
		String s;
		
		n = constantList.size();
		for (i = 0; i < n; i++) {
			s = constantList.getConstantName(i);
			if (allIdentsUsed.contains(s)) {
				throw new ParserException("Duplicated identifier \"" + s + "\"");
			}
			else {
				allIdentsUsed.addElement(s);
			}
		}
	}

	// find all constants (i.e. locate idents which are constants)
	
	private void findAllConstants() throws ParserException
	{
		int i, n;
		
		// look in constants
		constantList.findAllConstants(constantList);
		// look in globals
		n = globals.size();
		for (i = 0; i < n; i++) {
			getGlobal(i).findAllConstants(constantList);
		}
		// look in modules
		n = modules.size();
		for (i = 0; i < n; i++) {
			getModule(i).findAllConstants(constantList);
		}
	}
		
	// check variable names
	
	private void checkVarNames() throws ParserException
	{
		int i, j, n, m;
		Module module;
		String s;
		
		// compile list of all var names
		// and check as we go through
		
		// globals
		n = globals.size();
		for (i = 0; i < n; i++) {
			s = getGlobal(i).getName();
			if (allIdentsUsed.contains(s)) {
				throw new ParserException("Duplicated identifier \"" + s + "\"");
			}
			else {
				allIdentsUsed.addElement(s);
				varNames.addElement(s);
				varTypes.addElement(new Integer(getGlobal(i).getType()));
			}
		}
		
		// locals
		n = modules.size();
		for (i = 0; i < n; i++) {
			module = getModule(i);
			m = module.getNumDeclarations();
			for (j = 0; j < m; j++) {
				s = module.getDeclaration(j).getName();
				if (allIdentsUsed.contains(s)) {
					throw new ParserException("Duplicated identifier \"" + s + "\"");
				}
				else {
					allIdentsUsed.addElement(s);
					varNames.addElement(s);
					varTypes.addElement(new Integer(module.getDeclaration(j).getType()));
				}
			}
		}
		
		// check there is at least one variable
		if (varNames.size() == 0) {
			throw new ParserException("There must be at least one variable");
		}
	}

	// find all variables (i.e. locate idents which are variables)
	
	private void findAllVars() throws ParserException
	{
		int i, n;
		
		// nb: we even check in places where there shouldn't be vars
		//     eg. in constant definitions etc.
		
		// look in constants
		constantList.findAllVars(varNames, varTypes);
		// look in globals
		n = globals.size();
		for (i = 0; i < n; i++) {
			getGlobal(i).findAllVars(varNames, varTypes);
		}
		// look in modules
		n = modules.size();
		for (i = 0; i < n; i++) {
			getModule(i).findAllVars(varNames, varTypes);
		}
	}
		
	// check everything is ok
	// (includes type checking)
	
	private void check() throws ParserException
	{
		int i, n;
		Vector v;
		
		// check constants
		constantList.check();
		// check globals
		n = globals.size();
		for (i = 0; i < n; i++) {
			getGlobal(i).check();
		}
		// check modules
		n = modules.size();
		for (i = 0; i < n; i++) {
			getModule(i).check();
		}
	}
	
	// get undefined constants
	
	public Vector getUndefinedConstants()
	{
		return constantList.getUndefinedConstants();
	}
	
	// set values for undefined constants and evaluate all constants
	// always need to call this, even when there are no undefined constants
	// (if this is the case, someValues can be null)
	
	public void setUndefinedConstants(Values someValues) throws ParserException
	{
		constantValues = constantList.evaluateConstants(someValues, null);
	}

	// get all constant values
	
	public Values getConstantValues()
	{
		return constantValues;
	}
	
	// extract information about all variables and return in a VarList object
	
	public VarList createVarList() throws ParserException
	{
		int i, j, n, n2, low, high, start;
		String name;
		Module module;
		Declaration decl;
		VarList varList;
		
		// set up variable list
		varList = new VarList();
		
		// first add all globals to the list
		n = getNumGlobals();
		for (i = 0; i < n; i++) {
			decl = getGlobal(i);
			name = decl.getName();
			// check it is not a duplicate
			if (varList.exists(name)) {
				String s = "Duplicated variable " + name;
				throw new ParserException(s);
			}
			// variable is integer
			if (decl.getType() == Expression.INT) {
				low = decl.getLow().evaluateInt(constantValues, null);
				high = decl.getHigh().evaluateInt(constantValues, null);
				start = decl.getStart().evaluateInt(constantValues, null);
			}
			// variable is boolean
			else {
				low = 0;
				high = 1;
				start = (decl.getStart().evaluateBoolean(constantValues, null)) ? 1 : 0;
			}
			// check range is valid
			if (high - low <= 0) {
				String s = "Invalid range for variable " + name;
				throw new ParserException(s);
			}
			varList.addVar(name, low, high, start, -1);
		}
		
		// then add all module variables to the list
		n = getNumModules();
		for (i = 0; i < n; i++) {
			module = getModule(i);
			n2 = module.getNumDeclarations();
			for (j = 0; j < n2; j++) {
				decl = module.getDeclaration(j);
				name = decl.getName();
				// check it is not a duplicate
				if (varList.exists(name)) {
					String s = "Duplicated variable " + name;
					throw new ParserException(s);
				}
				// variable is integer
				if (decl.getType() == Expression.INT) {
					low = decl.getLow().evaluateInt(constantValues, null);
					high = decl.getHigh().evaluateInt(constantValues, null);
					start = decl.getStart().evaluateInt(constantValues, null);
				}
				// variable is boolean
				else {
					low = 0;
					high = 1;
					start = (decl.getStart().evaluateBoolean(constantValues, null)) ? 1 : 0;
				}
				// check range is valid
				if (high - low <= 0) {
					String s = "Invalid range for variable " + name;
					throw new ParserException(s);
				}
				varList.addVar(name, low, high, start, i);
			}
		}
		
		return varList;
	}

	// convert to string
	
	public String toString()
	{
		String s = "", tmp;
		int i, n;
		
		tmp = "" + formulaList;
		if (tmp.length() > 0) tmp += "\n";
		s += tmp;
		
		tmp = "" + constantList;
		if (tmp.length() > 0) tmp += "\n";
		s += tmp;
		
		n = globals.size();
		for (i = 0; i < n; i++) {
			s += "global " + globals.elementAt(i) + "\n";
		}
		if (n > 0) {
			s += "\n";
		}
		
		for (i = 0; i < modules.size()-1; i++) {
			s += modules.elementAt(i) + "\n\n";
		}
		s += modules.elementAt(modules.size()-1) + "\n";
		
		if (systemDefn != null) {
			s += "\nsystem " + systemDefn + " endsystem\n";
		}
		
		return s;
	}
}

//------------------------------------------------------------------------------
