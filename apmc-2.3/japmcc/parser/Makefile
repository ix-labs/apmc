# Reminder: $@ = target, $* = target without extension, $< = dependency

THIS_DIR = parser
DIR_REL = ..
CLASSES_DIR = classes

JAVAC=javac

JAVA_FILES = \
Command.java ConstantList.java Declaration.java ExpressionAnd.java ExpressionBinary.java ExpressionBrackets.java ExpressionCeil.java ExpressionConstant.java ExpressionDivide.java ExpressionDouble.java ExpressionFalse.java ExpressionFloor.java ExpressionFormula.java ExpressionIdent.java ExpressionInt.java Expression.java ExpressionMax.java ExpressionMin.java ExpressionMinus.java ExpressionNary.java ExpressionNot.java ExpressionOr.java ExpressionPlus.java ExpressionRange.java ExpressionRelOp.java ExpressionTimes.java ExpressionTrue.java ExpressionUnary.java ExpressionVar.java FormulaList.java LabelList.java Module.java ModulesFile.java ParseException.java PCTLAnd.java PCTLBoundedUntil.java PCTLBrackets.java PCTLExpression.java PCTLFormulaBinary.java PCTLFormula.java PCTLFormulaNary.java PCTLFormulaUnary.java PCTLImplies.java PCTLInit.java PCTLLabel.java PCTLNext.java PCTLNot.java PCTLOr.java PCTLSS.java PCTLUntil.java PrismParserConstants.java PrismParser.java PrismParserTokenManager.java PropertiesFile.java RenamedModule.java SimpleCharStream.java SystemBrackets.java SystemDefn.java SystemFullParallel.java SystemHide.java SystemInterleaved.java SystemModule.java SystemParallel.java SystemRename.java Token.java TokenMgrError.java Update.java Updates.java Values.java VarList.java ParserException.java

CLASS_FILES = $(JAVA_FILES:%.java=$(DIR_REL)/$(CLASSES_DIR)/$(THIS_DIR)/%.class)

default: all

all: PrismParser.java $(CLASS_FILES)

PrismParser.java: PrismParser.jj
	javacc $<

$(DIR_REL)/$(CLASSES_DIR)/$(THIS_DIR)/%.class: %.java
	(cd ..; $(JAVAC) -sourcepath $(THIS_DIR)/$(DIR_REL) -classpath $(THIS_DIR)/$(DIR_REL)/$(CLASSES_DIR) -d $(THIS_DIR)/$(DIR_REL)/$(CLASSES_DIR) $(THIS_DIR)/$<)

clean: 
	@rm -f $(CLASS_FILES)
