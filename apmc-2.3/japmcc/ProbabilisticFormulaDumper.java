import parser.*;
import java.io.PrintStream;

public class ProbabilisticFormulaDumper extends FormulaDumper {

	private int helper;

	public ProbabilisticFormulaDumper(PrintStream out)
	{
		super(out);
		helper = 1;
	}

    	protected String pctlBoundedUntil(PCTLBoundedUntil f) throws ParserException
	{
		output.println( "static int until_helper_" + (helper++) + "(const path *__p)\n" +
				"{\n" +
				"  return " + dumpPCTL(f.getOperand1()) + ";\n" +
				"}" );
		output.println( "static int until_helper_" + (helper++) + "(const path *__p)\n" +
				"{\n" +
				"  return " + dumpPCTL(f.getOperand2()) + ";\n" +
				"}" );

		String upper = dumpExpression(f.getUpperBound());
		String lower;
		if( f.getLowerBound() == null )
		{
			lower = "0";
		} else
			lower = dumpExpression(f.getLowerBound());

		return "bounded_until(until_helper_" + (helper-2) + ", " + lower + ", " + upper + ", until_helper_" + (helper-1) + ", " + varSource + ")";
	}

	protected String pctlUntil(PCTLUntil f) throws ParserException
	{
		output.println( "static int until_helper_" + (helper++) + "(const path *__p)\n" +
				"{\n" +
				"  return " + dumpPCTL(f.getOperand1()) + ";\n" +
				"}" );
		output.println( "static int until_helper_" + (helper++) + "(const path *__p)\n" +
				"{\n" +
				"  return " + dumpPCTL(f.getOperand2()) + ";\n" +
				"}" );

		return "until(until_helper_" + (helper-2) + ", until_helper_" + (helper-1) + ", " + varSource + ")";
	}

	protected String pctlNext(PCTLNext f) throws ParserException
	{
		output.println( "static int next_helper_" + (helper++) + "(const path *__p)\n" +
				"{\n" +
				"  return " + dumpPCTL(f.getOperand()) + ";\n" +
				"}" );
		return "next(next_helper_" + (helper-1) + ", " + varSource + ")";
	}
}
