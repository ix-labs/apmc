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
import java.text.*;



// class to store a list of typed constant/variable values

public class Values
{
	Vector names;
	Vector values;
	
	// constructors
	
	public Values()
	{
		names = new Vector();
		values = new Vector();
	}
	
	// add value (type of value detetmined by type of Object)
	// (note: no checking for duplication/inconsistencies/etc.)
	
	public void addValue(String n, Object o)
	{
		names.addElement(n);
		values.addElement(o);
	}
	
	// add multiple values
	// (note: no checking for duplication/inconsistencies/etc.)
	
	public void addValues(Values v)
	{
		int i, n;
		
		if (v == null) return;
		n = v.getNumValues();
		for (i = 0; i < n; i ++) {
			names.addElement(v.getName(i));
			values.addElement(v.getValue(i));
		}
	}
	
	// set value (overwrite if already present)
	// returns 0 if added, -1 if overwritten
	
	public int setValue(String n, Object o)
	{
		int i = getIndexOf(n);
		if (i == -1) {
			addValue(n, o);
			return 0;
		}
		else {
			values.setElementAt(o, i);
			return -1;
		}
	}
	
	// get methods
	
	public int getNumValues()
	{
		return names.size();
	}
	
	public String getName(int i)
	{
		return (String)names.elementAt(i);
	}

	public int getIndexOf(String n)
	{
		return names.indexOf(n);
	}
	
	public boolean contains(String n)
	{
		return names.contains(n);
	}
	
	public int getType(int i)
	{
		Object o = values.elementAt(i);
		if (o instanceof Integer) return Expression.INT;
		if (o instanceof Double) return Expression.DOUBLE;
		if (o instanceof Boolean) return Expression.BOOLEAN;
		else return 0;
	}

	public Object getValue(int i)
	{
		return values.elementAt(i);
	}

	public int getIntValue(int i) throws ParserException
	{
		Object o;
		
		o = values.elementAt(i);
		
		if (!(o instanceof Integer)) {
			throw new ParserException("Cannot get integer value for \"" + getName(i) + "\"");
		}
		
		return ((Integer)o).intValue();
	}

	public double getDoubleValue(int i) throws ParserException
	{
		Object o;
		
		o = values.elementAt(i);
		
		if (o instanceof Boolean) {
			throw new ParserException("Cannot get double value for \"" + getName(i) + "\"");
		}
		if (o instanceof Integer) {
			return ((Integer)o).intValue();
		}
		if (o instanceof Double) {
			return ((Double)o).doubleValue();
		}
		
		throw new ParserException("Cannot get double value for \"" + getName(i) + "\"");
	}

	public boolean getBooleanValue(int i) throws ParserException
	{
		Object o;
		
		o = values.elementAt(i);
		
		if (!(o instanceof Boolean)) {
			throw new ParserException("Cannot get boolean value for \"" + getName(i) + "\"");
		}
		
		return ((Boolean)o).booleanValue();
	}

	public Object getValueOf(String n) throws ParserException
	{
		int i;
		
		i = getIndexOf(n);
		if (i == -1) throw new ParserException("Couldn't get value for \"" + n + "\"");
		return getValue(i);
	}

	// compare for equality
	
	public boolean equals(Values v)
	{
		int i, j, n;
		Object o;
		String s;

		// trivial case: null arg
		if (v == null) return false;
		// check sizes are equal
		n = getNumValues();
		if (v.getNumValues() != n) return false;
		// check each value
		for (i = 0; i < n; i++) {
			s = getName(i);
			j = v.getIndexOf(s);
			if (j == -1) return false;
			o = v.getValue(j);
			if (!getValue(i).equals(o)) return false;
		}
		return true;
	}

	// to string
	
	public String toString()
	{
		int i, n;
		String s;
		
		n = getNumValues();
		s = "";
		for (i = 0; i < n; i++) {
			s += getName(i) + "=" + valToString(getValue(i));
			if (i < n-1) s += ", ";
		}
		
		return s;
	}
	
	private String valToString(Object o)
	{
		String s;
		
		if (o instanceof Double) {
			NumberFormat nf = new DecimalFormat();
			nf.setMaximumFractionDigits(6);
			s = nf.format(((Double)o).doubleValue());
		} else {
			s = o.toString();
		}
		
		return s;
	}
}

//------------------------------------------------------------------------------
