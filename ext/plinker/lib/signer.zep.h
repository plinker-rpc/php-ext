
extern zend_class_entry *plinker_lib_signer_ce;

ZEPHIR_INIT_CLASS(Plinker_Lib_Signer);

PHP_METHOD(Plinker_Lib_Signer, __construct);
PHP_METHOD(Plinker_Lib_Signer, encrypt);
PHP_METHOD(Plinker_Lib_Signer, decrypt);
PHP_METHOD(Plinker_Lib_Signer, encode);
PHP_METHOD(Plinker_Lib_Signer, decode);

ZEND_BEGIN_ARG_INFO_EX(arginfo_plinker_lib_signer___construct, 0, 0, 0)
	ZEND_ARG_ARRAY_INFO(0, config, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_plinker_lib_signer_encrypt, 0, 0, 2)
	ZEND_ARG_INFO(0, plaintext)
	ZEND_ARG_INFO(0, password)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_plinker_lib_signer_decrypt, 0, 0, 2)
	ZEND_ARG_INFO(0, ciphertext)
	ZEND_ARG_INFO(0, password)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_plinker_lib_signer_encode, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, data, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_plinker_lib_signer_decode, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, data, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(plinker_lib_signer_method_entry) {
	PHP_ME(Plinker_Lib_Signer, __construct, arginfo_plinker_lib_signer___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Plinker_Lib_Signer, encrypt, arginfo_plinker_lib_signer_encrypt, ZEND_ACC_PRIVATE)
	PHP_ME(Plinker_Lib_Signer, decrypt, arginfo_plinker_lib_signer_decrypt, ZEND_ACC_PRIVATE)
	PHP_ME(Plinker_Lib_Signer, encode, arginfo_plinker_lib_signer_encode, ZEND_ACC_PUBLIC)
	PHP_ME(Plinker_Lib_Signer, decode, arginfo_plinker_lib_signer_decode, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
