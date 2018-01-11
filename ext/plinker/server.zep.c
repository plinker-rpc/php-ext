
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
#include "kernel/file.h"
#include "kernel/fcall.h"
#include "kernel/string.h"
#include "kernel/exit.h"
#include "kernel/concat.h"
#include "kernel/require.h"


ZEPHIR_INIT_CLASS(Plinker_Server) {

	ZEPHIR_REGISTER_CLASS(Plinker, Server, plinker, server, plinker_server_method_entry, ZEND_ACC_FINAL_CLASS);

	zend_declare_property_null(plinker_server_ce, SL("post"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(plinker_server_ce, SL("signer"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(plinker_server_ce, SL("config"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

/**
 *
 */
PHP_METHOD(Plinker_Server, __construct) {

	zend_bool _4;
	zval *config_param = NULL, __$null, _0, _2, _3, _5, _6, _7$$3, _8$$3;
	zval config, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&config);
	ZVAL_UNDEF(&_1);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_8$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &config_param);

	if (!config_param) {
		ZEPHIR_INIT_VAR(&config);
		array_init(&config);
	} else {
	ZEPHIR_OBS_COPY_OR_DUP(&config, config_param);
	}


	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_INIT_VAR(&_1);
	zephir_create_array(&_1, 3, 0 TSRMLS_CC);
	zephir_array_update_string(&_1, SL("secret"), &__$null, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_VAR(&_2);
	array_init(&_2);
	zephir_array_update_string(&_1, SL("allowed_ips"), &_2, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&_1, SL("endpoint"), &__$null, PH_COPY | PH_SEPARATE);
	zephir_fast_array_merge(&_0, &_1, &config TSRMLS_CC);
	zephir_update_property_zval(this_ptr, SL("config"), &_0);
	zephir_read_property(&_3, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
	_4 = !(zephir_array_isset_string(&_3, SL("timeout")));
	if (!(_4)) {
		zephir_read_property(&_5, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_string(&_6, &_5, SL("timeout"), PH_NOISY | PH_READONLY, "plinker/server.zep", 47 TSRMLS_CC);
		_4 = !(zephir_is_numeric(&_6));
	}
	if (_4) {
		ZEPHIR_INIT_VAR(&_7$$3);
		ZVAL_STRING(&_7$$3, "timeout");
		ZEPHIR_INIT_VAR(&_8$$3);
		ZVAL_LONG(&_8$$3, 10);
		zephir_update_property_array(this_ptr, SL("config"), &_7$$3, &_8$$3 TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 *
 */
PHP_METHOD(Plinker_Server, listen) {

	zval _13$$3, _21$$4, _30$$6, _41$$8, _45$$9;
	zend_bool _9;
	zephir_fcall_cache_entry *_17 = NULL, *_49 = NULL;
	zval __$true, *_SERVER, _0, _1, _2, _3, _4, _5, _6, _7, _8, _10, _11, _12, _18, _19, _20, _23, _26, _27, _28, _29, ns, action, _32, response, _33, _34, _35, _36, _51, _52, _53, _14$$3, _15$$3, _16$$3, _22$$4, _24$$5, _25$$5, _31$$6, _37$$7, _38$$7, _39$$7, _40$$7, _43$$7, _44$$7, _47$$7, _48$$7, _50$$7, _42$$8, _46$$9;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_18);
	ZVAL_UNDEF(&_19);
	ZVAL_UNDEF(&_20);
	ZVAL_UNDEF(&_23);
	ZVAL_UNDEF(&_26);
	ZVAL_UNDEF(&_27);
	ZVAL_UNDEF(&_28);
	ZVAL_UNDEF(&_29);
	ZVAL_UNDEF(&ns);
	ZVAL_UNDEF(&action);
	ZVAL_UNDEF(&_32);
	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&_33);
	ZVAL_UNDEF(&_34);
	ZVAL_UNDEF(&_35);
	ZVAL_UNDEF(&_36);
	ZVAL_UNDEF(&_51);
	ZVAL_UNDEF(&_52);
	ZVAL_UNDEF(&_53);
	ZVAL_UNDEF(&_14$$3);
	ZVAL_UNDEF(&_15$$3);
	ZVAL_UNDEF(&_16$$3);
	ZVAL_UNDEF(&_22$$4);
	ZVAL_UNDEF(&_24$$5);
	ZVAL_UNDEF(&_25$$5);
	ZVAL_UNDEF(&_31$$6);
	ZVAL_UNDEF(&_37$$7);
	ZVAL_UNDEF(&_38$$7);
	ZVAL_UNDEF(&_39$$7);
	ZVAL_UNDEF(&_40$$7);
	ZVAL_UNDEF(&_43$$7);
	ZVAL_UNDEF(&_44$$7);
	ZVAL_UNDEF(&_47$$7);
	ZVAL_UNDEF(&_48$$7);
	ZVAL_UNDEF(&_50$$7);
	ZVAL_UNDEF(&_42$$8);
	ZVAL_UNDEF(&_46$$9);
	ZVAL_UNDEF(&_13$$3);
	ZVAL_UNDEF(&_21$$4);
	ZVAL_UNDEF(&_30$$6);
	ZVAL_UNDEF(&_41$$8);
	ZVAL_UNDEF(&_45$$9);

	ZEPHIR_MM_GROW();
	zephir_get_global(&_SERVER, SL("_SERVER"));
	if (!_SERVER) {
		ZEPHIR_THROW_EXCEPTION_STR(zend_exception_get_default(), "Invalid superglobal");
		return;
	}

	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "php://input");
	zephir_file_get_contents(&_0, &_1 TSRMLS_CC);
	zephir_update_property_zval(this_ptr, SL("post"), &_0);
	zephir_read_property(&_2, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_FUNCTION(&_3, "gzinflate", NULL, 26, &_2);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("post"), &_3);
	ZEPHIR_INIT_VAR(&_4);
	zephir_read_property(&_5, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
	zephir_json_decode(&_4, &_5, zephir_get_intval(&__$true) );
	zephir_update_property_zval(this_ptr, SL("post"), &_4);
	ZEPHIR_INIT_VAR(&_6);
	ZVAL_STRING(&_6, "Content-Type: text/plain; charset=utf-8");
	ZEPHIR_CALL_FUNCTION(NULL, "header", NULL, 27, &_6);
	zephir_check_call_status();
	zephir_read_property(&_7, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_string(&_8, &_7, SL("allowed_ips"), PH_NOISY | PH_READONLY, "plinker/server.zep", 64 TSRMLS_CC);
	_9 = !(ZEPHIR_IS_EMPTY(&_8));
	if (_9) {
		zephir_array_fetch_string(&_10, _SERVER, SL("REMOTE_ADDR"), PH_NOISY | PH_READONLY, "plinker/server.zep", 65 TSRMLS_CC);
		zephir_read_property(&_11, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_string(&_12, &_11, SL("allowed_ips"), PH_NOISY | PH_READONLY, "plinker/server.zep", 65 TSRMLS_CC);
		_9 = !(zephir_fast_in_array(&_10, &_12 TSRMLS_CC));
	}
	if (_9) {
		ZEPHIR_INIT_VAR(&_13$$3);
		zephir_create_array(&_13$$3, 2, 0 TSRMLS_CC);
		zephir_array_fetch_string(&_14$$3, _SERVER, SL("REMOTE_ADDR"), PH_NOISY | PH_READONLY, "plinker/server.zep", 67 TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_15$$3);
		ZEPHIR_CONCAT_SVS(&_15$$3, "IP not in allowed list (", &_14$$3, ")");
		zephir_array_update_string(&_13$$3, SL("error"), &_15$$3, PH_COPY | PH_SEPARATE);
		add_assoc_long_ex(&_13$$3, SL("code"), 403);
		ZEPHIR_CALL_FUNCTION(&_16$$3, "serialize", &_17, 14, &_13$$3);
		zephir_check_call_status();
		ZEPHIR_MM_RESTORE();
		zephir_exit(&_16$$3);
	}
	zephir_array_fetch_string(&_18, _SERVER, SL("HTTP_PLINKER"), PH_NOISY | PH_READONLY, "plinker/server.zep", 73 TSRMLS_CC);
	zephir_read_property(&_19, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_string(&_20, &_19, SL("token"), PH_NOISY | PH_READONLY, "plinker/server.zep", 73 TSRMLS_CC);
	if (!ZEPHIR_IS_EQUAL(&_18, &_20)) {
		ZEPHIR_INIT_VAR(&_21$$4);
		zephir_create_array(&_21$$4, 2, 0 TSRMLS_CC);
		add_assoc_stringl_ex(&_21$$4, SL("error"), SL("Plinker token mismatch"));
		add_assoc_long_ex(&_21$$4, SL("code"), 422);
		ZEPHIR_CALL_FUNCTION(&_22$$4, "serialize", &_17, 14, &_21$$4);
		zephir_check_call_status();
		ZEPHIR_MM_RESTORE();
		zephir_exit(&_22$$4);
	}
	ZEPHIR_OBS_VAR(&_23);
	zephir_read_property(&_23, this_ptr, SL("signer"), PH_NOISY_CC);
	if (!(zephir_is_true(&_23))) {
		ZEPHIR_INIT_VAR(&_24$$5);
		object_init_ex(&_24$$5, plinker_lib_signer_ce);
		zephir_read_property(&_25$$5, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(NULL, &_24$$5, "__construct", NULL, 2, &_25$$5);
		zephir_check_call_status();
		zephir_update_property_zval(this_ptr, SL("signer"), &_24$$5);
	}
	zephir_read_property(&_26, this_ptr, SL("signer"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_28, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_27, &_26, "decode", NULL, 0, &_28);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("post"), &_27);
	zephir_read_property(&_29, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_29) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_30$$6);
		zephir_create_array(&_30$$6, 2, 0 TSRMLS_CC);
		add_assoc_stringl_ex(&_30$$6, SL("error"), SL("Failed to decode payload, check secret"));
		add_assoc_long_ex(&_30$$6, SL("code"), 422);
		ZEPHIR_CALL_FUNCTION(&_31$$6, "serialize", &_17, 14, &_30$$6);
		zephir_check_call_status();
		ZEPHIR_MM_RESTORE();
		zephir_exit(&_31$$6);
	}
	zephir_read_property(&_32, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_OBS_VAR(&action);
	zephir_array_fetch_string(&action, &_32, SL("action"), PH_NOISY, "plinker/server.zep", 98 TSRMLS_CC);
	zephir_read_property(&_33, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_string(&_34, &_33, SL("component"), PH_NOISY | PH_READONLY, "plinker/server.zep", 102 TSRMLS_CC);
	zephir_read_property(&_35, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_string(&_36, &_35, SL("classes"), PH_NOISY | PH_READONLY, "plinker/server.zep", 102 TSRMLS_CC);
	if (zephir_array_key_exists(&_36, &_34 TSRMLS_CC)) {
		zephir_read_property(&_37$$7, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_string(&_38$$7, &_37$$7, SL("classes"), PH_NOISY | PH_READONLY, "plinker/server.zep", 104 TSRMLS_CC);
		ZEPHIR_OBS_VAR(&ns);
		zephir_read_property(&_39$$7, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_OBS_VAR(&_40$$7);
		zephir_array_fetch_string(&_40$$7, &_39$$7, SL("component"), PH_NOISY, "plinker/server.zep", 104 TSRMLS_CC);
		zephir_array_fetch(&ns, &_38$$7, &_40$$7, PH_NOISY, "plinker/server.zep", 104 TSRMLS_CC);
		if (!((zephir_file_exists(&ns TSRMLS_CC) == SUCCESS))) {
			ZEPHIR_INIT_VAR(&_41$$8);
			zephir_create_array(&_41$$8, 2, 0 TSRMLS_CC);
			add_assoc_stringl_ex(&_41$$8, SL("error"), SL("Component class not found"));
			add_assoc_long_ex(&_41$$8, SL("code"), 422);
			ZEPHIR_CALL_FUNCTION(&_42$$8, "serialize", &_17, 14, &_41$$8);
			zephir_check_call_status();
			ZEPHIR_MM_RESTORE();
			zephir_exit(&_42$$8);
		}
		if (zephir_require_zval(&ns TSRMLS_CC) == FAILURE) {
			RETURN_MM_NULL();
		}
		zephir_read_property(&_43$$7, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_string(&_44$$7, &_43$$7, SL("component"), PH_NOISY | PH_READONLY, "plinker/server.zep", 118 TSRMLS_CC);
		if (!(zephir_class_exists(&_44$$7, 1 TSRMLS_CC))) {
			ZEPHIR_INIT_VAR(&_45$$9);
			zephir_create_array(&_45$$9, 2, 0 TSRMLS_CC);
			add_assoc_stringl_ex(&_45$$9, SL("error"), SL("Component class name invalid"));
			add_assoc_long_ex(&_45$$9, SL("code"), 422);
			ZEPHIR_CALL_FUNCTION(&_46$$9, "serialize", &_17, 14, &_45$$9);
			zephir_check_call_status();
			ZEPHIR_MM_RESTORE();
			zephir_exit(&_46$$9);
		}
		zephir_read_property(&_47$$7, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_string(&_48$$7, &_47$$7, SL("component"), PH_NOISY | PH_READONLY, "plinker/server.zep", 126 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&response, this_ptr, "execute", &_49, 28, &_48$$7, &action);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(&_50$$7, "serialize", &_17, 14, &response);
		zephir_check_call_status();
		ZEPHIR_MM_RESTORE();
		zephir_exit(&_50$$7);
	}
	zephir_read_property(&_51, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_string(&_52, &_51, SL("component"), PH_NOISY | PH_READONLY, "plinker/server.zep", 132 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(&ns);
	ZEPHIR_CONCAT_SV(&ns, "\\Plinker\\Endpoint\\", &_52);
	if (zephir_class_exists(&ns, 1 TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(&response, this_ptr, "execute", &_49, 28, &ns, &action);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(&response);
		ZVAL_STRING(&response, "Component not implemented");
	}
	ZEPHIR_CALL_FUNCTION(&_53, "serialize", &_17, 14, &response);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
	zephir_exit(&_53);
	ZEPHIR_MM_RESTORE();

}

/**
 *
 */
PHP_METHOD(Plinker_Server, execute) {

	zval _5$$3;
	zend_class_entry *_1;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *ns, ns_sub, *action, action_sub, response, component, _0, _2, _3, _4, _6$$3, _7$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ns_sub);
	ZVAL_UNDEF(&action_sub);
	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&component);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_5$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &ns, &action);



	ZEPHIR_INIT_VAR(&response);
	ZVAL_NULL(&response);
	ZEPHIR_INIT_VAR(&component);
	zephir_fetch_safe_class(&_0, ns);
	_1 = zephir_fetch_class_str_ex(Z_STRVAL_P(&_0), Z_STRLEN_P(&_0), ZEND_FETCH_CLASS_AUTO);
	object_init_ex(&component, _1);
	if (zephir_has_constructor(&component TSRMLS_CC)) {
		zephir_read_property(&_2, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
		zephir_read_property(&_3, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_4);
		zephir_add_function(&_4, &_2, &_3);
		ZEPHIR_CALL_METHOD(NULL, &component, "__construct", NULL, 0, &_4);
		zephir_check_call_status();
	}
	if ((zephir_method_exists(&component, action TSRMLS_CC)  == SUCCESS)) {
		ZEPHIR_INIT_VAR(&_5$$3);
		zephir_create_array(&_5$$3, 2, 0 TSRMLS_CC);
		zephir_array_fast_append(&_5$$3, &component);
		zephir_array_fast_append(&_5$$3, action);
		zephir_read_property(&_6$$3, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_string(&_7$$3, &_6$$3, SL("params"), PH_NOISY | PH_READONLY, "plinker/server.zep", 159 TSRMLS_CC);
		ZEPHIR_INIT_NVAR(&response);
		ZEPHIR_CALL_USER_FUNC_ARRAY(&response, &_5$$3, &_7$$3);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(&response);
		ZEPHIR_CONCAT_SVSV(&response, "Component action (", action, ") not implemented in: ", ns);
	}
	RETURN_CCTOR(&response);

}

