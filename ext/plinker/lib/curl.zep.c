
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/array.h"
#include "kernel/fcall.h"
#include "kernel/string.h"
#include "kernel/operators.h"


ZEPHIR_INIT_CLASS(Plinker_Lib_Curl) {

	ZEPHIR_REGISTER_CLASS(Plinker\\Lib, Curl, plinker, lib_curl, plinker_lib_curl_method_entry, ZEND_ACC_FINAL_CLASS);

	zend_declare_property_null(plinker_lib_curl_ce, SL("config"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(plinker_lib_curl_ce, SL("options"), ZEND_ACC_PRIVATE TSRMLS_CC);

	return SUCCESS;

}

/**
 *
 */
PHP_METHOD(Plinker_Lib_Curl, __construct) {

	zval *config_param = NULL;
	zval config;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&config);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &config_param);

	if (!config_param) {
		ZEPHIR_INIT_VAR(&config);
		array_init(&config);
	} else {
	ZEPHIR_OBS_COPY_OR_DUP(&config, config_param);
	}


	zephir_update_property_zval(this_ptr, SL("config"), &config);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Plinker_Lib_Curl, setOptions) {

	zval _0, _1;
	zval __$true, __$false, _2;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 7, 0 TSRMLS_CC);
	zephir_array_update_long(&_0, 45, &__$true, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_array_update_long(&_0, 52, &__$true, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_array_update_long(&_0, 19913, &__$true, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_array_update_long(&_0, 64, &__$false, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_array_update_long(&_0, 81, &__$false, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	add_index_stringl(&_0, 10102, SL("gzip"));
	ZEPHIR_INIT_VAR(&_1);
	zephir_create_array(&_1, 1, 0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "Content-Type: application/json");
	zephir_array_fast_append(&_1, &_2);
	zephir_array_update_long(&_0, 10023, &_1, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_update_property_zval(this_ptr, SL("options"), &_0);
	ZEPHIR_MM_RESTORE();

}

/**
 *  POST
 */
PHP_METHOD(Plinker_Lib_Curl, post) {

	zephir_fcall_cache_entry *_8 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval headers, _9$$6;
	zval *url_param = NULL, *parameters = NULL, parameters_sub, *headers_param = NULL, __$true, __$null, curl, body, _3, _4, _6, _7, _0$$3, _1$$3, _2$$3, header$$4, *_5$$4, _10$$6, _11$$6;
	zval url;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&url);
	ZVAL_UNDEF(&parameters_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&curl);
	ZVAL_UNDEF(&body);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&header$$4);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&headers);
	ZVAL_UNDEF(&_9$$6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &url_param, &parameters, &headers_param);

	if (UNEXPECTED(Z_TYPE_P(url_param) != IS_STRING && Z_TYPE_P(url_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'url' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(url_param) == IS_STRING)) {
		zephir_get_strval(&url, url_param);
	} else {
		ZEPHIR_INIT_VAR(&url);
		ZVAL_EMPTY_STRING(&url);
	}
	if (!parameters) {
		parameters = &parameters_sub;
		ZEPHIR_CPY_WRT(parameters, &__$null);
	} else {
		ZEPHIR_SEPARATE_PARAM(parameters);
	}
	if (!headers_param) {
		ZEPHIR_INIT_VAR(&headers);
		array_init(&headers);
	} else {
	ZEPHIR_OBS_COPY_OR_DUP(&headers, headers_param);
	}


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setoptions", NULL, 7);
	zephir_check_call_status();
	if (Z_TYPE_P(parameters) == IS_ARRAY) {
		ZEPHIR_INIT_VAR(&_0$$3);
		zephir_json_encode(&_0$$3, parameters, 0 );
		ZEPHIR_CPY_WRT(parameters, &_0$$3);
		ZVAL_LONG(&_1$$3, 9);
		ZEPHIR_CALL_FUNCTION(&_2$$3, "gzdeflate", NULL, 8, parameters, &_1$$3);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(parameters, &_2$$3);
	}
	ZEPHIR_CALL_FUNCTION(&curl, "curl_init", NULL, 9, &url);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_LONG(&_3, 47);
	zephir_update_property_array(this_ptr, SL("options"), &_3, &__$true TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_4);
	ZVAL_LONG(&_4, 10015);
	zephir_update_property_array(this_ptr, SL("options"), &_4, parameters TSRMLS_CC);
	if (!(ZEPHIR_IS_EMPTY(&headers))) {
		zephir_is_iterable(&headers, 0, "plinker/lib/curl.zep", 78);
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&headers), _5$$4)
		{
			ZEPHIR_INIT_NVAR(&header$$4);
			ZVAL_COPY(&header$$4, _5$$4);
			zephir_update_property_array_multi(this_ptr, SL("options"), &header$$4 TSRMLS_CC, SL("la"), 2, 10023);
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&header$$4);
	}
	zephir_read_property(&_6, this_ptr, SL("options"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_FUNCTION(NULL, "curl_setopt_array", NULL, 10, &curl, &_6);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&body, "curl_exec", NULL, 11, &curl);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&_7, "curl_error", &_8, 12, &curl);
	zephir_check_call_status();
	if (zephir_is_true(&_7)) {
		ZEPHIR_INIT_VAR(&_9$$6);
		zephir_create_array(&_9$$6, 3, 0 TSRMLS_CC);
		zephir_array_update_string(&_9$$6, SL("url"), &url, PH_COPY | PH_SEPARATE);
		ZEPHIR_CALL_FUNCTION(&_10$$6, "curl_error", &_8, 12, &curl);
		zephir_check_call_status();
		zephir_array_update_string(&_9$$6, SL("error"), &_10$$6, PH_COPY | PH_SEPARATE);
		ZVAL_LONG(&_11$$6, 2097154);
		ZEPHIR_CALL_FUNCTION(&_10$$6, "curl_getinfo", NULL, 13, &curl, &_11$$6);
		zephir_check_call_status();
		zephir_array_update_string(&_9$$6, SL("code"), &_10$$6, PH_COPY | PH_SEPARATE);
		ZEPHIR_RETURN_CALL_FUNCTION("serialize", NULL, 14, &_9$$6);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_CALL_FUNCTION(NULL, "curl_close", NULL, 15, &curl);
	zephir_check_call_status();
	RETURN_CCTOR(&body);

}

