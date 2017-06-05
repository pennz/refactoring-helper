## Process this file with automake to produce Makefile.in

TESTS = check_counter
check_PROGRAMS = check_counter
check_counter_SOURCES = check_counter.c $(top_builddir)/src/counter.h
check_counter_CFLAGS = @CHECK_CFLAGS@
check_counter_LDADD = $(top_builddir)/src/libcounter.la @CHECK_LIBS@
