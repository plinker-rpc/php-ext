
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
#include "kernel/array.h"
#include "kernel/object.h"
#include "kernel/concat.h"
#include "kernel/fcall.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/operators.h"
#include "kernel/string.h"


ZEPHIR_INIT_CLASS(Plinker_Lib_Signer) {

	ZEPHIR_REGISTER_CLASS(Plinker\\Lib, Signer, plinker, lib_signer, plinker_lib_signer_method_entry, ZEND_ACC_FINAL_CLASS);

	zend_declare_property_null(plinker_lib_signer_ce, SL("config"), ZEND_ACC_PRIVATE TSRMLS_CC);

	return SUCCESS;

}

/**
 *
 */
PHP_METHOD(Plinker_Lib_Signer, __construct) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *config_param = NULL, __$null, _0, _2, _3$$3, _4$$3, _5$$3, _6$$3, _7$$3, _8$$3;
	zval config, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&config);
	ZVAL_UNDEF(&_1);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
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
	zephir_create_array(&_1, 1, 0 TSRMLS_CC);
	zephir_array_update_string(&_1, SL("secret"), &__$null, PH_COPY | PH_SEPARATE);
	zephir_fast_array_merge(&_0, &_1, &config TSRMLS_CC);
	zephir_update_property_zval(this_ptr, SL("config"), &_0);
	zephir_read_property(&_2, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset_string(&_2, SL("secret"))) {
		ZEPHIR_INIT_VAR(&_3$$3);
		ZVAL_STRING(&_3$$3, "h");
		ZEPHIR_CALL_FUNCTION(&_4$$3, "gmdate", NULL, 16, &_3$$3);
		zephir_check_call_status();
		zephir_read_property(&_5$$3, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_string(&_6$$3, &_5$$3, SL("secret"), PH_NOISY | PH_READONLY, "plinker/lib/signer.zep", 37 TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_VV(&_7$$3, &_4$$3, &_6$$3);
		ZEPHIR_INIT_NVAR(&_3$$3);
		ZVAL_STRING(&_3$$3, "sha256");
		ZEPHIR_CALL_FUNCTION(&_8$$3, "hash", NULL, 17, &_3$$3, &_7$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_3$$3);
		ZVAL_STRING(&_3$$3, "secret");
		zephir_update_property_array(this_ptr, SL("config"), &_3$$3, &_8$$3 TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 *
 */
PHP_METHOD(Plinker_Lib_Signer, encrypt) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *plaintext_param = NULL, *password_param = NULL, __$true, _0, _1, _3, _4, _6, _8;
	zval plaintext, password, method, key, _2, iv, _5, ciphertext, _7, hash, _9, _10;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&plaintext);
	ZVAL_UNDEF(&password);
	ZVAL_UNDEF(&method);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&iv);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&ciphertext);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&hash);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &plaintext_param, &password_param);

	if (UNEXPECTED(Z_TYPE_P(plaintext_param) != IS_STRING && Z_TYPE_P(plaintext_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'plaintext' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(plaintext_param) == IS_STRING)) {
		zephir_get_strval(&plaintext, plaintext_param);
	} else {
		ZEPHIR_INIT_VAR(&plaintext);
		ZVAL_EMPTY_STRING(&plaintext);
	}
	if (UNEXPECTED(Z_TYPE_P(password_param) != IS_STRING && Z_TYPE_P(password_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'password' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(password_param) == IS_STRING)) {
		zephir_get_strval(&password, password_param);
	} else {
		ZEPHIR_INIT_VAR(&password);
		ZVAL_EMPTY_STRING(&password);
	}


	ZEPHIR_INIT_VAR(&method);
	ZVAL_STRING(&method, "AES-256-CBC");
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "sha256");
	ZEPHIR_CALL_FUNCTION(&_1, "hash", NULL, 17, &_0, &password, &__$true);
	zephir_check_call_status();
	zephir_get_strval(&_2, &_1);
	ZEPHIR_CPY_WRT(&key, &_2);
	ZVAL_LONG(&_3, 16);
	ZEPHIR_CALL_FUNCTION(&_4, "openssl_random_pseudo_bytes", NULL, 18, &_3);
	zephir_check_call_status();
	zephir_get_strval(&_5, &_4);
	ZEPHIR_CPY_WRT(&iv, &_5);
	ZVAL_LONG(&_3, 1);
	ZEPHIR_CALL_FUNCTION(&_6, "openssl_encrypt", NULL, 19, &plaintext, &method, &key, &_3, &iv);
	zephir_check_call_status();
	zephir_get_strval(&_7, &_6);
	ZEPHIR_CPY_WRT(&ciphertext, &_7);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "sha256");
	ZEPHIR_CALL_FUNCTION(&_8, "hash_hmac", NULL, 20, &_0, &ciphertext, &key, &__$true);
	zephir_check_call_status();
	zephir_get_strval(&_9, &_8);
	ZEPHIR_CPY_WRT(&hash, &_9);
	ZEPHIR_INIT_VAR(&_10);
	ZEPHIR_CONCAT_VVV(&_10, &iv, &hash, &ciphertext);
	ZEPHIR_RETURN_CALL_FUNCTION("base64_encode", NULL, 21, &_10);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 *
 */
PHP_METHOD(Plinker_Lib_Signer, decrypt) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *ciphertext_param = NULL, *password_param = NULL, __$true, _0, _1, _2, _3, _4, _5, _6, _7, _8, _10, _11;
	zval ciphertext, password, method, iv, hash, key, _9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ciphertext);
	ZVAL_UNDEF(&password);
	ZVAL_UNDEF(&method);
	ZVAL_UNDEF(&iv);
	ZVAL_UNDEF(&hash);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&_9);
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

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &ciphertext_param, &password_param);

	if (UNEXPECTED(Z_TYPE_P(ciphertext_param) != IS_STRING && Z_TYPE_P(ciphertext_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'ciphertext' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(ciphertext_param) == IS_STRING)) {
		zephir_get_strval(&ciphertext, ciphertext_param);
	} else {
		ZEPHIR_INIT_VAR(&ciphertext);
		ZVAL_EMPTY_STRING(&ciphertext);
	}
	if (UNEXPECTED(Z_TYPE_P(password_param) != IS_STRING && Z_TYPE_P(password_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'password' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(password_param) == IS_STRING)) {
		zephir_get_strval(&password, password_param);
	} else {
		ZEPHIR_INIT_VAR(&password);
		ZVAL_EMPTY_STRING(&password);
	}


	ZEPHIR_CALL_FUNCTION(&_0, "base64_decode", NULL, 22, &ciphertext);
	zephir_check_call_status();
	zephir_get_strval(&ciphertext, &_0);
	ZEPHIR_INIT_VAR(&method);
	ZVAL_STRING(&method, "AES-256-CBC");
	ZVAL_LONG(&_1, 0);
	ZVAL_LONG(&_2, 16);
	ZEPHIR_INIT_VAR(&iv);
	zephir_substr(&iv, &ciphertext, 0 , 16 , 0);
	ZVAL_LONG(&_3, 16);
	ZVAL_LONG(&_4, 32);
	ZEPHIR_INIT_VAR(&hash);
	zephir_substr(&hash, &ciphertext, 16 , 32 , 0);
	ZVAL_LONG(&_5, 48);
	ZEPHIR_INIT_VAR(&_6);
	zephir_substr(&_6, &ciphertext, 48 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
	zephir_get_strval(&ciphertext, &_6);
	ZEPHIR_INIT_VAR(&_7);
	ZVAL_STRING(&_7, "sha256");
	ZEPHIR_CALL_FUNCTION(&_8, "hash", NULL, 17, &_7, &password, &__$true);
	zephir_check_call_status();
	zephir_get_strval(&_9, &_8);
	ZEPHIR_CPY_WRT(&key, &_9);
	ZEPHIR_INIT_NVAR(&_7);
	ZVAL_STRING(&_7, "sha256");
	ZEPHIR_CALL_FUNCTION(&_10, "hash_hmac", NULL, 20, &_7, &ciphertext, &key, &__$true);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_10, &hash)) {
		RETURN_MM_NULL();
	}
	ZVAL_LONG(&_11, 1);
	ZEPHIR_RETURN_CALL_FUNCTION("openssl_decrypt", NULL, 23, &ciphertext, &method, &key, &_11, &iv);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 *
 */
PHP_METHOD(Plinker_Lib_Signer, encode) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *data_param = NULL, _0, _1, _2, _3, _4, _5, _6;
	zval data;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&data);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &data_param);

	ZEPHIR_OBS_COPY_OR_DUP(&data, data_param);


	ZEPHIR_CALL_FUNCTION(&_0, "serialize", NULL, 14, &data);
	zephir_check_call_status();
	zephir_get_strval(&data, &_0);
	zephir_create_array(return_value, 2, 0 TSRMLS_CC);
	zephir_read_property(&_2, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_string(&_3, &_2, SL("secret"), PH_NOISY | PH_READONLY, "plinker/lib/signer.zep", 84 TSRMLS_CC);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "encrypt", NULL, 24, &data, &_3);
	zephir_check_call_status();
	zephir_array_update_string(return_value, SL("data"), &_1, PH_COPY | PH_SEPARATE);
	zephir_read_property(&_4, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_string(&_5, &_4, SL("secret"), PH_NOISY | PH_READONLY, "plinker/lib/signer.zep", 89 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_6);
	ZVAL_STRING(&_6, "sha256");
	ZEPHIR_CALL_FUNCTION(&_1, "hash_hmac", NULL, 20, &_6, &data, &_5);
	zephir_check_call_status();
	zephir_array_update_string(return_value, SL("token"), &_1, PH_COPY | PH_SEPARATE);
	RETURN_MM();

}

/**
 *
 */
PHP_METHOD(Plinker_Lib_Signer, decode) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *data_param = NULL, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10$$3, _11$$3;
	zval data, _12$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&data);
	ZVAL_UNDEF(&_12$$3);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_11$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &data_param);

	ZEPHIR_OBS_COPY_OR_DUP(&data, data_param);


	zephir_array_fetch_string(&_1, &data, SL("data"), PH_NOISY | PH_READONLY, "plinker/lib/signer.zep", 98 TSRMLS_CC);
	zephir_read_property(&_2, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_string(&_3, &_2, SL("secret"), PH_NOISY | PH_READONLY, "plinker/lib/signer.zep", 98 TSRMLS_CC);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "decrypt", NULL, 25, &_1, &_3);
	zephir_check_call_status();
	zephir_array_update_string(&data, SL("data"), &_0, PH_COPY | PH_SEPARATE);
	zephir_array_fetch_string(&_4, &data, SL("data"), PH_NOISY | PH_READONLY, "plinker/lib/signer.zep", 103 TSRMLS_CC);
	zephir_read_property(&_5, this_ptr, SL("config"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_string(&_6, &_5, SL("secret"), PH_NOISY | PH_READONLY, "plinker/lib/signer.zep", 105 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_7);
	ZVAL_STRING(&_7, "sha256");
	ZEPHIR_CALL_FUNCTION(&_8, "hash_hmac", NULL, 20, &_7, &_4, &_6);
	zephir_check_call_status();
	zephir_array_fetch_string(&_9, &data, SL("token"), PH_NOISY | PH_READONLY, "plinker/lib/signer.zep", 105 TSRMLS_CC);
	if (ZEPHIR_IS_EQUAL(&_8, &_9)) {
		zephir_array_fetch_string(&_10$$3, &data, SL("data"), PH_NOISY | PH_READONLY, "plinker/lib/signer.zep", 106 TSRMLS_CC);
		ZEPHIR_CALL_FUNCTION(&_11$$3, "unserialize", NULL, 4, &_10$$3);
		zephir_check_call_status();
		zephir_get_arrval(&_12$$3, &_11$$3);
		RETURN_CTOR(&_12$$3);
	} else {
		RETURN_MM_NULL();
	}

}

