include $(top_srcdir)/aminclude_static.am

lib_LTLIBRARIES = libbeercrypto.la
libbeercrypto_la_SOURCES = unsafe/arcfour/arcfour.c unsafe/misty1/misty1.c
libbeercrypto_la_LIBS = $(CODE_COVERAGE_LIBS)
libbeercrypto_la_CPPFLAGS = $(CODE_COVERAGE_CPPFLAGS) -I$(top_srcdir)/include 
libbeercrypto_la_CFLAGS = $(CODE_COVERAGE_CFLAGS)

clean-local: code-coverage-clean
distclean-local: code-coverage-dist-clean