include $(top_srcdir)/aminclude_static.am

AM_CPPFLAGS = -I$(top_srcdir)/include $(CODE_COVERAGE_CPPFLAGS)
AM_CFLAGS = $(CODE_COVERAGE_CFLAGS)

TESTS = test_arcfour test_MISTY1 test_ripemd160

check_PROGRAMS = test_arcfour test_MISTY1 test_ripemd160

LDADD = -lcmocka ../src/libbeercrypto.la $(CODE_COVERAGE_LIBS)

test_arcfour_SOURCES = test_arcfour.c
test_MISTY1_SOURCES = test_MISTY1.c
test_ripemd160_SOURCES = test_ripemd160.c

clean-local: code-coverage-clean
distclean-local: code-coverage-dist-clean