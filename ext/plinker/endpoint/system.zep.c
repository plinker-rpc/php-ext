
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
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
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

	zval *config_param = NULL;
	zval config;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&config);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &config_param);

	ZEPHIR_OBS_COPY_OR_DUP(&config, config_param);



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


	ZEPHIR_CALL_FUNCTION(&ds, "disk_total_space", NULL, 5, &path);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&df, "disk_free_space", NULL, 6, &path);
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


	ZEPHIR_RETURN_CALL_FUNCTION("disk_total_space", NULL, 5, &path);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Get current user
 *
 * @return string
 */
PHP_METHOD(Plinker_Endpoint_System, whoami) {

	zval _0;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "whoami");
	ZEPHIR_RETURN_CALL_FUNCTION("shell_exec", NULL, 7, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Execute command
 *
 * @return string
 */
PHP_METHOD(Plinker_Endpoint_System, exec) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *cmd_param = NULL;
	zval cmd;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&cmd);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &cmd_param);

	if (UNEXPECTED(Z_TYPE_P(cmd_param) != IS_STRING && Z_TYPE_P(cmd_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'cmd' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(cmd_param) == IS_STRING)) {
		zephir_get_strval(&cmd, cmd_param);
	} else {
		ZEPHIR_INIT_VAR(&cmd);
		ZVAL_EMPTY_STRING(&cmd);
	}


	ZEPHIR_RETURN_CALL_FUNCTION("shell_exec", NULL, 7, &cmd);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Execute command
 *
 * @return string
 */
PHP_METHOD(Plinker_Endpoint_System, test) {

	zval *this_ptr = getThis();


	RETURN_STRING("tesing");

}

