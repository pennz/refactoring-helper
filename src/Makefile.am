## Process this file with automake to produce Makefile.in

lib_LTLIBRARIES = libcounter.la
libcounter_la_SOURCES = parser/counter.c parser/counter.h

bin_PROGRAMS = main
main_SOURCES = main.c
main_LDADD = libcounter.la
