import java.io.PrintStream;
import parser.*;
import java.util.Vector;

public abstract class FormulaDumper {

	protected String varSource;
	protected String prototype;
	protected PrintStream output;

	public FormulaDumper(PrintStream o)
	{
		output = o;
		varSource = "";
		prototype="(void)";
	}

	public void setSource(String v)
	{
		varSource = v;
	}

	public String getArrowSource()
	{
		if(varSource.equals(""))
			return "";
		return varSource + "->";
	}

	public void setPrototype(String p)
	{
		prototype = p;
	}

	private String dumpNaryExpression(ExpressionNary e, String op)
	{
		int i, n;
		String s = "";
		
		n = e.getNumOperands();
		if(n > 0)
			s += "(";
		for (i = 0; i < n-1; i++) {
			s = s + dumpExpression(e.getOperand(i)) + op;
		}
		if (n > 0) {
			s = s + dumpExpression(e.getOperand(n-1));
			s += ")";
		}
		
		return s;		
	}

	private String dumpBinaryExpression(ExpressionBinary e, String op)
	{
		try {
			if( e.getType() == Expression.DOUBLE )
				return "(((double)(" + dumpExpression(e.getOperand1()) + "))" + op + "((double)(" + dumpExpression(e.getOperand2()) + ")))";
		} catch ( ParserException exc ) {
			System.err.println("error " + exc);
			System.exit(0);
		}
		return "(" + dumpExpression(e.getOperand1()) + op + dumpExpression(e.getOperand2()) + ")";
	}

	private String dumpRecNaryExpression(ExpressionNary e, String op)
	{
		int n = e.getNumOperands();
		if(n == 1)
			return dumpExpression( e.getOperand(0) );
		else {
			String s = op + "(";
			for(int i = 0; i < n-2; i++)
				s += dumpExpression(e.getOperand(i)) + ", " + op + "(";
			s += dumpExpression(e.getOperand(n-2)) + ", " + dumpExpression(e.getOperand(n-1));
			for(int i = 0; i < n-1; i++)
				s += ")";
			return s;
		}
	}

	private String dumpRange(ExpressionRange r)
	{
		String s = "";
		String v = dumpExpression(r.getOperand());
		if(r.getRelOp().equals("!="))
			s = "!(";

		for(int i = 0; i < r.getNumRangeOperands(); i++)
		{
			if(i > 0)
				s += "||";
			if( r.getRangeOperandSize(i) == 1 )
				s += "(" + v + "==" + dumpExpression(r.getRangeOperandLow(i)) +")";
			else
				s += "((" + v + ">=" + dumpExpression(r.getRangeOperandLow(i)) + ")&&(" + v + "<=" + dumpExpression(r.getRangeOperandHigh(i))+"))";
		}

		if(r.getRelOp().equals("!="))
			s += ")";
		return s;
	}

	private String dumpRelOpExpression(ExpressionRelOp e)
	{
		if( e.getRelOp().equals("=") )
			return "(" + dumpExpression(e.getOperand1()) + "==" + dumpExpression(e.getOperand2()) + ")";
		else
			return "(" + dumpExpression(e.getOperand1()) + e.getRelOp() + dumpExpression(e.getOperand2()) + ")";
	}

	public String dumpExpression(Expression e)
	{
		if( e instanceof ExpressionAnd )
			return dumpNaryExpression((ExpressionNary)e, "&&");
		else if( e instanceof ExpressionBrackets )
			return dumpExpression( ((ExpressionBrackets)e).getOperand() );
		else if( e instanceof ExpressionCeil )
			return "ceil(" + dumpExpression( ((ExpressionCeil)e).getOperand() ) + ")";
		else if( e instanceof ExpressionConstant )
			return ((ExpressionConstant)e).getName();
		else if( e instanceof ExpressionDivide )
			return dumpBinaryExpression( (ExpressionBinary)e, "/" );
		else if( e instanceof ExpressionDouble )
			return "" + ((ExpressionDouble)e).getValue();
		else if( e instanceof ExpressionFalse )
			return "0";
		else if( e instanceof ExpressionFloor )
			return "floor(" + dumpExpression( ((ExpressionFloor)e).getOperand() ) + ")";
		else if( e instanceof ExpressionIdent )
			return getArrowSource() + ((ExpressionIdent)e).getName();
		else if( e instanceof ExpressionInt )
			return "" + ((ExpressionInt)e).getValue();
		else if( e instanceof ExpressionMax )
			return dumpRecNaryExpression( (ExpressionNary)e, "MAX" );
		else if( e instanceof ExpressionMin )
			return dumpRecNaryExpression( (ExpressionNary)e, "MIN" );
		else if( e instanceof ExpressionMinus )
			return dumpBinaryExpression( (ExpressionBinary)e, "-" );
		else if( e instanceof ExpressionNot )
			return "!(" + dumpExpression( ((ExpressionNot)e).getOperand() ) + ")";
		else if( e instanceof ExpressionOr )
			return dumpNaryExpression((ExpressionNary)e, "||");
		else if( e instanceof ExpressionPlus )
			return dumpBinaryExpression((ExpressionBinary)e, "+");
		else if( e instanceof ExpressionRange )
			return dumpRange((ExpressionRange)e);
		else if( e instanceof ExpressionRelOp )
			return dumpRelOpExpression((ExpressionRelOp)e );
		else if( e instanceof ExpressionTimes )
			return dumpBinaryExpression((ExpressionBinary)e, "*");
		else if( e instanceof ExpressionTrue )
			return "1";
		else if( e instanceof ExpressionVar )
			return getArrowSource() + ((ExpressionVar)e).getName();
		else return "ExpressionClass " + e.getClass().getName();
	}

	public String dumpUpdate( Update u, String spaces )
	{
		String s = "";
		for(int i = 0; i < u.getNumElements(); i++)
		{
			s += spaces + getArrowSource() + u.getVar(i) + " = " + dumpExpression( u.getExpression(i) ) + ";\n";
		}
		return s;
	}

	
	private String pctlNary(PCTLFormulaNary f, String op) throws ParserException
	{
		int i, n;
		String s = "";
		
		n = f.getNumOperands();
		if(n > 0)
			s += "(";
		for (i = 0; i < n-1; i++) {
			s = s + dumpPCTL(f.getOperand(i)) + op;
		}
		if (n > 0) {
			s = s + dumpPCTL(f.getOperand(n-1));
			s += ")";
		}
		
		return s;		
	}

	protected abstract String pctlBoundedUntil(PCTLBoundedUntil f) throws ParserException;
	protected abstract String pctlUntil(PCTLUntil f) throws ParserException;
	protected abstract String pctlNext(PCTLNext f) throws ParserException;

	public String dumpPCTL(PCTLFormula f) throws ParserException
	{
		if( f instanceof PCTLAnd )
			return pctlNary((PCTLFormulaNary)f, "&&");
		else if( f instanceof PCTLBoundedUntil )
			return pctlBoundedUntil((PCTLBoundedUntil)f);
		else if( f instanceof PCTLBrackets )
			return dumpPCTL(((PCTLFormulaUnary)f).getOperand());
		else if( f instanceof PCTLExpression )
			return dumpExpression( ((PCTLExpression)f).getExpression() );
		else if( f instanceof PCTLImplies )
			return "(!(" + dumpPCTL(((PCTLFormulaBinary)f).getOperand1()) + ")) || (" + dumpPCTL(((PCTLFormulaBinary)f).getOperand2()) + ")";
		else if( f instanceof PCTLNext )
			return pctlNext((PCTLNext)f);
		else if( f instanceof PCTLNot )
			return "!(" + dumpPCTL(((PCTLFormulaUnary)f).getOperand()) + ")";
		else if( f instanceof PCTLOr )
			return pctlNary((PCTLFormulaNary)f, "||");
		else if( f instanceof PCTLUntil )
			return pctlUntil((PCTLUntil)f);
		else throw new ParserException(f.getClass().getName() + " not done");
	}

	public String dumpProb(PCTLFormula f) throws ParserException
	{
		String op = null;
		int iop;
		Expression prob = null;

		if( f instanceof PCTLNext )
		{
			op = ((PCTLNext)f).getRelOp();
			prob = ((PCTLNext)f).getProb();
		}
		else if( f instanceof PCTLUntil )
		{
			op = ((PCTLUntil)f).getRelOp();
			prob = ((PCTLUntil)f).getProb();
		}
		else if( f instanceof PCTLBoundedUntil )
		{
			op = ((PCTLBoundedUntil)f).getProbRelOp();
			prob = ((PCTLBoundedUntil)f).getProb();
		}
		if( op == ">" )
		  iop = 1;
		else if( op == "<" )
		  iop = 2;
		else if( op == "=" )
		  iop = 3;
		else if( op == ">=" )
		  iop = 4;
		else if( op == "<=" )
		  iop = 5;
		else
		  iop = 0;
		if (op == null || prob == null)
		  iop = 0;
		if (prob == null)
		  prob = new ExpressionDouble(0);
		return iop + ", " + prob;
	}


	public int varsInExpression(Expression e, Vector acc) throws ParserException
	{
		if( e instanceof ExpressionUnary )
			return varsInExpression( ((ExpressionUnary)e).getOperand(), acc );
		else if( e instanceof ExpressionBinary )
		{
			ExpressionBinary b = (ExpressionBinary)e;
			return varsInExpression( b.getOperand1(), acc ) + varsInExpression( b.getOperand2(), acc );
		} 
		else if(e instanceof ExpressionNary )
		{
			int r = 0;
			ExpressionNary n = (ExpressionNary)e;
			for(int i = 0; i < n.getNumOperands(); i++)
				r += varsInExpression( n.getOperand(i), acc );
			return r;
		}
		else if( e instanceof ExpressionConstant )
			return 0;
		else if( e instanceof ExpressionFalse )
			return 0;
		else if( e instanceof ExpressionIdent )
		{
			acc.add( ((ExpressionIdent)e).getName() );
			return 1;
		}
		else if( e instanceof ExpressionInt )
			return 0;
		else if( e instanceof ExpressionRange )
			throw new ParserException("Range not implemented yet in varsInExpression");
		else if( e instanceof ExpressionTrue )
			return 0;
		else if( e instanceof ExpressionVar )
		{
			acc.add( ((ExpressionVar)e).getName() );
			return 1;
		}
		else throw new ParserException("ExpressionClass " + e.getClass().getName());
	}

	public int varsInPCTL(PCTLFormula f, Vector acc) throws ParserException
	{
		if( f instanceof PCTLFormulaNary )
		{
			PCTLFormulaNary n = (PCTLFormulaNary)f;
			int r = 0;
			for(int i = 0; i < n.getNumOperands(); i++)
				r += varsInPCTL(n.getOperand(i), acc);
			return r;
		}
		else if( f instanceof PCTLFormulaBinary )
		{
			PCTLFormulaBinary b = (PCTLFormulaBinary)f;
			return varsInPCTL(b.getOperand1(), acc) + varsInPCTL(b.getOperand2(), acc);
		}
		else if( f instanceof PCTLFormulaUnary )
			return varsInPCTL(((PCTLFormulaUnary)f).getOperand(), acc);
		else if( f instanceof PCTLExpression )
			return varsInExpression( ((PCTLExpression)f).getExpression(), acc );
		else throw new ParserException( f.getClass().getName() + " not done" );
	}

}
