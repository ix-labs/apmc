# AC_PREREQ([2.59])

dnl Initialisation of the project
AC_INIT([APMC deployment], [2.0.0], [guillaume.guirado@lrde.epita.fr], [apmcdeploy])
dnl Initialisation of Automake, create bzip2
AM_INIT_AUTOMAKE([1.4 foreign])

CFLAGS="-Wall -O3"
dnl Checks for C compiler.
AC_LANG_PUSH([C])
AC_LANG_COMPILER
AC_LANG_POP

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([sys/ioctl.h sys/filio.h])
AC_CONFIG_HEADERS([config.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_TIME

# Checks for library functions.
AC_FUNC_FORK
AC_PROG_GCC_TRADITIONAL
AC_FUNC_SELECT_ARGTYPES
AC_CHECK_FUNCS([dup2 memset select])

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
