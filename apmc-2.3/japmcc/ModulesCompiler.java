import java.io.PrintStream;
import parser.*;
import java.util.Vector;

public abstract class ModulesCompiler {

	protected ModulesFile mf;
	protected PropertiesFile pf;
	protected PrintStream output;
	protected FormulaDumper d;

	private Vector pVars;

	public ModulesCompiler(ModulesFile _mf, PropertiesFile _pf, PrintStream _out, FormulaDumper _d)
	{
		mf = _mf;
		pf = _pf;
		output = _out;
		d = _d;

		try {
			pVars = new Vector();
			for(int i = 0; i < pf.getNumProperties(); i++)
			{
				Vector v = new Vector();
				d.varsInPCTL( pf.getProperty(i), v );
				for(int j = 0; j < v.size(); j++)
				{
					if( !pVars.contains( v.elementAt(j) ) )
						pVars.add( v.elementAt(j) );
				}
			}
		} catch (Exception e) {
			System.err.println("Internal JAPMCC error: " + e);
			System.exit(1);
		}
	}

	public void compileConstants(Values md) throws ParserException
	{
		Values cv = mf.getConstantValues();
		ConstantList cl = mf.getConstantList();

		output.println( "#include <stdlib.h>\n" +
				"#include <string.h>\n" +
				"#include <math.h>\n" +
				"\n"+
				"static unsigned int get_random(unsigned int min, unsigned int max)\n"+
				"{\n"+
				"  max++;\n"+
				"  return min + (unsigned int)( (double)(max-min)*rand()/(RAND_MAX+(double)min));\n"+
				"}\n"+
				"\n"+
				"static double probability()\n"+
				"{\n"+
				"  double r = (double)((unsigned int)-2);\n"+
				"  double R = get_random(0, (unsigned int)-2);\n"+
				"  r = ((double)R) / r;\n"+
				"  return r;\n"+
				"}\n"+
				"/* constants and macros */\n" +
				"#define new(a) (a*)calloc(1, sizeof(a))\n" +
				"#define MAX(a,b) (((a)<(b))?(b):(a))\n" +
				"#define MIN(a,b) (((a)<(b))?(a):(b))\n" );
		
		for(int i = 0; i < cv.getNumValues(); i++)
		{
			output.print("#define " + cv.getName(i) + "\t(" );
			if( cl.getConstantType(i) == Expression.INT )
				output.println("(int)(" + cv.getIntValue(i) + "))");
			if( cl.getConstantType(i) == Expression.BOOLEAN )
				output.println("(int)(" + (cv.getBooleanValue(i) ? "1" : "0" +" ))" ));
			if( cl.getConstantType(i) == Expression.DOUBLE )
				output.println("(double)(" + cv.getDoubleValue(i) + "))");
		}
		for(int i = 0; i < md.getNumValues(); i++)
		{
			output.print("#define " + md.getName(i) + "\t(" );
			if( md.getType(i) == Expression.INT )
				output.println("(int)(" + md.getIntValue(i) + "))");
			if( md.getType(i) == Expression.BOOLEAN )
				output.println("(int)(" + (md.getBooleanValue(i) ? "1" : "0" +" ))" ));
			if( md.getType(i) == Expression.DOUBLE )
				output.println("(double)(" + md.getDoubleValue(i) + "))");
		}
		output.println("");
	}

	protected void compAllVariablesDeclaration(String spaces) throws ParserException
	{
		VarList varList = mf.createVarList();

		for(int i = 0; i < varList.getNumVars(); i++)
			output.println(spaces + "int " + varList.getName(i) + ";");
	}

	protected void compPropertiesVariablesDeclaration(String spaces) throws ParserException
	{
		for(int i = 0; i < pVars.size(); i++)
			output.println(spaces + "int " + pVars.elementAt(i) + ";");
	}

	protected void compAllVariablesInitialization(String spaces, String source) throws ParserException
	{
		VarList varList = mf.createVarList();
		String s;
		if( !source.equals("") )
			s = spaces + source + "->";
		else
			s = spaces;

		for(int i = 0; i < varList.getNumVars(); i++)
			output.println(s + varList.getName(i) + " = " + varList.getStart(i) + ";");
	}

	protected void compPropertiesVariablesIntialization(String spaces, String dest, String source) throws ParserException
	{
		String src;
		if( source.equals("") )
			src = "";
		else
			src = source + "->";

		String dst;
		if( dest.equals("") )
			dst = spaces;
		else
			dst = spaces + dest + "->";

		for(int i = 0; i < pVars.size(); i++)
			output.println(dst + pVars.elementAt(i) + " = " + src + pVars.elementAt(i) + ";");
	}

	public abstract void compileVariables() throws ParserException;
	public abstract void compileRules() throws ParserException;
	public abstract void compileProperties() throws ParserException;
	public void compileProbs() throws ParserException
	{
		output.print( "struct s_threshold\n" +
			      "{\n" +
			      "  char op;\n" +
			      "  double threshold;\n" +
			      "};\n" +
			      "\n" +
			      "static struct s_threshold tthresholds[NB_VERIF_GOAL] =\n" +
			      "{\n" );
		for(int i = 0; i < pf.getNumProperties(); i++)
		{
			try {
				output.print("  { " + d.dumpProb(pf.getProperty(i)) + " }");
				if( i != pf.getNumProperties() - 1 )
				  output.print(",");
				output.print("\n");
			} catch (ParserException e) {
				System.err.println("Unable to dump threshold " + i + ":" + e);
				output.print("{}");
				if( i != pf.getNumProperties() - 1 )
				  output.print(",");
				output.print("\n");
				continue;
			}
		}
		output.print( "};\n\n" );
	}

	public void compileEnd() throws ParserException
	{
		output.println(	"static void run(int nbtrue[NB_VERIF_GOAL], int nbfalse[NB_VERIF_GOAL], int path_len, int some_time)\n" +
				"{\n" +
				"  int p, r;\n" +
				"  struct rule totest[NBRULES];\n" +
				"  int nbtotest;\n" +
				"  time_t start, end;\n" +
				"\n" +
				"  memset(nbtrue, 0, sizeof(int)*NB_VERIF_GOAL);\n" +
				"  memset(nbfalse, 0, sizeof(int)*NB_VERIF_GOAL);\n" +
				"  time(&start);\n" +
				"  do {\n" +
				"      init_state();\n" +
				"      for(p = 0; p < path_len; p++)\n" +
				"	{\n" +
				"	  memcpy(totest, rules, NBRULES * sizeof(struct rule));\n" +
				"	  nbtotest = NBRULES;\n" +
				"	  while( nbtotest > 0 )\n" +
				"	    {\n" +
				"	      r = get_random(0, nbtotest-1);\n" +
				"	      if( totest[r].guard() )\n" +
				"		break;\n" +
				"	      memcpy(&totest[r], &totest[nbtotest-1], sizeof(struct rule));\n" +
				"	      nbtotest--;\n" +
				"	    }\n" +
				"	  if( nbtotest == 0 )\n" +
				"	    break;\n" +
				"	  totest[r].action();\n" +
				"	  append_state();\n" +
				"	}\n" +
				"\n" +
				"      for(p = 0; p < NB_VERIF_GOAL; p++)\n" +
				"	{\n" +
				"	  if( VERIF_GOAL[p](first_path) )\n" +
				"	    nbtrue[p]++;\n" +
				"	  else\n" +
				"	    nbfalse[p]++;\n" +
				"	}\n" +
				"    time(&end);\n" +
				"  } while (end-start < some_time);\n" +
				"}\n" +
				"\n" +
				"#include \"endcode.h\"\n");
	}

}
