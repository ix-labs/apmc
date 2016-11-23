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

import parser.*;

import java.util.Vector;

import java.io.PrintStream;

public class ProbabilisticSynchCommand
{
	String synch;
	Expression guard;
	Vector updates;
	
	// constructor
	
	public ProbabilisticSynchCommand(String s)
	{
		synch = s;
		updates = new Vector();
	}
	
	public ProbabilisticSynchCommand(Command c)
	{
		synch = c.getSynch();
		guard = c.getGuard();
		updates = new Vector();
		updates.add( c.getUpdates() );
	}

	public ProbabilisticSynchCommand(ProbabilisticSynchCommand s)
	{
		synch = s.getSynch();
		guard = s.getGuard();
		updates = new Vector();
		Vector ou = s.getUpdates();
		for(int i = 0; i < ou.size(); i++)
			updates.add(ou.elementAt(i));
	}

	// set methods
	
	public void setGuard(Expression g)
	{
		guard = g;
	}
	
	public void setUpdates(Vector u)
	{
		updates = u;
	}

	public void addUpdates(Updates u)
	{
		updates.add(u);
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
	
	public Vector getUpdates()
	{
		return updates;
	}
	
	public ProbabilisticSynchCommand multiply(Command c)
	{
		ProbabilisticSynchCommand s = new ProbabilisticSynchCommand(this);

		ExpressionAnd g = new ExpressionAnd();
		g.addOperand( guard );
		g.addOperand( c.getGuard() );
		s.setGuard(g);
		s.getUpdates().add( c.getUpdates() );
		return s;
	}

	// convert to string
	
	public String toString()
	{
	        String up = new String();
		for(int i = 0; i < updates.size(); i++)
		    up = up + updates.elementAt(i).toString() + " ++ ";
		return "[" + synch + "] " + guard + " -> " + up;
	}
}

//------------------------------------------------------------------------------
