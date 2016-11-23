GROUP=sims
SERVER=tipi0d
TARGET=amc-client
PWD=/users/parall/herault/APMC/client
RSH=ssh

$(TARGET) : amc-client.o
	gcc -g -o $(TARGET) amc-client.o
	ln -s -f `pwd`/$(TARGET) ../$(TARGET)

amc-client.o : amc-client.c
	gcc -g -I../include -o amc-client.o -c amc-client.c

run :
	@for i in `cat $(GROUP)` ; do \
	    echo $$i ; \
	    echo "yes" | $(RSH) $$i "(cd $(PWD) && ./$(TARGET) $(SERVER))" > $(PWD)/$$i.out 2>&1 & \
	done

status :
	@for i in `cat $(GROUP)` ; do \
	    echo -n $$i" " ; \
	    export running=`$(RSH) $$i "ps auxww | grep $(TARGET) | grep -v grep | grep -v 'sh -c'"` ; \
	    test -z "$$running" && echo "[ [31mSTOPPED[0m ]" ; \
	    test -z "$$running" || echo \[\ [32mRUNNING[0m\ \]\ `echo $$running | awk '{printf("%%CPU:%s, %%MEM:%s, TIME:%s\n", $$3, $$4, $$10);}'` ; \
	done

kill :
	@for i in `cat $(GROUP)` ; do \
	    echo $$i ; \
	    $(RSH) $$i killall -TERM $(TARGET) ; \
	    rm -f $$i.out ; \
	done

clean :
	rm -f amc-client.o amc_gc_code.c amc_gc_code amc-client *~
