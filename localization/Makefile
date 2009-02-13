
GTK_CFLAGS=`pkg-config gtk+-2.0 --cflags`
GTK_LIBS=`pkg-config gtk+-2.0 --libs`

PACKAGE=loc_test
SOURCES=main.cpp

DIST_SOURCES=$(SOURCES) Makefile $(PACKAGE).pot

all:
	g++ -Wall $(GTK_CFLAGS) $(GTK_LIBS) $(SOURCES) -o $(PACKAGE) 

loc:
	rm -f $(PACKAGE).po $(PACKAGE).pot ru.po $(PACKAGE).mo;
	xgettext -C --default-domain=$(PACKAGE) -k_ $(SOURCES);
	mv $(PACKAGE).po $(PACKAGE).pot;
	msginit;
	gvim ru.po;
	msgfmt ru.po -o $(PACKAGE).mo;

install:
	cp ./$(PACKAGE) /usr/local/bin/$(PACKAGE);
	cp ./$(PACKAGE).mo /usr/local/share/locale/ru/LC_MESSAGES/$(PACKAGE).mo

uninstall:
	rm -f /usr/local/bin/$(PACKAGE);
	rm -f /usr/local/share/locale/ru/LC_MESSAGES/$(PACKAGE).mo

dist:
	tar -c $(DIST_SOURCES) > $(PACKAGE).tar;
	gzip $(PACKAGE).tar > $(PACKAGE).tar.gz;
