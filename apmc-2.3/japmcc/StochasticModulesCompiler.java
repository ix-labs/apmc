import parser.*;
import java.util.Vector;
import java.io.PrintStream;

public class StochasticModulesCompiler extends ModulesCompiler {

	public StochasticModulesCompiler(ModulesFile _mf, PropertiesFile _pf, PrintStream out)
	{
		super(_mf, _pf, out, new StochasticFormulaDumper(out));
		d.setSource("current");
	}

	public void compileVariables() throws ParserException
	{
		output.println("/* configuration and path definition */");
		output.println( "typedef struct conf {\n" +
				"  double TIME;\n");
		compAllVariablesDeclaration("  ");
		output.println( "} conf;\n" +
				"static conf *current;\n");

		output.println( "typedef struct path {\n" +
				"  struct path *next;\n" + 
				"  double TIME;\n");
		compPropertiesVariablesDeclaration("  ");
		output.println( "} path;\n\n" +
				"static path *first_path, *current_path;\n\n" +
				"static void init_state()\n"+
				"{\n"+
				"  if(current == NULL) current = new(conf);\n" +
				"  if(first_path == NULL) first_path = new(path);\n" +
				"  current_path = first_path;\n");
		compAllVariablesInitialization("  ", "current");
		compPropertiesVariablesIntialization("  ", "first_path", "current");
		output.println( "}\n\n"+
				"static void append_state()\n"+
				"{\n" +
				"  path *n;\n" +
				"  if( current_path->next )\n" +
				"    n = current_path->next;\n" +
				"  else\n" +
				"    n = new(path);\n" +
				"  n->TIME = current->TIME;\n");
		compPropertiesVariablesIntialization("  ", "n", "current");
		output.println( "  current_path->next = n;\n" +
				"  current_path = n;\n" +
				"}\n");
	}

	private void compileUpdates(Updates u)
	{
		for(int i = 0; i < u.getNumUpdates(); i++)
		{
			output.println( "  __rv = probability();\n"+
					"  current->TIME -= (1.0/" + d.dumpExpression( u.getProbability(i) ) + ") * logl(__rv);\n" +
					"  " + d.dumpUpdate(u.getUpdate(i), "  ") );
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

	private Vector multiplySynch(Module m, Vector cm, String synch) throws ParserException
	{
		Vector res = new Vector();

		if( cm.size() == 0 )
		{
			for(int i = 0; i < m.getNumCommands(); i++)
			{
				Command c = m.getCommand(i);
				if( c.getSynch().equals(synch) )
					res.add( new StochasticSynchCommand(c) );
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
					StochasticSynchCommand c2 = (StochasticSynchCommand)(cm.elementAt(j));
					res.add( c2.multiply(c) );
				}
			}
		}
		return res;
	}

	private Vector getCommandsWithSynch(String synch) throws ParserException
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
			output.println( "static int " + gname + "(void)\n" +
					"{\n"+
					"  return " + d.dumpExpression(g) + ";\n" +
					"}");
			guards.add( gname );

			Updates u = c.getUpdates();

			String aname = new String();
			aname = "__a" + actions.size();
			output.println( "static void " + aname + "(void)\n" + 
					"{\n"+
					"  double __rv;\n");
			compileUpdates(u);
			output.println( "\n}" +
					"\n");
			actions.add( aname );
		}

		Vector synchs = mf.getSynchs();
		for(int i = 0; i < synchs.size(); i++)
		{
			Vector synchCommands = getCommandsWithSynch( (String)(synchs.elementAt(i)) );

			for(int j = 0; j < synchCommands.size(); j++)
			{
				StochasticSynchCommand synchCommand = (StochasticSynchCommand)(synchCommands.elementAt(j));

				Expression g = synchCommand.getGuard();
				String gname = new String();
				gname = "__g" + guards.size();
				output.println( "static int " + gname + "(void)\n" +
						"{\n" +
						"  return " + d.dumpExpression(g) + ";\n" +
						"}");
				guards.add( gname );
	
				Vector su = synchCommand.getUpdates();
				String aname = new String();
				aname = "__a" + actions.size();
				output.println( "static void " + aname + "(void)\n"+
						"{\n"+
						"  double __rv;\n" +
						"  __rv = probability();\n" +
						"  current->TIME -= (1.0/((double)" + d.dumpExpression(synchCommand.getProbability()) +
					                 ")) * logl(__rv);");
				for(int k = 0; k < su.size(); k++)
					output.print( d.dumpUpdate( (Update)(su.elementAt(k)), "  ") );
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
		output.println( "#define NB_VERIF_GOAL " + pf.getNumProperties());
		output.println( "\n" +
				"static double MAX_TIME_VERIF[NB_VERIF_GOAL];\n" +
				"static int    CUR_PROP_VERIF;\n" +
				"typedef int (*tester_t)(const path *);\n" +
				"\n" +
				"static int until(tester_t __left, tester_t __right, const path *__p)\n" +
				"{\n" +
				"  int __cond;\n" +
				"\n" +
				"  if(!__p) return 0;\n" +
				"\n" +
				"  __cond = __right(__p);\n" +
				"  if (__cond)\n" +
				"    {\n" +
				"      MAX_TIME_VERIF[CUR_PROP_VERIF] = MAX(__p->TIME, MAX_TIME_VERIF[CUR_PROP_VERIF]);\n" +
				"      return 1;\n" +
				"    }\n" +
				"  __cond = __left(__p);\n" +
				"  if (!__cond)\n" +
				"    return 0;\n" +
				"  if(!__p->next)\n" +
				"    return 0;\n" +
				"  return until(__left, __right, __p->next);\n" +
				"}\n" +
				"\n" +
				"static int bounded_until(tester_t __left, double __lower, double __upper, tester_t __right, const path *__p)\n" + 
				"{\n" + 
				"  int __cond;\n" + 
				"\n" + 
				"  if(!__p) return 0;\n" + 
				"\n" + 
				"  __cond = __right(__p);\n" + 
				"  if( __cond && (__p->TIME >= __lower) && (__p->TIME <= __upper) )\n" + 
				"    {\n" +
				"      MAX_TIME_VERIF[CUR_PROP_VERIF] = MAX(__p->TIME, MAX_TIME_VERIF[CUR_PROP_VERIF]);\n" +
				"      return 1;\n" +
				"    }\n" +
				"  __cond=__left(__p);\n" + 
				"  if (!__cond)\n" + 
				"    return 0;\n" + 
				"  return bounded_until(__left, __lower, __upper, __right, __p->next);\n" + 
				"}\n" + 
				"\n" +
				"static int next(tester_t __w, const path *__p)\n" +
				"{\n" +
				"  int ret;\n" +
				"  if(!__p) return 0;\n" +
				"  if(!__p->next) return 0;\n" +
				"  ret = __w(__p->next);\n" +
				"  if( ret )\n" +
				"    MAX_TIME_VERIF[CUR_PROP_VERIF] = MAX(__p->next->TIME, MAX_TIME_VERIF[CUR_PROP_VERIF]);\n" +
				"  return ret;\n" +
				"}\n");

		d.setSource("__p");
		d.setPrototype("(const path *__p)");

		for(int i = 0; i < pf.getNumProperties(); i++)
		{
			try {
				output.print("static int verify_path_" + i + "(const path *__p)\n{\n" + 
					     "  CUR_PROP_VERIF = " + i + ";\n" +
					     "  MAX_TIME_VERIF[CUR_PROP_VERIF] = -1.0;\n" +
					     "  return " + d.dumpPCTL(pf.getProperty(i)) + ";\n" +
					     "}\n");
			} catch (ParserException e) {
				System.err.println("Unable to dump goal " + i + ":" + e);
				output.print("static int verify_path_" + i + "(const path *__p) { return 0; }\n");
				continue;
			}
		}
		output.println("typedef int (*verifier_func_t)(const path *__p);");
		output.println("verifier_func_t VERIF_GOAL[] = {");
		for(int i = 0; i < pf.getNumProperties()-1; i++)
			output.println("  verify_path_" + i + ",");
		output.println("  verify_path_" + (pf.getNumProperties()-1) + "\n};\n");
	}

}
