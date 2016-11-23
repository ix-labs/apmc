AC_PREREQ([2.59])

dnl Initialisation of the project
AC_INIT([APMC Worker], [1.0.0], [guillaume.guirado@lrde.epita.fr], [apmcworker])
dnl Initialisation of Automake, create bzip2
AM_INIT_AUTOMAKE([1.4 foreign dist-bzip2])

CFLAGS="-Wall -O3"

dnl Checks for C compiler.
AC_LANG_PUSH([C])
AC_LANG_COMPILER
AC_LANG_POP
# Checks for programs.
AC_PROG_CC
AC_CHECK_HEADERS([sys/ioctl.h sys/filio.h])

# Checks for library functions.
# AC_FUNC_FORK
# AC_PROG_GCC_TRADITIONAL
# AC_FUNC_SELECT_ARGTYPES
# AC_CHECK_FUNCS([dup2 memset select])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT