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

public class StochasticSynchCommand
{
	String synch;
	Expression guard;
	Expression prob;
	Vector updates;
	
	// constructor
	
	public StochasticSynchCommand(Command c) throws ParserException
	{
		synch = c.getSynch();
		guard = c.getGuard();
		Updates cu = c.getUpdates();
		if( cu.getNumUpdates() != 1 )
			throw new ParserException("updates should only have one member is Stochastic models");
		prob = cu.getProbability(0);
		updates = new Vector();
		updates.add( cu.getUpdate(0) );
	}

	public StochasticSynchCommand(StochasticSynchCommand s)
	{
		synch = s.getSynch();
		guard = s.getGuard();
		updates = new Vector();
		Vector ou = s.getUpdates();
		for(int i = 0; i < ou.size(); i++)
			updates.add(ou.elementAt(i));
		prob = s.getProbability();
	}

	// set methods
	
	public void setGuard(Expression g)
	{
		guard = g;
	}

	public void setProbability(Expression p)
	{
		prob = p;
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
	
	public Expression getProbability()
	{
		return prob;
	}

	public Vector getUpdates()
	{
		return updates;
	}

	public void addUpdate(Update u)
	{
		updates.add(u);
	}
	
	public StochasticSynchCommand multiply(Command c) throws ParserException
	{
		StochasticSynchCommand s = new StochasticSynchCommand(this);

		ExpressionAnd g = new ExpressionAnd();
		g.addOperand( guard );
		g.addOperand( c.getGuard() );
		s.setGuard(g);

		Updates cu = c.getUpdates();
		if( cu.getNumUpdates() != 1 )
			throw new ParserException("Stochastic models should have only one probability per command");

		ExpressionTimes p = new ExpressionTimes();
		p.setOperand1( cu.getProbability(0) );
		p.setOperand2( prob );
		s.setProbability( p );

		s.addUpdate( cu.getUpdate(0) );
		return s;
	}

	// convert to string
	
	public String toString()
	{
	        String up = new String();
		for(int i = 0; i < updates.size(); i++)
			up = up + " & " + ((Update)(updates.elementAt(i))).toString();
		return "[" + synch + "] " + guard + " -> " + prob.toString() + ":" + up;
	}
}

//------------------------------------------------------------------------------
