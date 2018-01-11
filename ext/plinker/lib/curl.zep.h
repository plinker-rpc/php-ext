
extern zend_class_entry *plinker_lib_curl_ce;

ZEPHIR_INIT_CLASS(Plinker_Lib_Curl);

PHP_METHOD(Plinker_Lib_Curl, __construct);
PHP_METHOD(Plinker_Lib_Curl, setOptions);
PHP_METHOD(Plinker_Lib_Curl, post);

ZEND_BEGIN_ARG_INFO_EX(arginfo_plinker_lib_curl___construct, 0, 0, 0)
	ZEND_ARG_ARRAY_INFO(0, config, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_plinker_lib_curl_post, 0, 0, 1)
	ZEND_ARG_INFO(0, url)
	ZEND_ARG_INFO(0, parameters)
	ZEND_ARG_ARRAY_INFO(0, headers, 1)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(plinker_lib_curl_method_entry) {
	PHP_ME(Plinker_Lib_Curl, __construct, arginfo_plinker_lib_curl___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Plinker_Lib_Curl, setOptions, NULL, ZEND_ACC_FINAL|ZEND_ACC_PRIVATE)
	PHP_ME(Plinker_Lib_Curl, post, arginfo_plinker_lib_curl_post, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
