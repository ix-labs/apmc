MAJOR=1
MINOR=2
SUBREV=9
VERSION=$(MAJOR).$(MINOR).$(SUBREV)
BINDIR=$(shell echo APMC-$(VERSION)-`uname -m`)

all : 
	make -C server all
	make -C client amc-client

dist :  APMC-$(VERSION).tar.gz

bindist: all
	@mkdir -p $(BINDIR)/bin
	@cp -f server/src/amc-server $(BINDIR)/bin
	@cp -f client/amc-client $(BINDIR)/bin
	@mkdir -p $(BINDIR)/examples
	@cp -rf server/examples/*.* $(BINDIR)/examples
	tar cvzf $(BINDIR).tar.gz $(BINDIR)
	@rm -fr $(BINDIR)

APMC-$(VERSION).tar.gz : clean
	@ln -sf `pwd` APMC-$(VERSION)	
	tar cvzf APMC-$(VERSION).tar.gz --exclude "CVS" --exclude ".deps" --exclude ".cvsignore" --exclude "*.pm" --exclude "*.prop" APMC-$(VERSION)/[^AC]*
	@([ "$(USER)" = "syp" ] && cp -f APMC-$(VERSION).tar.gz ~syp/WWW/APMC/ && ln -sf APMC-$(VERSION).tar.gz ~syp/WWW/APMC/APMC-current.tar.gz ) || true
	@[ -L APMC-$(VERSION) ] && rm -f APMC-$(VERSION)

clean : 
	make -C server clean
	make -C client clean
	rm -f amc-client amc-server
	rm -f amc_gc_code*
	find . -name '*~' | xargs rm -f {}

