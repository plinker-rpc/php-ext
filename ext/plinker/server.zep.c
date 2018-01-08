
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
#include "kernel/string.h"
#include "kernel/fcall.h"
#include "kernel/exit.h"
#include "kernel/concat.h"


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

	zval _11$$3, _19$$4, _28$$6, _39$$8, _45$$9;
	zend_bool _7;
	zephir_fcall_cache_entry *_15 = NULL, *_49 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval __$true, *_SERVER, _0, _1, _2, _3, _4, _5, _6, _8, _9, _10, _16, _17, _18, _21, _24, _25, _26, _27, ns, action, _30, response, _31, _32, _33, _34, _51, _52, _53, _12$$3, _13$$3, _14$$3, _20$$4, _22$$5, _23$$5, _29$$6, _35$$7, _36$$7, _37$$7, _38$$7, src$$7, _41$$7, _42$$7, _43$$7, _44$$7, _47$$7, _48$$7, _50$$7, _40$$8, _46$$9;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_18);
	ZVAL_UNDEF(&_21);
	ZVAL_UNDEF(&_24);
	ZVAL_UNDEF(&_25);
	ZVAL_UNDEF(&_26);
	ZVAL_UNDEF(&_27);
	ZVAL_UNDEF(&ns);
	ZVAL_UNDEF(&action);
	ZVAL_UNDEF(&_30);
	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&_31);
	ZVAL_UNDEF(&_32);
	ZVAL_UNDEF(&_33);
	ZVAL_UNDEF(&_34);
	ZVAL_UNDEF(&_51);
	ZVAL_UNDEF(&_52);
	ZVAL_UNDEF(&_53);
	ZVAL_UNDEF(&_12$$3);
	ZVAL_UNDEF(&_13$$3);
	ZVAL_UNDEF(&_14$$3);
	ZVAL_UNDEF(&_20$$4);
	ZVAL_UNDEF(&_22$$5);
	ZVAL_UNDEF(&_23$$5);
	ZVAL_UNDEF(&_29$$6);
	ZVAL_UNDEF(&_35$$7);
	ZVAL_UNDEF(&_36$$7);
	ZVAL_UNDEF(&_37$$7);
	ZVAL_UNDEF(&_38$$7);
	ZVAL_UNDEF(&src$$7);
	ZVAL_UNDEF(&_41$$7);
	ZVAL_UNDEF(&_42$$7);
	ZVAL_UNDEF(&_43$$7);
	ZVAL_UNDEF(&_44$$7);
	ZVAL_UNDEF(&_47$$7);
	ZVAL_UNDEF(&_48$$7);
	ZVAL_UNDEF(&_50$$7);
	ZVAL_UNDEF(&_40$$8);
	ZVAL_UNDEF(&_46$$9);
	ZVAL_UNDEF(&_11$$3);
	ZVAL_UNDEF(&_19$$4);
	ZVAL_UNDEF(&_28$$6);
	ZVAL_UNDEF(&_39$$8);
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
	ZEPHIR_INIT_VAR(&_2);
	zephir_read_property(&_3, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
	zephir_json_decode(&_2, &_3, zephir_get_intval(&__$true) );
	zephir_update_property_zval(this_ptr, SL("post"), &_2);
	ZEPHIR_INIT_VAR(&_4);
	ZVAL_STRING(&_4, "Content-Type: text/plain; charset=utf-8");
	ZEPHIR_CALL_FUNCTION(NULL, "header", NULL, 28, &_4);
	zephir_check_call_status();
	zephir_read_property(&_5, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_string(&_6, &_5, SL("allowed_ips"), PH_NOISY | PH_READONLY, "plinker/server.zep", 63 TSRMLS_CC);
	_7 = !(ZEPHIR_IS_EMPTY(&_6));
	if (_7) {
		zephir_array_fetch_string(&_8, _SERVER, SL("REMOTE_ADDR"), PH_NOISY | PH_READONLY, "plinker/server.zep", 64 TSRMLS_CC);
		zephir_read_property(&_9, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_string(&_10, &_9, SL("allowed_ips"), PH_NOISY | PH_READONLY, "plinker/server.zep", 64 TSRMLS_CC);
		_7 = !(zephir_fast_in_array(&_8, &_10 TSRMLS_CC));
	}
	if (_7) {
		ZEPHIR_INIT_VAR(&_11$$3);
		zephir_create_array(&_11$$3, 2, 0 TSRMLS_CC);
		zephir_array_fetch_string(&_12$$3, _SERVER, SL("REMOTE_ADDR"), PH_NOISY | PH_READONLY, "plinker/server.zep", 66 TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_13$$3);
		ZEPHIR_CONCAT_SVS(&_13$$3, "IP not in allowed list (", &_12$$3, ")");
		zephir_array_update_string(&_11$$3, SL("error"), &_13$$3, PH_COPY | PH_SEPARATE);
		add_assoc_long_ex(&_11$$3, SL("code"), 403);
		ZEPHIR_CALL_FUNCTION(&_14$$3, "serialize", &_15, 17, &_11$$3);
		zephir_check_call_status();
		ZEPHIR_MM_RESTORE();
		zephir_exit(&_14$$3);
	}
	zephir_array_fetch_string(&_16, _SERVER, SL("HTTP_PLINKER"), PH_NOISY | PH_READONLY, "plinker/server.zep", 72 TSRMLS_CC);
	zephir_read_property(&_17, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_string(&_18, &_17, SL("token"), PH_NOISY | PH_READONLY, "plinker/server.zep", 72 TSRMLS_CC);
	if (!ZEPHIR_IS_EQUAL(&_16, &_18)) {
		ZEPHIR_INIT_VAR(&_19$$4);
		zephir_create_array(&_19$$4, 2, 0 TSRMLS_CC);
		add_assoc_stringl_ex(&_19$$4, SL("error"), SL("Plinker token mismatch"));
		add_assoc_long_ex(&_19$$4, SL("code"), 422);
		ZEPHIR_CALL_FUNCTION(&_20$$4, "serialize", &_15, 17, &_19$$4);
		zephir_check_call_status();
		ZEPHIR_MM_RESTORE();
		zephir_exit(&_20$$4);
	}
	ZEPHIR_OBS_VAR(&_21);
	zephir_read_property(&_21, this_ptr, SL("signer"), PH_NOISY_CC);
	if (!(zephir_is_true(&_21))) {
		ZEPHIR_INIT_VAR(&_22$$5);
		object_init_ex(&_22$$5, plinker_lib_signer_ce);
		zephir_read_property(&_23$$5, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(NULL, &_22$$5, "__construct", NULL, 2, &_23$$5);
		zephir_check_call_status();
		zephir_update_property_zval(this_ptr, SL("signer"), &_22$$5);
	}
	zephir_read_property(&_24, this_ptr, SL("signer"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_26, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_25, &_24, "decode", NULL, 0, &_26);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("post"), &_25);
	zephir_read_property(&_27, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_27) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_28$$6);
		zephir_create_array(&_28$$6, 2, 0 TSRMLS_CC);
		add_assoc_stringl_ex(&_28$$6, SL("error"), SL("Failed to decode payload, check secret"));
		add_assoc_long_ex(&_28$$6, SL("code"), 422);
		ZEPHIR_CALL_FUNCTION(&_29$$6, "serialize", &_15, 17, &_28$$6);
		zephir_check_call_status();
		ZEPHIR_MM_RESTORE();
		zephir_exit(&_29$$6);
	}
	zephir_read_property(&_30, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_OBS_VAR(&action);
	zephir_array_fetch_string(&action, &_30, SL("action"), PH_NOISY, "plinker/server.zep", 97 TSRMLS_CC);
	zephir_read_property(&_31, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_string(&_32, &_31, SL("component"), PH_NOISY | PH_READONLY, "plinker/server.zep", 101 TSRMLS_CC);
	zephir_read_property(&_33, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_string(&_34, &_33, SL("classes"), PH_NOISY | PH_READONLY, "plinker/server.zep", 101 TSRMLS_CC);
	if (zephir_array_key_exists(&_34, &_32 TSRMLS_CC)) {
		zephir_read_property(&_35$$7, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_string(&_36$$7, &_35$$7, SL("classes"), PH_NOISY | PH_READONLY, "plinker/server.zep", 103 TSRMLS_CC);
		ZEPHIR_OBS_VAR(&ns);
		zephir_read_property(&_37$$7, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_OBS_VAR(&_38$$7);
		zephir_array_fetch_string(&_38$$7, &_37$$7, SL("component"), PH_NOISY, "plinker/server.zep", 103 TSRMLS_CC);
		zephir_array_fetch(&ns, &_36$$7, &_38$$7, PH_NOISY, "plinker/server.zep", 103 TSRMLS_CC);
		if (!((zephir_file_exists(&ns TSRMLS_CC) == SUCCESS))) {
			ZEPHIR_INIT_VAR(&_39$$8);
			zephir_create_array(&_39$$8, 2, 0 TSRMLS_CC);
			add_assoc_stringl_ex(&_39$$8, SL("error"), SL("Component class not found"));
			add_assoc_long_ex(&_39$$8, SL("code"), 422);
			ZEPHIR_CALL_FUNCTION(&_40$$8, "serialize", &_15, 17, &_39$$8);
			zephir_check_call_status();
			ZEPHIR_MM_RESTORE();
			zephir_exit(&_40$$8);
		}
		ZEPHIR_INIT_VAR(&src$$7);
		zephir_file_get_contents(&src$$7, &ns TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_41$$7);
		ZEPHIR_INIT_VAR(&_42$$7);
		ZEPHIR_CONCAT_SV(&_42$$7, "?>", &src$$7);
		zephir_eval_php(&_42$$7, &_41$$7, "/home/lozza/php_inbuilt/plinker/plinker/server.zep:115" TSRMLS_CC);
		zephir_read_property(&_43$$7, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_string(&_44$$7, &_43$$7, SL("component"), PH_NOISY | PH_READONLY, "plinker/server.zep", 118 TSRMLS_CC);
		if (!(zephir_class_exists(&_44$$7, 1 TSRMLS_CC))) {
			ZEPHIR_INIT_VAR(&_45$$9);
			zephir_create_array(&_45$$9, 2, 0 TSRMLS_CC);
			add_assoc_stringl_ex(&_45$$9, SL("error"), SL("Component class name invalid"));
			add_assoc_long_ex(&_45$$9, SL("code"), 422);
			ZEPHIR_CALL_FUNCTION(&_46$$9, "serialize", &_15, 17, &_45$$9);
			zephir_check_call_status();
			ZEPHIR_MM_RESTORE();
			zephir_exit(&_46$$9);
		}
		zephir_read_property(&_47$$7, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_string(&_48$$7, &_47$$7, SL("component"), PH_NOISY | PH_READONLY, "plinker/server.zep", 126 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&response, this_ptr, "execute", &_49, 29, &_48$$7, &action);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(&_50$$7, "serialize", &_15, 17, &response);
		zephir_check_call_status();
		ZEPHIR_MM_RESTORE();
		zephir_exit(&_50$$7);
	}
	zephir_read_property(&_51, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_string(&_52, &_51, SL("component"), PH_NOISY | PH_READONLY, "plinker/server.zep", 132 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(&ns);
	ZEPHIR_CONCAT_SV(&ns, "\\Plinker\\Endpoint\\", &_52);
	if (zephir_class_exists(&ns, 1 TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(&response, this_ptr, "execute", &_49, 29, &ns, &action);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(&response);
		ZVAL_STRING(&response, "Component not implemented");
	}
	ZEPHIR_CALL_FUNCTION(&_53, "serialize", &_15, 17, &response);
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

