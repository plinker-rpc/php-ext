
extern zend_class_entry *plinker_endpoint_system_ce;

ZEPHIR_INIT_CLASS(Plinker_Endpoint_System);

PHP_METHOD(Plinker_Endpoint_System, __construct);
PHP_METHOD(Plinker_Endpoint_System, disk_space);
PHP_METHOD(Plinker_Endpoint_System, total_disk_space);

ZEND_BEGIN_ARG_INFO_EX(arginfo_plinker_endpoint_system___construct, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, config, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_plinker_endpoint_system_disk_space, 0, 0, 0)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_plinker_endpoint_system_total_disk_space, 0, 0, 0)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(plinker_endpoint_system_method_entry) {
	PHP_ME(Plinker_Endpoint_System, __construct, arginfo_plinker_endpoint_system___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Plinker_Endpoint_System, disk_space, arginfo_plinker_endpoint_system_disk_space, ZEND_ACC_PUBLIC)
	PHP_ME(Plinker_Endpoint_System, total_disk_space, arginfo_plinker_endpoint_system_total_disk_space, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
