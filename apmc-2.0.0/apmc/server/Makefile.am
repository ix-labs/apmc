EXTRA_DIST=lex.ltl.c ltl.l reactive-modules.c server-cmdline.c ltl.tmpl.y reactive-modules.l rm.tab.c bison_pp.pl lex.rm.c ltl.tab.c ltl.y reactive-modules.tmpl.y rm.tab.h testexpr.c expr.tmpl.y ltl.tab.h reactive-modules.y testlib.c

CFLAGS=-I../include -I. -I../libapmc -Wall
LDFLAGS=-lm

YACC=bison -y -v -t
LEX=flex

TARGET2=apmc-cmdline

LIBAPMC=libapmc.so

OBJECTS=rm.tab.o lex.rm.o ltl.tab.o lex.ltl.o

CMD_OBJECTS=server-cmdline.o

OBJECTS2=$(OBJECTS) $(CMD_OBJECTS)

.PHONY: ../libapmc

all : $(TARGET2)


../libapmc/.libs/libapmc.a:
	(cd ../libapmc; make clean all)

../libapmc:
	(cd ../libapmc; make clean all)

$(TARGET2) : $(OBJECTS2) ../libapmc/.libs/libapmc.a
	$(CC) $(OBJECTS2) $(LDFLAGS) -o $(TARGET2)  ../libapmc/.libs/libapmc.a

depend : clean
	makedepend -fMakefile -Y -- $(CFLAGS) -- $(SOURCES) 2>/dev/null
	rm -f Makefile.bak

TAGS : $(SOURCES)
	$(MAKE) clean
	rm -f TAGS
	etags $(SOURCES)

ltl.tab.c ltl.tab.h : ltl.y
	$(YACC) -p ltl_ -b ltl -d ltl.y

lex.ltl.c : ltl.l ltl.tab.h
	$(LEX) -Pltl_ -olex.ltl.c ltl.l

rm.tab.c rm.tab.h : reactive-modules.y
	$(YACC) -p rm_ -b rm -d reactive-modules.y

lex.rm.c_force : reactive-modules.l rm.tab.h
	$(LEX) -Prm_ -olex.rm.c reactive-modules.l

ltl.y : ltl.tmpl.y expr.tmpl.y
	perl bison_pp.pl ltl.tmpl.y > ltl.y

reactive-modules.y : reactive-modules.tmpl.y expr.tmpl.y
	perl bison_pp.pl reactive-modules.tmpl.y > reactive-modules.y

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean :
	rm -f $(OBJECTS) $(CMD_OBJECTS)
#	rm -f lex.rm.c rm.tab.h
#	rm -f rm.tab.c rm.output
#	rm -f lex.ltl.c ltl.tab.h ltl.tab.c ltl.output
	rm -f ../$(TARGET2) $(TARGET2)
	rm -f *~ \#*\#
	rm -f apmc_gc_code*
#	rm -f ltl.y
#	rm -f reactive-modules.y
	rm -f testlib testlib.o testexpr.o

ltl.tab.o : ltl.tab.c ../libapmc/reactive-modules.h ../libapmc/rm_clone.h ../libapmc/rm_display.h
	$(CC) $(CFLAGS) -o $@ -c ltl.tab.c

rm.tab.o : rm.tab.c ../libapmc/reactive-modules.h ../libapmc/rm_clone.h ../libapmc/rm_display.h
	$(CC) $(CFLAGS) -o $@ -c rm.tab.c

lex.rm.o: lex.rm.c
	$(CC) $(CFLAGS) -o $@ -c lex.rm.c

lex.ltl.o: lex.ltl.c
	$(CC) $(CFLAGS) -o $@ -c lex.ltl.c -DYY_NO_UNPUT

server-cmdline.o: server-cmdline.c
	$(CC) $(CFLAGS) -o $@ -c server-cmdline.c
