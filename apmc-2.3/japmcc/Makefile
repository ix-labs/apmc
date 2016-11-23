CLASSES_DIR=classes

JAVAC=javac
JAVA_FILES = JAPMCC.java ProbabilisticSynchCommand.java StochasticSynchCommand.java StochasticModulesCompiler.java ProbabilisticModulesCompiler.java ModulesCompiler.java FormulaDumper.java StochasticFormulaDumper.java ProbabilisticFormulaDumper.java
CLASS_FILES = $(JAVA_FILES:%.java=$(CLASSES_DIR)/%.class)

SAMPLE_P = examples/dice/dice.pctl
SAMPLE_M = examples/dice/dice.pm
SAMPLE_D = "x=1"

SAMPLE_P = examples/tandem/tandem.csl
SAMPLE_M = examples/tandem/tandem.sm
SAMPLE_D = "c=10"

SAMPLE_P = examples/polling/poll.csl
SAMPLE_M = examples/polling/poll10.sm
SAMPLE_D = 

SAMPLE_P = ../Formule.prop
SAMPLE_M = ../Csmacd.pm
SAMPLE_D = 

all : parser $(CLASS_FILES)

parser : 
	$(MAKE) -C parser

$(CLASSES_DIR)/%.class : %.java
	$(JAVAC) -sourcepath . -classpath $(CLASSES_DIR) -d $(CLASSES_DIR) $<

clean :
	rm -f $(CLASS_FILES)
	$(MAKE) -C parser clean

test : test.o
	gcc -o test test.o -lm

test.o : test.c endcode.h
	gcc -Wall -o test.o -c test.c

test.c : $(CLASS_FILES) $(SAMPLE_P) $(SAMPLE_M)
	java -cp classes JAPMCC -d -p $(SAMPLE_P) -m $(SAMPLE_M) $(SAMPLE_D) > test.c

.PHONY: parser clean
