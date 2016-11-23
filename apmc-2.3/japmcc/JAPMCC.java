import java.io.*;
import java.util.logging.*;
import parser.*;
import java.util.Vector;
import java.util.regex.*;

public class JAPMCC {

	private static PrintStream output;
	private static ModulesFile mf;
	private static PropertiesFile pf;

	private static void usage(String reason)
	{
		System.err.println("Usage: JAPMCC <module> <property> <output> <options>");
		System.err.println("  <module>   : [-m|--module] <filename>");
		System.err.println("  <property> : [-p|--property] <filename>");
		System.err.println("  <output>   : [-o|--output] <filename>");
		System.err.println("  <options>  : -h|--help        prints this help");
		System.err.println("               -d|--debug       enables all logging");
		System.err.println("");
		System.err.println(" Compiles a module and a property into a ad-hoc APMC verifier core");
		System.err.println(" Currently, only stochastic models are supported");
		System.err.println("");
		if( reason.equals("") )
		{
			System.exit(0);
		} else {
			System.err.println("*** error : " + reason);
			System.exit(1);
		}
	}

	public static void main(String[] args) throws ParseException, ParserException
	{
		InputStream module = null;
		InputStream property = null;
		output = System.out;
		Values moreDef = new Values();
		Pattern definition = null;
		Pattern equal = null;
		ModulesCompiler comp = null;

		try {
			definition = Pattern.compile("[a-zA-Z_0-9]+=(([0-9]*(.[0-9]+)?)|true|false)");
			equal = Pattern.compile("=");
		} catch (PatternSyntaxException e) {
			System.err.println("unable to compile one of the patterns: " + e);
			System.exit(1);
		 }

		Logger log = Logger.getLogger("JAPMCC");
		log.setLevel(Level.WARNING);

		for(int i = 0; i < args.length; i++)
		{
			if( args[i].equals("-m") || args[i].equals("--module") )
			{
				if( i+1 >= args.length )
					usage("no file specified after " + args[i]);
				try {
					module = new FileInputStream(args[i+1]);
				} catch(Exception e) {
					usage("error while opening " + args[i+1] + ": " + e.toString());
				}
				i++;
			}

			else if( args[i].equals("-p") || args[i].equals("--property") )
			{
				if( i+1 >= args.length )
					usage("no file specified after " + args[i]);
				try {
					property = new FileInputStream(args[i+1]);
				} catch(Exception e) {
					usage("error while opening " + args[i+1] + ": " + e.toString());
				}
				i++;
			}

			else if( args[i].equals("-o") || args[i].equals("--output") )
			{
				if( i+1 >= args.length )
					usage("no file specified after " + args[i]);
				try {
					output = new PrintStream(new FileOutputStream(args[i+1]));
				} catch(Exception e) {
					usage("error while opening " + args[i+1] + ": " + e.toString());
				}
				i++;
			}

			else if( args[i].equals("-h") || args[i].equals("--help") )
			{
				usage("");
			}

			else if( args[i].equals("-d") || args[i].equals("--debug") )
			{
				log.setLevel(Level.ALL);
			}

			else if ( definition.matcher(args[i]).matches() )
			{
				Object v = null;
				String def[] = equal.split(args[i]);

				if( def.length != 2 )
				{
					System.err.println(args[i] + ": malformed definition");
					System.exit(1);
				}

				try {
					v = new Integer(Integer.parseInt( def[1] ));
				} catch ( NumberFormatException _1 ) {
					try {
						v = new Double(Double.parseDouble( def[1] ));
	       				} catch ( NumberFormatException _2 ) {
						if( def[1].equals("true") )
							v = new Boolean(true);
						else if ( def[1].equals("false") )
							v = new Boolean(false);
						else {
							System.err.println(def[1] + " is neither a boolean, a double or an integer in definition of " + def[0]);
							System.exit(1);
						}
					}
				}
				log.info("defining " + def[0] + " to " + v.getClass().getName() + ":" + v);
				moreDef.addValue(def[0], v);
			}

			else
				usage("Unknown argument " + args[i]);
		}

		if( module == null )
			usage("module is a mandatory argument");
		if( property == null )
			usage("property is a mandatory argument");

		PrismParser p = new PrismParser();

                try {
			mf = p.parseModulesFile(module);
		} catch (ParseException e) {
			System.err.println("Syntax error in module file:\n" + e.getShortMessage());
			System.exit(1);
		}

		log.info("module file parsed");

		try {
			mf.tidyUp();
		} catch (ParserException e) {
			System.err.println("Error in module:\n" + e.getMessage());
			System.exit(1);
		}

		log.info("module file tidied up");

		Vector undefinedConstants = mf.getUndefinedConstants();
		int nberr = 0;
		for(int i = 0; i < undefinedConstants.size(); i++)
		{
			if( !moreDef.contains( (String)(undefinedConstants.elementAt(i)) ) )
			{
				System.err.println( undefinedConstants.elementAt(i).toString() + " is undefined");
				nberr++;
			}
		}
		if(nberr > 0)
			System.exit(1);

		mf.setUndefinedConstants(moreDef);

		try {
			pf = p.parsePropertiesFile(mf, property);
		} catch (ParseException e) {
			System.err.println("Syntax error in property file:\n" + e.getShortMessage());
			System.exit(1);
		}

		log.info("property file parsed");

		try {
			pf.tidyUp();
		} catch (ParserException e) {
			System.err.println("Error in property:\n" + e.getMessage());
			System.exit(1);
		}

		log.info("property file tidied up");

		log.info("moreDef = " + moreDef);

		pf.setUndefinedConstants(moreDef);

		if( mf.getType() == ModulesFile.PROBABILISTIC )
			comp = new ProbabilisticModulesCompiler(mf, pf, output);

		if( mf.getType() == ModulesFile.NONDETERMINISTIC )
		{
			System.err.println("nondeterministic models cannot be handled by appoximate probabilistic model checking");
			comp = new ProbabilisticModulesCompiler(mf, pf, output);
			//System.exit(1);
		}

		if( mf.getType() == ModulesFile.STOCHASTIC )
			comp = new StochasticModulesCompiler(mf, pf, output);

		try {
			comp.compileConstants(moreDef);
			comp.compileVariables();
			comp.compileRules();
			comp.compileProperties();
			comp.compileProbs();
			comp.compileEnd();
		} catch (ParserException e) {
			System.err.println("Unable to compile to a C file: " + e);
			System.exit(1);
		}
	}
}
