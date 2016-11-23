AC_PREREQ([2.59])

dnl Initialisation of the project
AC_INIT([APMC], [2.0.0], [guillaume.guirado@lrde.epita.fr], [apmc])
dnl Initialisation of Automake, create bzip2
AM_INIT_AUTOMAKE([1.4 foreign dist-bzip2])

dnl Checks for C compiler.
AC_LANG_PUSH([C])
AC_LANG_COMPILER
AC_LANG_POP

AC_PROG_CC
AC_PROG_LIBTOOL

AC_CHECK_HEADERS([sys/ioctl.h sys/filio.h])
AC_CONFIG_HEADERS([config.h])


AC_CONFIG_FILES([Makefile
		apmc/Makefile
		apmc/libapmc/Makefile
		apmc/server/Makefile
		apmc/include/Makefile])
AC_OUTPUT

(cd apmc_deployment; ./configure)
(cd apmc/worker; ./configure)
