
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
#include "kernel/require.h"
#include "kernel/concat.h"


ZEPHIR_INIT_CLASS(Plinker_Server) {

	ZEPHIR_REGISTER_CLASS(Plinker, Server, plinker, server, plinker_server_method_entry, ZEND_ACC_FINAL_CLASS);

	/**
	 * @var
	 */
	zend_declare_property_null(plinker_server_ce, SL("post"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var
	 */
	zend_declare_property_null(plinker_server_ce, SL("config"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var
	 */
	zend_declare_property_null(plinker_server_ce, SL("signer"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @const - error strings
	 */
	zephir_declare_class_constant_string(plinker_server_ce, SL("ERROR_IP"), "IP not in allowed list (%s)");

	zephir_declare_class_constant_string(plinker_server_ce, SL("ERROR_TOKEN"), "Plinker token mismatch");

	zephir_declare_class_constant_string(plinker_server_ce, SL("ERROR_DECODE"), "Failed to decode payload, check secret");

	zephir_declare_class_constant_string(plinker_server_ce, SL("ERROR_USR_COMPONENT"), "User component class (%s) not found");

	zephir_declare_class_constant_string(plinker_server_ce, SL("ERROR_EXT_COMPONENT"), "Component (%s) not implemented");

	zephir_declare_class_constant_string(plinker_server_ce, SL("ERROR_ACTION"), "Component action (%s) not implemented in: %s");

	return SUCCESS;

}

/**
 * Class construct
 *
 * @param  array          config config array which holds object configuration
 * @return void
 */
PHP_METHOD(Plinker_Server, __construct) {

	zend_bool _4;
	zval *config_param = NULL, __$false, __$null, _0, _2, _3, _5, _6, _7$$3, _8$$3;
	zval config, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&config);
	ZVAL_UNDEF(&_1);
	ZVAL_BOOL(&__$false, 0);
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
	zephir_array_update_string(&_1, SL("debug"), &__$false, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&_1, SL("secret"), &__$null, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_VAR(&_2);
	array_init(&_2);
	zephir_array_update_string(&_1, SL("allowed_ips"), &_2, PH_COPY | PH_SEPARATE);
	zephir_fast_array_merge(&_0, &_1, &config TSRMLS_CC);
	zephir_update_property_zval(this_ptr, SL("config"), &_0);
	zephir_read_property(&_3, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
	_4 = !(zephir_array_isset_string(&_3, SL("timeout")));
	if (!(_4)) {
		zephir_read_property(&_5, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_string(&_6, &_5, SL("timeout"), PH_NOISY | PH_READONLY, "plinker/server.zep", 69 TSRMLS_CC);
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
 * Listen method
 *
 * <code>
 *  $server->listen();
 * </code>
 *
 * @return void
 */
PHP_METHOD(Plinker_Server, listen) {

	zval _13$$3, _22$$4, _31$$6, _66$$10, _73$$11;
	zend_bool _9, _65$$7;
	zephir_fcall_cache_entry *_17 = NULL, *_18 = NULL, *_80 = NULL;
	zval __$true, *_SERVER, _0, _1, _2, _3, _4, _5, _6, _7, _8, _10, _11, _12, _19, _20, _21, _24, _27, _28, _29, _30, response, ns, action, _33, _34, _35, _36, _37, _38, _39, _82, _83, _87, _14$$3, _15$$3, _16$$3, _23$$4, _25$$5, _26$$5, _32$$6, _40$$7, _41$$7, _42$$7, _43$$7, _44$$7, _45$$7, _51$$7, _52$$7, _53$$7, _54$$7, _55$$7, _56$$7, _71$$7, _72$$7, _78$$7, _79$$7, _81$$7, _46$$8, _47$$8, _48$$8, _49$$8, _50$$8, _57$$9, _58$$9, _59$$9, _60$$9, _61$$9, _62$$9, _63$$9, _64$$9, _67$$10, _68$$10, _69$$10, _70$$10, _74$$11, _75$$11, _76$$11, _77$$11, _84$$13, _85$$13, _86$$13;
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
	ZVAL_UNDEF(&_19);
	ZVAL_UNDEF(&_20);
	ZVAL_UNDEF(&_21);
	ZVAL_UNDEF(&_24);
	ZVAL_UNDEF(&_27);
	ZVAL_UNDEF(&_28);
	ZVAL_UNDEF(&_29);
	ZVAL_UNDEF(&_30);
	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&ns);
	ZVAL_UNDEF(&action);
	ZVAL_UNDEF(&_33);
	ZVAL_UNDEF(&_34);
	ZVAL_UNDEF(&_35);
	ZVAL_UNDEF(&_36);
	ZVAL_UNDEF(&_37);
	ZVAL_UNDEF(&_38);
	ZVAL_UNDEF(&_39);
	ZVAL_UNDEF(&_82);
	ZVAL_UNDEF(&_83);
	ZVAL_UNDEF(&_87);
	ZVAL_UNDEF(&_14$$3);
	ZVAL_UNDEF(&_15$$3);
	ZVAL_UNDEF(&_16$$3);
	ZVAL_UNDEF(&_23$$4);
	ZVAL_UNDEF(&_25$$5);
	ZVAL_UNDEF(&_26$$5);
	ZVAL_UNDEF(&_32$$6);
	ZVAL_UNDEF(&_40$$7);
	ZVAL_UNDEF(&_41$$7);
	ZVAL_UNDEF(&_42$$7);
	ZVAL_UNDEF(&_43$$7);
	ZVAL_UNDEF(&_44$$7);
	ZVAL_UNDEF(&_45$$7);
	ZVAL_UNDEF(&_51$$7);
	ZVAL_UNDEF(&_52$$7);
	ZVAL_UNDEF(&_53$$7);
	ZVAL_UNDEF(&_54$$7);
	ZVAL_UNDEF(&_55$$7);
	ZVAL_UNDEF(&_56$$7);
	ZVAL_UNDEF(&_71$$7);
	ZVAL_UNDEF(&_72$$7);
	ZVAL_UNDEF(&_78$$7);
	ZVAL_UNDEF(&_79$$7);
	ZVAL_UNDEF(&_81$$7);
	ZVAL_UNDEF(&_46$$8);
	ZVAL_UNDEF(&_47$$8);
	ZVAL_UNDEF(&_48$$8);
	ZVAL_UNDEF(&_49$$8);
	ZVAL_UNDEF(&_50$$8);
	ZVAL_UNDEF(&_57$$9);
	ZVAL_UNDEF(&_58$$9);
	ZVAL_UNDEF(&_59$$9);
	ZVAL_UNDEF(&_60$$9);
	ZVAL_UNDEF(&_61$$9);
	ZVAL_UNDEF(&_62$$9);
	ZVAL_UNDEF(&_63$$9);
	ZVAL_UNDEF(&_64$$9);
	ZVAL_UNDEF(&_67$$10);
	ZVAL_UNDEF(&_68$$10);
	ZVAL_UNDEF(&_69$$10);
	ZVAL_UNDEF(&_70$$10);
	ZVAL_UNDEF(&_74$$11);
	ZVAL_UNDEF(&_75$$11);
	ZVAL_UNDEF(&_76$$11);
	ZVAL_UNDEF(&_77$$11);
	ZVAL_UNDEF(&_84$$13);
	ZVAL_UNDEF(&_85$$13);
	ZVAL_UNDEF(&_86$$13);
	ZVAL_UNDEF(&_13$$3);
	ZVAL_UNDEF(&_22$$4);
	ZVAL_UNDEF(&_31$$6);
	ZVAL_UNDEF(&_66$$10);
	ZVAL_UNDEF(&_73$$11);

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
	ZEPHIR_CALL_FUNCTION(&_3, "gzinflate", NULL, 27, &_2);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("post"), &_3);
	ZEPHIR_INIT_VAR(&_4);
	zephir_read_property(&_5, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
	zephir_json_decode(&_4, &_5, zephir_get_intval(&__$true) );
	zephir_update_property_zval(this_ptr, SL("post"), &_4);
	ZEPHIR_INIT_VAR(&_6);
	ZVAL_STRING(&_6, "Content-Type: text/plain; charset=utf-8");
	ZEPHIR_CALL_FUNCTION(NULL, "header", NULL, 28, &_6);
	zephir_check_call_status();
	zephir_read_property(&_7, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_string(&_8, &_7, SL("allowed_ips"), PH_NOISY | PH_READONLY, "plinker/server.zep", 92 TSRMLS_CC);
	_9 = !(ZEPHIR_IS_EMPTY(&_8));
	if (_9) {
		zephir_array_fetch_string(&_10, _SERVER, SL("REMOTE_ADDR"), PH_NOISY | PH_READONLY, "plinker/server.zep", 93 TSRMLS_CC);
		zephir_read_property(&_11, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_string(&_12, &_11, SL("allowed_ips"), PH_NOISY | PH_READONLY, "plinker/server.zep", 93 TSRMLS_CC);
		_9 = !(zephir_fast_in_array(&_10, &_12 TSRMLS_CC));
	}
	if (_9) {
		ZEPHIR_INIT_VAR(&_13$$3);
		zephir_create_array(&_13$$3, 2, 0 TSRMLS_CC);
		zephir_array_fetch_string(&_14$$3, _SERVER, SL("REMOTE_ADDR"), PH_NOISY | PH_READONLY, "plinker/server.zep", 95 TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_15$$3);
		ZVAL_STRING(&_15$$3, "IP not in allowed list (%s)");
		ZEPHIR_CALL_FUNCTION(&_16$$3, "sprintf", &_17, 29, &_15$$3, &_14$$3);
		zephir_check_call_status();
		zephir_array_update_string(&_13$$3, SL("error"), &_16$$3, PH_COPY | PH_SEPARATE);
		add_assoc_long_ex(&_13$$3, SL("code"), 403);
		ZEPHIR_CALL_FUNCTION(&_16$$3, "serialize", &_18, 15, &_13$$3);
		zephir_check_call_status();
		ZEPHIR_MM_RESTORE();
		zephir_exit(&_16$$3);
	}
	zephir_array_fetch_string(&_19, _SERVER, SL("HTTP_PLINKER"), PH_NOISY | PH_READONLY, "plinker/server.zep", 101 TSRMLS_CC);
	zephir_read_property(&_20, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_string(&_21, &_20, SL("token"), PH_NOISY | PH_READONLY, "plinker/server.zep", 101 TSRMLS_CC);
	if (!ZEPHIR_IS_EQUAL(&_19, &_21)) {
		ZEPHIR_INIT_VAR(&_22$$4);
		zephir_create_array(&_22$$4, 2, 0 TSRMLS_CC);
		add_assoc_stringl_ex(&_22$$4, SL("error"), SL("Plinker token mismatch"));
		add_assoc_long_ex(&_22$$4, SL("code"), 422);
		ZEPHIR_CALL_FUNCTION(&_23$$4, "serialize", &_18, 15, &_22$$4);
		zephir_check_call_status();
		ZEPHIR_MM_RESTORE();
		zephir_exit(&_23$$4);
	}
	ZEPHIR_OBS_VAR(&_24);
	zephir_read_property(&_24, this_ptr, SL("signer"), PH_NOISY_CC);
	if (!(zephir_is_true(&_24))) {
		ZEPHIR_INIT_VAR(&_25$$5);
		object_init_ex(&_25$$5, plinker_lib_signer_ce);
		zephir_read_property(&_26$$5, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(NULL, &_25$$5, "__construct", NULL, 2, &_26$$5);
		zephir_check_call_status();
		zephir_update_property_zval(this_ptr, SL("signer"), &_25$$5);
	}
	zephir_read_property(&_27, this_ptr, SL("signer"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_29, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_28, &_27, "decode", NULL, 0, &_29);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("post"), &_28);
	zephir_read_property(&_30, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_30) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_31$$6);
		zephir_create_array(&_31$$6, 2, 0 TSRMLS_CC);
		add_assoc_stringl_ex(&_31$$6, SL("error"), SL("Failed to decode payload, check secret"));
		add_assoc_long_ex(&_31$$6, SL("code"), 422);
		ZEPHIR_CALL_FUNCTION(&_32$$6, "serialize", &_18, 15, &_31$$6);
		zephir_check_call_status();
		ZEPHIR_MM_RESTORE();
		zephir_exit(&_32$$6);
	}
	zephir_read_property(&_33, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_OBS_VAR(&action);
	zephir_array_fetch_string(&action, &_33, SL("action"), PH_NOISY, "plinker/server.zep", 125 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(&_6);
	zephir_read_property(&_34, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_35, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
	zephir_fast_array_merge(&_6, &_34, &_35 TSRMLS_CC);
	zephir_update_property_zval(this_ptr, SL("config"), &_6);
	zephir_read_property(&_36, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_string(&_37, &_36, SL("component"), PH_NOISY | PH_READONLY, "plinker/server.zep", 132 TSRMLS_CC);
	zephir_read_property(&_38, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_string(&_39, &_38, SL("classes"), PH_NOISY | PH_READONLY, "plinker/server.zep", 132 TSRMLS_CC);
	if (zephir_array_key_exists(&_39, &_37 TSRMLS_CC)) {
		zephir_read_property(&_40$$7, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_string(&_41$$7, &_40$$7, SL("classes"), PH_NOISY | PH_READONLY, "plinker/server.zep", 134 TSRMLS_CC);
		zephir_read_property(&_43$$7, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_OBS_VAR(&_44$$7);
		zephir_array_fetch_string(&_44$$7, &_43$$7, SL("component"), PH_NOISY, "plinker/server.zep", 134 TSRMLS_CC);
		zephir_array_fetch(&_42$$7, &_41$$7, &_44$$7, PH_NOISY | PH_READONLY, "plinker/server.zep", 134 TSRMLS_CC);
		zephir_array_fetch_long(&_45$$7, &_42$$7, 0, PH_NOISY | PH_READONLY, "plinker/server.zep", 134 TSRMLS_CC);
		if (!(ZEPHIR_IS_EMPTY(&_45$$7))) {
			zephir_read_property(&_46$$8, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch_string(&_47$$8, &_46$$8, SL("classes"), PH_NOISY | PH_READONLY, "plinker/server.zep", 135 TSRMLS_CC);
			zephir_read_property(&_49$$8, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_VAR(&_50$$8);
			zephir_array_fetch_string(&_50$$8, &_49$$8, SL("component"), PH_NOISY, "plinker/server.zep", 135 TSRMLS_CC);
			zephir_array_fetch(&_48$$8, &_47$$8, &_50$$8, PH_NOISY | PH_READONLY, "plinker/server.zep", 135 TSRMLS_CC);
			ZEPHIR_OBS_VAR(&ns);
			zephir_array_fetch_long(&ns, &_48$$8, 0, PH_NOISY, "plinker/server.zep", 135 TSRMLS_CC);
		}
		zephir_read_property(&_51$$7, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_string(&_52$$7, &_51$$7, SL("classes"), PH_NOISY | PH_READONLY, "plinker/server.zep", 139 TSRMLS_CC);
		zephir_read_property(&_54$$7, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_OBS_VAR(&_55$$7);
		zephir_array_fetch_string(&_55$$7, &_54$$7, SL("component"), PH_NOISY, "plinker/server.zep", 139 TSRMLS_CC);
		zephir_array_fetch(&_53$$7, &_52$$7, &_55$$7, PH_NOISY | PH_READONLY, "plinker/server.zep", 139 TSRMLS_CC);
		zephir_array_fetch_long(&_56$$7, &_53$$7, 1, PH_NOISY | PH_READONLY, "plinker/server.zep", 139 TSRMLS_CC);
		if (!(ZEPHIR_IS_EMPTY(&_56$$7))) {
			ZEPHIR_INIT_VAR(&_57$$9);
			zephir_read_property(&_58$$9, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
			zephir_read_property(&_59$$9, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch_string(&_60$$9, &_59$$9, SL("classes"), PH_NOISY | PH_READONLY, "plinker/server.zep", 142 TSRMLS_CC);
			zephir_read_property(&_62$$9, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_VAR(&_63$$9);
			zephir_array_fetch_string(&_63$$9, &_62$$9, SL("component"), PH_NOISY, "plinker/server.zep", 142 TSRMLS_CC);
			zephir_array_fetch(&_61$$9, &_60$$9, &_63$$9, PH_NOISY | PH_READONLY, "plinker/server.zep", 142 TSRMLS_CC);
			zephir_array_fetch_long(&_64$$9, &_61$$9, 1, PH_NOISY | PH_READONLY, "plinker/server.zep", 143 TSRMLS_CC);
			zephir_fast_array_merge(&_57$$9, &_58$$9, &_64$$9 TSRMLS_CC);
			zephir_update_property_zval(this_ptr, SL("config"), &_57$$9);
		}
		_65$$7 = !(ZEPHIR_IS_EMPTY(&ns));
		if (_65$$7) {
			_65$$7 = !((zephir_file_exists(&ns TSRMLS_CC) == SUCCESS));
		}
		if (_65$$7) {
			ZEPHIR_INIT_VAR(&_66$$10);
			zephir_create_array(&_66$$10, 2, 0 TSRMLS_CC);
			zephir_read_property(&_67$$10, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch_string(&_68$$10, &_67$$10, SL("component"), PH_NOISY | PH_READONLY, "plinker/server.zep", 149 TSRMLS_CC);
			ZEPHIR_INIT_VAR(&_69$$10);
			ZVAL_STRING(&_69$$10, "User component class (%s) not found");
			ZEPHIR_CALL_FUNCTION(&_70$$10, "sprintf", &_17, 29, &_69$$10, &_68$$10);
			zephir_check_call_status();
			zephir_array_update_string(&_66$$10, SL("error"), &_70$$10, PH_COPY | PH_SEPARATE);
			add_assoc_long_ex(&_66$$10, SL("code"), 422);
			ZEPHIR_CALL_FUNCTION(&_70$$10, "serialize", &_18, 15, &_66$$10);
			zephir_check_call_status();
			ZEPHIR_MM_RESTORE();
			zephir_exit(&_70$$10);
		}
		if (zephir_require_zval(&ns TSRMLS_CC) == FAILURE) {
			RETURN_MM_NULL();
		}
		zephir_read_property(&_71$$7, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_string(&_72$$7, &_71$$7, SL("component"), PH_NOISY | PH_READONLY, "plinker/server.zep", 158 TSRMLS_CC);
		if (!(zephir_class_exists(&_72$$7, 1 TSRMLS_CC))) {
			ZEPHIR_INIT_VAR(&_73$$11);
			zephir_create_array(&_73$$11, 2, 0 TSRMLS_CC);
			zephir_read_property(&_74$$11, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch_string(&_75$$11, &_74$$11, SL("component"), PH_NOISY | PH_READONLY, "plinker/server.zep", 160 TSRMLS_CC);
			ZEPHIR_INIT_VAR(&_76$$11);
			ZVAL_STRING(&_76$$11, "User component class (%s) not found");
			ZEPHIR_CALL_FUNCTION(&_77$$11, "sprintf", &_17, 29, &_76$$11, &_75$$11);
			zephir_check_call_status();
			zephir_array_update_string(&_73$$11, SL("error"), &_77$$11, PH_COPY | PH_SEPARATE);
			add_assoc_long_ex(&_73$$11, SL("code"), 422);
			ZEPHIR_CALL_FUNCTION(&_77$$11, "serialize", &_18, 15, &_73$$11);
			zephir_check_call_status();
			ZEPHIR_MM_RESTORE();
			zephir_exit(&_77$$11);
		}
		zephir_read_property(&_78$$7, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_string(&_79$$7, &_78$$7, SL("component"), PH_NOISY | PH_READONLY, "plinker/server.zep", 166 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&response, this_ptr, "execute", &_80, 30, &_79$$7, &action);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(&_81$$7, "serialize", &_18, 15, &response);
		zephir_check_call_status();
		ZEPHIR_MM_RESTORE();
		zephir_exit(&_81$$7);
	}
	zephir_read_property(&_82, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_string(&_83, &_82, SL("component"), PH_NOISY | PH_READONLY, "plinker/server.zep", 172 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(&ns);
	ZEPHIR_CONCAT_SV(&ns, "\\Plinker\\Endpoint\\", &_83);
	if (zephir_class_exists(&ns, 1 TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(&response, this_ptr, "execute", &_80, 30, &ns, &action);
		zephir_check_call_status();
	} else {
		zephir_read_property(&_84$$13, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_string(&_85$$13, &_84$$13, SL("component"), PH_NOISY | PH_READONLY, "plinker/server.zep", 178 TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_86$$13);
		ZVAL_STRING(&_86$$13, "Component (%s) not implemented");
		ZEPHIR_CALL_FUNCTION(&response, "sprintf", &_17, 29, &_86$$13, &_85$$13);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_FUNCTION(&_87, "serialize", &_18, 15, &response);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
	zephir_exit(&_87);
	ZEPHIR_MM_RESTORE();

}

/**
 * Execute component
 *
 * @param  ns      component class namespace
 * @param  action  component action
 * @return string
 */
PHP_METHOD(Plinker_Server, execute) {

	zval _3$$3;
	zend_class_entry *_1;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *ns, ns_sub, *action, action_sub, response, component, _0, _2, _4$$3, _5$$3, _6$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ns_sub);
	ZVAL_UNDEF(&action_sub);
	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&component);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_3$$3);

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
		ZEPHIR_CALL_METHOD(NULL, &component, "__construct", NULL, 0, &_2);
		zephir_check_call_status();
	}
	if ((zephir_method_exists(&component, action TSRMLS_CC)  == SUCCESS)) {
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_create_array(&_3$$3, 2, 0 TSRMLS_CC);
		zephir_array_fast_append(&_3$$3, &component);
		zephir_array_fast_append(&_3$$3, action);
		zephir_read_property(&_4$$3, this_ptr, SL("post"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_string(&_5$$3, &_4$$3, SL("params"), PH_NOISY | PH_READONLY, "plinker/server.zep", 203 TSRMLS_CC);
		ZEPHIR_INIT_NVAR(&response);
		ZEPHIR_CALL_USER_FUNC_ARRAY(&response, &_3$$3, &_5$$3);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_VAR(&_6$$4);
		ZVAL_STRING(&_6$$4, "Component action (%s) not implemented in: %s");
		ZEPHIR_CALL_FUNCTION(&response, "sprintf", NULL, 29, &_6$$4, action, ns);
		zephir_check_call_status();
	}
	RETURN_CCTOR(&response);

}

PHP_FUNCTION(g_plinker_plinker_server) {
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *options_param = NULL, _0;
	zval options;
		ZVAL_UNDEF(&options);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &options_param);

	if (!options_param) {
		ZEPHIR_INIT_VAR(&options);
		array_init(&options);
	} else {
	ZEPHIR_OBS_COPY_OR_DUP(&options, options_param);
	}


	ZEPHIR_INIT_VAR(&_0);
	object_init_ex(&_0, plinker_server_ce);
	ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 31, &options);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &_0, "listen", NULL, 32);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

