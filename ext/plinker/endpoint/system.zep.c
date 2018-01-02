
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
#include "kernel/memory.h"
#include "kernel/string.h"
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/operators.h"
#include "kernel/math.h"


/**
 * Lxd\Endpoints\Images
 *
 * Provides image facilities to the API
 * @see https://github.com/lxc-systems/lxd/blob/master/lxd/endpoints/images.zep
 */
ZEPHIR_INIT_CLASS(Plinker_Endpoint_System) {

	ZEPHIR_REGISTER_CLASS(Plinker\\Endpoint, System, plinker, endpoint_system, plinker_endpoint_system_method_entry, ZEND_ACC_FINAL_CLASS);

	zend_declare_property_null(plinker_endpoint_system_ce, SL("host_os"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

/**
 * Class construct.
 *
 * @param  array          config Config array which holds object configuration
 * @param  <Lxd\Lib\Curl> curl
 * @return void
 */
PHP_METHOD(Plinker_Endpoint_System, __construct) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *config_param = NULL, __$true, _0, _1, _2, _3, _4;
	zval config;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&config);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &config_param);

	ZEPHIR_OBS_COPY_OR_DUP(&config, config_param);


	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_CALL_FUNCTION(&_2, "php_uname", NULL, 5);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, " ");
	ZEPHIR_CALL_FUNCTION(&_4, "strstr", NULL, 6, &_2, &_3, &__$true);
	zephir_check_call_status();
	zephir_fast_strtoupper(&_1, &_4);
	zephir_fast_trim(&_0, &_1, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
	zephir_update_property_zval(this_ptr, SL("host_os"), &_0);
	ZEPHIR_MM_RESTORE();

}

/**
 * Get diskspace
 *
 * @param  string $path
 * @return int
 */
PHP_METHOD(Plinker_Endpoint_System, disk_space) {

	zend_bool _1, _2;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *path_param = NULL, ds, df, _0, _3, _4;
	zval path;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&path);
	ZVAL_UNDEF(&ds);
	ZVAL_UNDEF(&df);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &path_param);

	if (!path_param) {
		ZEPHIR_INIT_VAR(&path);
		ZVAL_STRING(&path, "/");
	} else {
	if (UNEXPECTED(Z_TYPE_P(path_param) != IS_STRING && Z_TYPE_P(path_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'path' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(path_param) == IS_STRING)) {
		zephir_get_strval(&path, path_param);
	} else {
		ZEPHIR_INIT_VAR(&path);
		ZVAL_EMPTY_STRING(&path);
	}
	}


	ZEPHIR_CALL_FUNCTION(&ds, "disk_total_space", NULL, 7, &path);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&df, "disk_free_space", NULL, 8, &path);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_0);
	_1 = ZEPHIR_GT_LONG(&df, 0);
	if (_1) {
		_1 = ZEPHIR_GT_LONG(&ds, 0);
	}
	_2 = _1;
	if (_2) {
		_2 = ZEPHIR_LT(&df, &ds);
	}
	if (_2) {
		ZEPHIR_SINIT_VAR(_3);
		div_function(&_3, &df, &ds TSRMLS_CC);
		ZVAL_LONG(&_4, (zephir_get_numberval(&_3) * 100));
		ZVAL_DOUBLE(&_0, zephir_floor(&_4 TSRMLS_CC));
	} else {
		ZVAL_LONG(&_0, 0);
	}
	RETURN_CCTOR(&_0);

}

/**
 * Get total diskspace
 *
 * @param  string $path
 * @return int
 */
PHP_METHOD(Plinker_Endpoint_System, total_disk_space) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *path_param = NULL;
	zval path;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&path);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &path_param);

	if (!path_param) {
		ZEPHIR_INIT_VAR(&path);
		ZVAL_STRING(&path, "/");
	} else {
	if (UNEXPECTED(Z_TYPE_P(path_param) != IS_STRING && Z_TYPE_P(path_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'path' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(path_param) == IS_STRING)) {
		zephir_get_strval(&path, path_param);
	} else {
		ZEPHIR_INIT_VAR(&path);
		ZVAL_EMPTY_STRING(&path);
	}
	}


	ZEPHIR_RETURN_CALL_FUNCTION("disk_total_space", NULL, 7, &path);
	zephir_check_call_status();
	RETURN_MM();

}

