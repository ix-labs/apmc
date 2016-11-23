CC=gcc
CFLAGS=-I../../include -I../include -Wall -g -DEBUG # -DNDEBUG \
#	-pg -DYYERROR_VERBOSE -DNEBUG_VERIFY \
#	-DYYDEBUG=1 -DDEBUG_FR -DDEBUG_PC -DDEBUG_AR -DDEBUG_SV
LDFLAGS=-lm #-pg libefence.a -lpthread

YACC=bison -y -v #-t
LEX=flex

GTK_CFLAGS=$(shell gtk-config --cflags)
GTK_LDFLAGS=$(shell gtk-config --libs)

TARGET1=amc-server
TARGET2=amc-cmdline
OBJECTS=rm.tab.o lex.rm.o ltl.tab.o lex.ltl.o double.o\
	reactive-modules.o verif.o path.o \
	rm_interp.o rm_clone.o rm_free.o rm_display.o\
	compilers.o strategy1.o strategy2.o strategy3.o 

GTK_OBJECTS=support.o callbacks.o interface.o gtkbfs.o main.o
CMD_OBJECTS=server-cmdline.o

OBJECTS1=$(OBJECTS) $(GTK_OBJECTS)
OBJECTS2=$(OBJECTS) $(CMD_OBJECTS)

SOURCES=reactive-modules.c verif.c path.c double.c compilers.c \
	rm_interp.c rm_clone.c rm_free.c rm_display.c\
	ltl.y ltl.l reactive-modules.l reactive-modules.l \
	support.c callbacks.c interface.c \
	strategy1.c strategy2.c strategy3.c \
	gtkbfs.c main.c \
	server-cmdline.c

all : $(TARGET1) $(TARGET2)

$(TARGET1) : $(OBJECTS1)
	gcc $(OBJECTS1) $(LDFLAGS) $(GTK_LDFLAGS) -o $(TARGET1) -lutil
	ln -s -f `pwd`/$(TARGET1) ../../$(TARGET1)
$(TARGET2) : $(OBJECTS2)
	gcc $(OBJECTS2) $(LDFLAGS) -o $(TARGET2) -lpthread
	ln -s -f `pwd`/$(TARGET2) ../../$(TARGET2)

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

lex.rm.c : reactive-modules.l rm.tab.h
	$(LEX) -Prm_ -olex.rm.c reactive-modules.l

reactive-modules.c : ../include/reactive-modules.h
	@echo dont remove my trick or take care to the consequences

%.o : %.c 
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -o $@ -c $<

clean :
	rm -f $(OBJECTS) $(CMD_OBJECTS) $(GTK_OBJECTS)
	rm -f lex.rm.c rm.tab.h rm.tab.c rm.output
	rm -f lex.ltl.c ltl.tab.h ltl.tab.c ltl.output
	rm -f $(TARGET1) $(TARGET2)
	rm -f *~ \#*\#
	rm -f amc_gc_code*

ltl.tab.o : ../include/path.h ../include/reactive-modules.h 
ltl.tab.o : ../include/rm_clone.h ../include/rm_interp.h 
ltl.tab.o : ../include/rm_display.h
rm.tab.o : ../include/path.h ../include/reactive-modules.h
rm.tab.o : ../include/rm_clone.h ../include/rm_interp.h 
rm.tab.o : ../include/rm_display.h
 
# DO NOT DELETE

reactive-modules.o: ../include/reactive-modules.h ../include/path.h
reactive-modules.o: ../include/rm_free.h ../include/rm_clone.h
reactive-modules.o: ../include/rm_interp.h ../include/rm_display.h
reactive-modules.o: ../include/double.h
path.o: ../include/path.h ../include/reactive-modules.h ../include/rm_free.h
path.o: ../include/rm_clone.h ../include/rm_interp.h ../include/rm_display.h
double.o: ../include/double.h
compilers.o: ../include/compilers.h ../include/reactive-modules.h
compilers.o: ../include/path.h ../include/rm_free.h ../include/rm_clone.h
compilers.o: ../include/rm_interp.h ../include/rm_display.h
compilers.o: ../include/support.h
rm_interp.o: ../include/rm_interp.h ../include/reactive-modules.h
rm_interp.o: ../include/path.h ../include/rm_free.h ../include/rm_clone.h
rm_interp.o: ../include/rm_display.h
rm_clone.o: ../include/rm_clone.h ../include/reactive-modules.h
rm_clone.o: ../include/path.h ../include/rm_free.h ../include/rm_interp.h
rm_clone.o: ../include/rm_display.h
rm_free.o: ../include/rm_free.h ../include/reactive-modules.h
rm_free.o: ../include/path.h ../include/rm_clone.h ../include/rm_interp.h
rm_free.o: ../include/rm_display.h
rm_display.o: ../include/rm_display.h ../include/reactive-modules.h
rm_display.o: ../include/path.h ../include/rm_free.h ../include/rm_clone.h
rm_display.o: ../include/rm_interp.h
ltl.o: ../include/path.h ../include/reactive-modules.h ../include/rm_free.h
ltl.o: ../include/rm_clone.h ../include/rm_interp.h ../include/rm_display.h
reactive-modules.o: ../include/reactive-modules.h ../include/path.h
reactive-modules.o: ../include/rm_free.h ../include/rm_clone.h
reactive-modules.o: ../include/rm_interp.h ../include/rm_display.h
reactive-modules.o: ../include/double.h
reactive-modules.o: ../include/reactive-modules.h ../include/path.h
reactive-modules.o: ../include/rm_free.h ../include/rm_clone.h
reactive-modules.o: ../include/rm_interp.h ../include/rm_display.h
reactive-modules.o: ../include/double.h
support.o: ../include/support.h
callbacks.o: ../include/callbacks.h ../include/interface.h
callbacks.o: ../include/support.h ../include/reactive-modules.h
callbacks.o: ../include/path.h ../include/rm_free.h ../include/rm_clone.h
callbacks.o: ../include/rm_interp.h ../include/rm_display.h
callbacks.o: ../../include/proto.h ../include/double.h ../include/compilers.h
interface.o: ../include/callbacks.h ../include/interface.h
interface.o: ../include/support.h ../../include/proto.h
interface.o: ../include/compilers.h ../include/reactive-modules.h
interface.o: ../include/path.h ../include/rm_free.h ../include/rm_clone.h
interface.o: ../include/rm_interp.h ../include/rm_display.h
interface.o: ../pixmap/open.xpm ../pixmap/save.xpm ../pixmap/saveas.xpm
interface.o: ../pixmap/clean.xpm ../pixmap/go.xpm ../pixmap/stop.xpm
interface.o: ../pixmap/compile.xpm
strategy1.o: ../include/compilers.h ../include/reactive-modules.h
strategy1.o: ../include/path.h ../include/rm_free.h ../include/rm_clone.h
strategy1.o: ../include/rm_interp.h ../include/rm_display.h
strategy2.o: ../include/compilers.h ../include/reactive-modules.h
strategy2.o: ../include/path.h ../include/rm_free.h ../include/rm_clone.h
strategy2.o: ../include/rm_interp.h ../include/rm_display.h
main.o: ../include/interface.h ../include/support.h ../include/callbacks.h
main.o: ../include/reactive-modules.h ../include/path.h ../include/rm_free.h
main.o: ../include/rm_clone.h ../include/rm_interp.h ../include/rm_display.h
main.o: ../include/compilers.h
gtkbfs.o: gtkbfs.h
