
extern zend_class_entry *plinker_client_ce;

ZEPHIR_INIT_CLASS(Plinker_Client);

PHP_METHOD(Plinker_Client, __construct);
PHP_METHOD(Plinker_Client, __get);
PHP_METHOD(Plinker_Client, __call);

ZEND_BEGIN_ARG_INFO_EX(arginfo_plinker_client___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, server)
	ZEND_ARG_ARRAY_INFO(0, config, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_plinker_client___get, 0, 0, 1)
	ZEND_ARG_INFO(0, method)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_plinker_client___call, 0, 0, 2)
	ZEND_ARG_INFO(0, action)
	ZEND_ARG_ARRAY_INFO(0, params, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(plinker_client_method_entry) {
	PHP_ME(Plinker_Client, __construct, arginfo_plinker_client___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Plinker_Client, __get, arginfo_plinker_client___get, ZEND_ACC_PUBLIC)
	PHP_ME(Plinker_Client, __call, arginfo_plinker_client___call, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
