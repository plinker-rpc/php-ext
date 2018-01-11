
extern zend_class_entry *plinker_server_ce;

ZEPHIR_INIT_CLASS(Plinker_Server);

PHP_METHOD(Plinker_Server, __construct);
PHP_METHOD(Plinker_Server, listen);
PHP_METHOD(Plinker_Server, execute);

ZEND_BEGIN_ARG_INFO_EX(arginfo_plinker_server___construct, 0, 0, 0)
	ZEND_ARG_ARRAY_INFO(0, config, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_plinker_server_execute, 0, 0, 2)
	ZEND_ARG_INFO(0, ns)
	ZEND_ARG_INFO(0, action)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(plinker_server_method_entry) {
	PHP_ME(Plinker_Server, __construct, arginfo_plinker_server___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Plinker_Server, listen, NULL, ZEND_ACC_FINAL|ZEND_ACC_PUBLIC)
	PHP_ME(Plinker_Server, execute, arginfo_plinker_server_execute, ZEND_ACC_FINAL|ZEND_ACC_PRIVATE)
	PHP_FE_END
};
