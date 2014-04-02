PHP_ARG_ENABLE(nw_util, Enable nw_util support)

if test "$PHP_NW_UTIL" != "no"; then
    AC_DEFINE(HAVE_NW_UTIL, 1, [You have nw_util extension])
    PHP_NEW_EXTENSION(nw_util, nw_util.c, $ext_shared)
fi
