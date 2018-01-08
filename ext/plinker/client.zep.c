
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/memory.h"
#include "kernel/array.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/fcall.h"
#include "kernel/concat.h"


ZEPHIR_INIT_CLASS(Plinker_Client) {

	ZEPHIR_REGISTER_CLASS(Plinker, Client, plinker, client, plinker_client_method_entry, ZEND_ACC_FINAL_CLASS);

	zend_declare_property_null(plinker_client_ce, SL("component"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(plinker_client_ce, SL("response"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(plinker_client_ce, SL("config"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(plinker_client_ce, SL("curl"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(plinker_client_ce, SL("signer"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

/**
 *
 */
PHP_METHOD(Plinker_Client, __construct) {

	zend_bool _3;
	zval config, _1;
	zval *server_param = NULL, *config_param = NULL, __$null, _0, _2, _4, _5, _6$$3, _7$$3;
	zval server;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&server);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&config);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &server_param, &config_param);

	if (UNEXPECTED(Z_TYPE_P(server_param) != IS_STRING && Z_TYPE_P(server_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'server' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(server_param) == IS_STRING)) {
		zephir_get_strval(&server, server_param);
	} else {
		ZEPHIR_INIT_VAR(&server);
		ZVAL_EMPTY_STRING(&server);
	}
	if (!config_param) {
		ZEPHIR_INIT_VAR(&config);
		array_init(&config);
	} else {
		zephir_get_arrval(&config, config_param);
	}


	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_INIT_VAR(&_1);
	zephir_create_array(&_1, 2, 0 TSRMLS_CC);
	zephir_array_update_string(&_1, SL("server"), &server, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&_1, SL("secret"), &__$null, PH_COPY | PH_SEPARATE);
	zephir_fast_array_merge(&_0, &_1, &config TSRMLS_CC);
	zephir_update_property_zval(this_ptr, SL("config"), &_0);
	zephir_read_property(&_2, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
	_3 = !(zephir_array_isset_string(&_2, SL("timeout")));
	if (!(_3)) {
		zephir_read_property(&_4, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_string(&_5, &_4, SL("timeout"), PH_NOISY | PH_READONLY, "plinker/client.zep", 50 TSRMLS_CC);
		_3 = !(zephir_is_numeric(&_5));
	}
	if (_3) {
		ZEPHIR_INIT_VAR(&_6$$3);
		ZVAL_STRING(&_6$$3, "timeout");
		ZEPHIR_INIT_VAR(&_7$$3);
		ZVAL_LONG(&_7$$3, 10);
		zephir_update_property_array(this_ptr, SL("config"), &_6$$3, &_7$$3 TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 *
 */
PHP_METHOD(Plinker_Client, __get) {

	zval *method_param = NULL;
	zval method;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&method);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &method_param);

	if (UNEXPECTED(Z_TYPE_P(method_param) != IS_STRING && Z_TYPE_P(method_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'method' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(method_param) == IS_STRING)) {
		zephir_get_strval(&method, method_param);
	} else {
		ZEPHIR_INIT_VAR(&method);
		ZVAL_EMPTY_STRING(&method);
	}


	zephir_update_property_zval(this_ptr, SL("component"), &method);
	RETURN_THIS();

}

/**
 * Magic caller
 *
 * @param string $action
 * @param array  $params
 */
PHP_METHOD(Plinker_Client, __call) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval params, _8, _14;
	zval *action_param = NULL, *params_param = NULL, _0, _3, _6, payload, _7, _9, _10, _11, _12, _13, _15, _16, _17, _1$$5, _2$$5, _4$$6, _5$$6;
	zval action;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&action);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&payload);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_1$$5);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_14);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &action_param, &params_param);

	if (UNEXPECTED(Z_TYPE_P(action_param) != IS_STRING && Z_TYPE_P(action_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'action' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(action_param) == IS_STRING)) {
		zephir_get_strval(&action, action_param);
	} else {
		ZEPHIR_INIT_VAR(&action);
		ZVAL_EMPTY_STRING(&action);
	}
	ZEPHIR_OBS_COPY_OR_DUP(&params, params_param);


	if (!(zephir_is_scalar(&action))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(zend_exception_get_default(TSRMLS_C), "Method name has no scalar value", "plinker/client.zep", 74);
		return;
	}
	if (!(Z_TYPE_P(&params) == IS_ARRAY)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(zend_exception_get_default(TSRMLS_C), "Params must be given as array", "plinker/client.zep", 78);
		return;
	}
	ZEPHIR_OBS_VAR(&_0);
	zephir_read_property(&_0, this_ptr, SL("curl"), PH_NOISY_CC);
	if (!(zephir_is_true(&_0))) {
		ZEPHIR_INIT_VAR(&_1$$5);
		object_init_ex(&_1$$5, plinker_lib_curl_ce);
		zephir_read_property(&_2$$5, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(NULL, &_1$$5, "__construct", NULL, 1, &_2$$5);
		zephir_check_call_status();
		zephir_update_property_zval(this_ptr, SL("curl"), &_1$$5);
	}
	ZEPHIR_OBS_VAR(&_3);
	zephir_read_property(&_3, this_ptr, SL("signer"), PH_NOISY_CC);
	if (!(zephir_is_true(&_3))) {
		ZEPHIR_INIT_VAR(&_4$$6);
		object_init_ex(&_4$$6, plinker_lib_signer_ce);
		zephir_read_property(&_5$$6, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(NULL, &_4$$6, "__construct", NULL, 2, &_5$$6);
		zephir_check_call_status();
		zephir_update_property_zval(this_ptr, SL("signer"), &_4$$6);
	}
	ZEPHIR_CALL_FUNCTION(&_6, "array_values", NULL, 3, &params);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&params, &_6);
	zephir_read_property(&_7, this_ptr, SL("signer"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_8);
	zephir_create_array(&_8, 4, 0 TSRMLS_CC);
	ZEPHIR_OBS_VAR(&_9);
	zephir_read_property(&_9, this_ptr, SL("component"), PH_NOISY_CC);
	zephir_array_update_string(&_8, SL("component"), &_9, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_9);
	zephir_read_property(&_9, this_ptr, SL("config"), PH_NOISY_CC);
	zephir_array_update_string(&_8, SL("config"), &_9, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&_8, SL("action"), &action, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&_8, SL("params"), &params, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_METHOD(&payload, &_7, "encode", NULL, 0, &_8);
	zephir_check_call_status();
	zephir_read_property(&_10, this_ptr, SL("curl"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_12, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_string(&_13, &_12, SL("server"), PH_NOISY | PH_READONLY, "plinker/client.zep", 104 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_14);
	zephir_create_array(&_14, 1, 0 TSRMLS_CC);
	zephir_array_fetch_string(&_15, &payload, SL("token"), PH_NOISY | PH_READONLY, "plinker/client.zep", 106 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_16);
	ZEPHIR_CONCAT_SV(&_16, "PLINKER: ", &_15);
	zephir_array_fast_append(&_14, &_16);
	ZEPHIR_CALL_METHOD(&_11, &_10, "post", NULL, 0, &_13, &payload, &_14);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("response"), &_11);
	zephir_read_property(&_17, this_ptr, SL("response"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_FUNCTION("unserialize", NULL, 4, &_17);
	zephir_check_call_status();
	RETURN_MM();

}

