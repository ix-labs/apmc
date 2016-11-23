EXTRA_DIST=examples ChangeLog
SUBDIRS=include libapmc worker server

MAJOR=2
MINOR=0
SUBREV=0
VERSION=$(MAJOR).$(MINOR).$(SUBREV)
BINDIR=$(shell echo APMC-$(VERSION)-`uname -m`)

all :
	(cd server; make all)
	mv server/apmc-cmdline .
	(cd libapmc; make)

launch: all
	(cd ../apmc_deployment; ./configure; make dist)
	-ln -s ../apmc_deployment/apmcdeploy-2.0.0.tar.gz

dist :  APMC-$(VERSION).tar.gz

bindist: all
	@mkdir -p $(BINDIR)/bin
	@cp -f server/apmc-server $(BINDIR)/bin
	@cp -f libapmc/client/apmc-client $(BINDIR)/bin
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
	(cd server; make clean)
	(cd libapmc; make clean)
	find . -name '*~' | xargs rm -f {}

