PHP_ARG_ENABLE(url_check, whether to enable URL Checker support,
[  --enable-url_check	Enable URL Checker support])

if test "$PHP_URL_CHECK" = "yes"; then
LIBNAME=curl
LIBSYMBOL=symbol_curl_in_url_check

PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
[
  PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $MYEXTENSION_DIR/lib, MYEXTENSION_SHARED_LIBADD)
  AC_DEFINE(HAVE_MYEXTENSIONLIB,1,[ ])
],[
  AC_MSG_ERROR([wrong $LIBNAME lib version or lib not found])
],[
  -lcurl
]
AC_DEFINE(HAVE_URL_CHECK, 1, [Whether you have URL Checher])
PHP_NEW_EXTENSION(url_check, url_check.c, $ext_shared)
fi

