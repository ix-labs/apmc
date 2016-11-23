import parser.*;
import java.util.Vector;
import java.io.PrintStream;

public class ProbabilisticModulesCompiler extends ModulesCompiler {

	public ProbabilisticModulesCompiler(ModulesFile _mf, PropertiesFile _pf, PrintStream _output)
	{
		super(_mf, _pf, _output, new ProbabilisticFormulaDumper(_output));
		d.setSource("current");
	}

	public void compileVariables() throws ParserException
	{
		output.println("/* configuration and path definition */");
		output.println( "typedef struct conf {");
		compAllVariablesDeclaration("  ");
		output.println( "} conf;\n" +
				"static conf *current;\n");

		output.println( "typedef struct path {\n" +
				"  struct path *next;\n");
		compPropertiesVariablesDeclaration("  ");
		output.println( "} path;\n\n" +
				"static path *first_path, *current_path;\n\n" +
				"static void init_state()\n"+
				"{\n" +
				"  if(current == NULL) current = new(conf);\n" +
				"  if(first_path == NULL) first_path = new(path);\n" +
				"  current_path = first_path;\n");
		compAllVariablesInitialization("  " , "current");
		compPropertiesVariablesIntialization("  ", "first_path", "current");
		output.println( "}\n\n"+
				"static void append_state()\n"+
				"{\n" +
				"  path *n;\n" +
				"  if( current_path->next )\n" +
				"    n = current_path->next;\n" +
				"  else\n" +
				"    n = new(path);");
		compPropertiesVariablesIntialization("  ", "n", "current");
		output.println( "  current_path->next = n;\n" +
				"  current_path = n;\n" +
				"}\n");
	}

	private void compileUpdates(Updates u)
	{
		output.println("  __rv = probability();\n  __rv_min = 0.0;\n  __rv_max = 0.0;");
		for(int i = 0; i < u.getNumUpdates(); i++)
		{
			output.println( "  __rv_max += " + d.dumpExpression(u.getProbability(i)) + ";\n" +
					"  if( (__rv >= __rv_min) && (__rv < __rv_max) )\n" +
					"    {\n" +
					d.dumpUpdate(u.getUpdate(i), "      ") +
					"    }\n" +
					"  __rv_min = __rv_max;");
		}
	}

	private Vector getCommandsWithoutSynch()
	{
		Vector res = new Vector();
		for(int mi = 0; mi < mf.getNumModules(); mi++)
		{
			Module m = mf.getModule(mi);
			for(int ci = 0; ci < m.getNumCommands(); ci++)
			{
				Command c = m.getCommand(ci);
				if( c.getSynch().equals("") )
					res.add(c);
			}
		}
		return res;
	}

	// Returns all the modules using this synch

	private Vector getModulesWithSynch(String synch)
	{
		Vector res = new Vector();
		for(int mi = 0; mi < mf.getNumModules(); mi++)
		{
			Module m = mf.getModule(mi);
			if( m.usesSynch(synch) )
				res.add(m);
		}
		return res;
	}

	private Vector multiplySynch(Module m, Vector cm, String synch)
	{
		Vector res = new Vector();
		if( cm.size() == 0 )
		{
			for(int i = 0; i < m.getNumCommands(); i++)
			{
				Command c = m.getCommand(i);
				if( c.getSynch().equals(synch) )
					res.add( new ProbabilisticSynchCommand(c) );
			}
			return res;
		}

		for(int i = 0; i < m.getNumCommands(); i++)
		{
			Command c = m.getCommand(i);

			if( c.getSynch().equals(synch) )
			{
				for(int j = 0; j < cm.size(); j++)
				{
					ProbabilisticSynchCommand c2 = (ProbabilisticSynchCommand)(cm.elementAt(j));
					res.add( c2.multiply(c) );
				}
			}
		}
		return res;
	}

	private Vector getCommandsWithSynch(String synch)
	{
		Vector synchCommands = new Vector();
		Vector modules = getModulesWithSynch(synch);
		for(int i = 0; i < modules.size(); i++)
		{
			Module m = (Module)(modules.elementAt(i));
			synchCommands = multiplySynch(m, synchCommands, synch);
		}
		return synchCommands;
	}

	public void compileRules() throws ParserException
	{
		Vector guards = new Vector();
		Vector actions = new Vector();

		output.println("typedef void (*action_t)(void);\n" +
			       "typedef int  (*guard_t)(void);\n" +
			       "\n" +
			       "struct rule {\n" +
			       "  guard_t guard;\n" +
			       "  action_t action;\n" +
			       "};\n");

		Vector commands = getCommandsWithoutSynch();
		for(int i = 0; i < commands.size(); i++)
		{
			Command c = (Command)(commands.elementAt(i));
			Expression g = c.getGuard();

			String gname = new String();
			gname = "__g" + guards.size();
			output.print(   "static int " + gname + "(void)\n"+
					"{\n"+
					"  return " + d.dumpExpression(g) + ";\n" +
					"}\n");
			guards.add( gname );

			Updates u = c.getUpdates();

			String aname = new String();
			aname = "__a" + actions.size();
			output.println("static void " + aname + "(void)\n{\n  double __rv, __rv_min, __rv_max;\n");
			compileUpdates(u);
			output.println("\n}\n");
			actions.add( aname );
		}

		Vector synchs = mf.getSynchs();
		for(int i = 0; i < synchs.size(); i++)
		{
			Vector synchCommands = getCommandsWithSynch( (String)(synchs.elementAt(i)) );

			for(int j = 0; j < synchCommands.size(); j++)
			{
				ProbabilisticSynchCommand synchCommand = (ProbabilisticSynchCommand)(synchCommands.elementAt(j));

				Expression g = synchCommand.getGuard();
				String gname = new String();
				gname = "__g" + guards.size();
				output.print(   "static int " + gname + "(void)\n" +
						"{\n" +
						"  return " + d.dumpExpression(g) + ";\n" +
						"}\n");
				guards.add( gname );
	
				Vector vu = synchCommand.getUpdates();
				String aname = new String();
				aname = "__a" + actions.size();
				output.println("static void " + aname + "(void)\n{\n  double __rv, __rv_min, __rv_max;\n");
				for(int vi = 0; vi < vu.size(); vi++)
					compileUpdates( (Updates)(vu.elementAt(vi)) );
				output.println("\n}\n");
				actions.add( aname );
			}
		}

		output.println("#define NBRULES " + actions.size() );
		output.println("static struct rule rules[" + actions.size() + "] = {");
		for(int i = 0; i < actions.size()-1; i++)
			output.println("  { " + guards.elementAt(i) + ", " + actions.elementAt(i) + " },");
		output.println("  { " + guards.elementAt(actions.size()-1) + ", " + actions.elementAt(actions.size()-1) + " }");
		output.println("};\n");
	}

	public void compileProperties() throws ParserException
	{
		output.println( "typedef int (*tester_t)(const path *);\n" +
				"\n" +
				"static int until(tester_t __left, tester_t __right, const path *__p)\n" +
				"{\n" +
				"  int __cond;\n" +
				"\n" +
				"  if(!__p) return 0;\n" +
				"\n" +
				"  __cond = __right(__p);\n" +
				"  if (__cond)\n" +
				"    return 1;\n" +
				"  __cond = __left(__p);\n" +
				"  if (!__cond)\n" +
				"    return 0;\n" +
				"  if(!__p->next)\n" +
				"    return 0;\n" +
				"  return until(__left, __right, __p->next);\n" +
				"}\n" +
				"\n" +
				"static int bounded_until(tester_t __left, int __lower, int __upper, tester_t __right, const path *__p)\n" +
				"{\n" +
				"  int __cond;\n" +
				"\n" +
				"  if(!__p) return 0;\n" +
				"\n" +
				"  if( __lower <= 0 )\n" +
				"    {\n" +
				"      if( __upper > 0 )\n" +
				"	{\n" +
				"	  __cond = __right(__p);\n" +
				"	  if (__cond)\n" +
				"	    return 1;\n" +
				"	  __cond = __left(__p);\n" +
				"	  if (!__cond)\n" +
				"	    return 0;\n" +
				"	  if(!__p->next)\n" +
				"	    return 0;\n" +
				"	  return bounded_until(__left, 0, __upper-1, __right, __p->next);\n" +
				"	}\n" +
				"      return 0;\n" +
				"    }\n" +
				"  __cond = __left(__p);\n" +
				"  if( __cond )\n" +
				"    return bounded_until(__left, __lower-1, __upper-1, __right, __p->next);\n" +
				"  return 0;\n" +
				"}\n" +
			       "\n" +
			       "static int next(tester_t __w, const path *__p)\n" +
			       "{\n" +
			       "  if(!__p) return 0;\n" +
			       "  if(!__p->next) return 0;\n" +
			       "  return __w(__p->next);\n" +
			       "}\n");

		d.setSource("__p");
		d.setPrototype("(const path *__p)");

		for(int i = 0; i < pf.getNumProperties(); i++)
		{
			try {
				output.print("static int verify_path_" + i + "(const path *__p)\n{\n" + 
					     "  return " + d.dumpPCTL(pf.getProperty(i)) + ";\n" +
					     "}\n");
			} catch (ParserException e) {
				System.err.println("Unable to dump goal " + i + ":" + e);
				output.print("static int verify_path_" + i + "(const path *__p) { return 0; }\n");
				continue;
			}
		}
		output.println("#define NB_VERIF_GOAL " + pf.getNumProperties());
		output.println("typedef int (*verifier_func_t)(const path *__p);");
		output.println("verifier_func_t VERIF_GOAL[] = {");
		for(int i = 0; i < pf.getNumProperties()-1; i++)
			output.println("  verify_path_" + i + ",");
		output.println("  verify_path_" + (pf.getNumProperties()-1) + "\n};\n");
	}

}
