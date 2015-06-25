#ifndef PHP_URL_CHECK_H
#define PHP_URL_CHECK_H 1

#define PHP_URL_CHECK_VERSION "0.1"
#define PHP_URL_CHECK_EXTNAME "url_check"

#define CHECK_MAX_THREADS 8

PHP_FUNCTION(url_checker);

extern zend_module_entry url_check_module_entry;
#define phpext_url_check_ptr &url_check_module_entry

#endif

