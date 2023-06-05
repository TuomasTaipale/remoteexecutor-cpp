ACLOCAL_AMFLAGS = -I m4

BASE_CPPFLAGS = \
    -I$(top_srcdir)/include -I$(builddir)/include \
    -Wall -Werror -Wextra -Wpedantic \
    $(PTHREAD_CFLAGS)

BASE_LDFLAGS = \
    $(PTHREAD_CFLAGS)

BASE_LIBS = \
    $(PTHREAD_LIBS)

pkginclude_HEADERS = \
    include/remoteexecutor/executor.hpp \
    include/remoteexecutor/work.hpp

lib_LTLIBRARIES = \
    libre.la

libre_la_SOURCES = \
    include/private/workqueue.hpp \
    src/lib/executor.cpp \
    src/lib/workqueue.cpp

libre_la_CPPFLAGS = \
    $(BASE_CPPFLAGS)

libre_la_LDFLAGS = \
    $(BASE_LDFLAGS) \
    -version-info @REMOTEEXECUTOR_LT_VERSION@

libre_la_LIBADD = \
    $(BASE_LIBS)

bin_PROGRAMS = \
    simpleexample

simpleexample_SOURCES = \
    src/programs/simpleexample.cpp

simpleexample_CPPFLAGS = \
    $(BASE_CPPFLAGS)

simpleexample_LDADD = \
    libre.la

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libremoteexecutor.pc
nodist_pkgconfig_DATA = libremoteexecutor.pc

EXTRA_DIST = \
    $(top_srcdir)/libremoteexecutor.pc.in

clean-local:
	rm -f libremoteexecutor.pc