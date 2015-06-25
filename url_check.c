#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_url_check.h"
#include "checker.hh"

static zend_function_entry url_check_functions[] = {
	PHP_FE(url_checker, NULL) {
		NULL,
		NULL,
		NULL
	}
};

zend_module_entry url_check_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	PHP_URL_CHECK_EXTNAME,
	url_check_functions,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
#if ZEND_MODULE_API_NO >= 20010901
	PHP_URL_CHECK_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_URL_CHECK
ZEND_GET_MODULE(url_check)
#endif

PHP_FUNCTION(url_checker) {
	zval *arg, **data;
	HashTable *arg_hash;
	HashPosition arg_point;
	int arg_count;

	int i, result[CHECK_MAX_THREADS];
	thread_arg *arg_t;
	pthread_t thread[CHECK_MAX_THREADS];
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &arg) == FAILURE) {
		RETURN_NULL();
	}

	arg_hash = Z_ARRVAL_P(arg);
	arg_count = zend_hash_num_elements(arg_hash);
	status = (int*)malloc(arg_count * sizeof(int));
	arg_t = (thread_arg*)malloc(arg_count * sizeof(thread_arg));

	for (i = 0; i < arg_count; i++) {
		status[i] = -1;
	}

	php_printf("Array count: %d<br>", arg_count);

	for (zend_hash_internal_pointer_reset_ex(arg_hash, &arg_point), i = 0; zend_hash_get_current_data_ex(arg_hash, (void**)&data, &arg_point) == SUCCESS; zend_hash_move_forward_ex(arg_hash, &arg_point), i++) {
		convert_to_string_ex(data);
		arg_t[i].status = i;
		arg_t[i].url = Z_STRVAL_PP(data);
		//result[i] = pthread_create(&thread[i], NULL, thread_func, &arg_t[i]);
		php_printf("Number: %d<br>URL: %s<br><hr>", arg_t[i].status, arg_t[i].url);
	}

	free(status);
	free(arg_t);

	RETURN_STRING("URL Checker", 1);
}

