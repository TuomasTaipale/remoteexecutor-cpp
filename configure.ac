# API version
#
# 1. If no interface changes has been made, increment RE_MICRO.
# 2. Else, if new interfaces have been added but existing interfaces have not
#    been changed, increment RE_MINOR and zero RE_MICRO. (Backward compatible interface change.)
# 3. Else, increment RE_MAJOR and zero both RE_MINOR and RE_MICRO. (Backward incompatible
#    interface change.)
#
# Change the numbers just before release.
m4_define([RE_MAJOR], 0)
m4_define([RE_MINOR], 1)
m4_define([RE_MICRO], 0)

# ABI version with libtool
#
# 1. Always increase the revision value.
# 2. Increase the current value whenever an interface has been added, removed or changed.
# 3. Increase the age value only if the changes made to the ABI are backward compatible.
#
# Never zero or decrease any of the ABI version number values.
#
# See https://autotools.io/libtool/version.html
#
# Change the numbers just before release.
m4_define([RE_CURRENT], [1])
m4_define([RE_REVISION], [1])
m4_define([RE_AGE], [0])

AC_INIT([remoteexecutor], [RE_MAJOR.RE_MINOR.RE_MICRO], [], [],
	[https://github.com/TuomasTaipale/remoteexecutor])
AC_CONFIG_HEADERS([include/private/config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([libremoteexecutor.pc])
AM_INIT_AUTOMAKE([subdir-objects foreign 1.13 tar-pax -Wall -Werror])
AM_SILENT_RULES([yes])
AM_PROG_AR
LT_INIT
AC_PROG_CXX
AC_LANG([C++])
AC_CONFIG_MACRO_DIR([m4])
AX_CXX_COMPILE_STDCXX([17], [noext], [mandatory])
AX_PTHREAD
REMOTEEXECUTOR_LT_VERSION=m4_format("%d:%d:%d", RE_CURRENT, RE_REVISION, RE_AGE)
AC_SUBST(REMOTEEXECUTOR_LT_VERSION)
AC_OUTPUT
