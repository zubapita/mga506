if WITH_CUTTER
noinst_LTLIBRARIES = test_mrn_sys.la
endif

AM_CPPFLAGS = $(GROONGA_CFLAGS) $(MECAB_INCLUDES) $(CUTTER_CFLAGS) $(GCUTTER_CFLAGS)
AM_INCLUDES = -l. -l..
ACLOCAL_AMFLAGS = $$ACLOCAL_ARGS

DEFS          = @DEFS@

LDFLAGS = -module -rpath $(libdir) -avoid-version -no-undefined

LIBS = $(CUTTER_LIBS) $(GROONGA_LIBS) $(MECAB_LIBS)

EXTERNAL_SRC = ../../mrn_sys.c

test_mrn_sys_la_SOURCES = $(EXTERNAL_SRC) test_mrn_sys.c
