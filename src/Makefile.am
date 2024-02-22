## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = test

test_SOURCES = \
	main.c \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h \
	ets.c ets.h \
	utilisateur.c utilisateur.h \
	rdv.c rdv.h \
	fonction.c fonction.h \
	yassAjoutRegister.c yassAjoutRegister.h \
	yassVerifLogin.c yassVerifLogin.h \
	fonctions.c fonctions.h

test_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

