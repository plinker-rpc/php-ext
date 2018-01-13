
/* This file was generated automatically by Zephir do not modify it! */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#include "php_ext.h"
#include "plinker.h"

#include <ext/standard/info.h>

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/globals.h"
#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"



zend_class_entry *plinker_client_ce;
zend_class_entry *plinker_endpoint_system_ce;
zend_class_entry *plinker_lib_curl_ce;
zend_class_entry *plinker_lib_signer_ce;
zend_class_entry *plinker_server_ce;

ZEND_DECLARE_MODULE_GLOBALS(plinker)

PHP_INI_BEGIN()
	
PHP_INI_END()

static PHP_MINIT_FUNCTION(plinker)
{
	REGISTER_INI_ENTRIES();
	zephir_module_init();
	ZEPHIR_INIT(Plinker_Client);
	ZEPHIR_INIT(Plinker_Endpoint_System);
	ZEPHIR_INIT(Plinker_Lib_Curl);
	ZEPHIR_INIT(Plinker_Lib_Signer);
	ZEPHIR_INIT(Plinker_Server);
	return SUCCESS;
}

#ifndef ZEPHIR_RELEASE
static PHP_MSHUTDOWN_FUNCTION(plinker)
{
	zephir_deinitialize_memory(TSRMLS_C);
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
#endif

/**
 * Initialize globals on each request or each thread started
 */
static void php_zephir_init_globals(zend_plinker_globals *plinker_globals TSRMLS_DC)
{
	plinker_globals->initialized = 0;

	/* Memory options */
	plinker_globals->active_memory = NULL;

	/* Virtual Symbol Tables */
	plinker_globals->active_symbol_table = NULL;

	/* Cache Enabled */
	plinker_globals->cache_enabled = 1;

	/* Recursive Lock */
	plinker_globals->recursive_lock = 0;

	/* Static cache */
	memset(plinker_globals->scache, '\0', sizeof(zephir_fcall_cache_entry*) * ZEPHIR_MAX_CACHE_SLOTS);


}

/**
 * Initialize globals only on each thread started
 */
static void php_zephir_init_module_globals(zend_plinker_globals *plinker_globals TSRMLS_DC)
{

}

static PHP_RINIT_FUNCTION(plinker)
{

	zend_plinker_globals *plinker_globals_ptr;
#ifdef ZTS
	tsrm_ls = ts_resource(0);
#endif
	plinker_globals_ptr = ZEPHIR_VGLOBAL;

	php_zephir_init_globals(plinker_globals_ptr TSRMLS_CC);
	zephir_initialize_memory(plinker_globals_ptr TSRMLS_CC);


	return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(plinker)
{
	
	zephir_deinitialize_memory(TSRMLS_C);
	return SUCCESS;
}

static PHP_MINFO_FUNCTION(plinker)
{
	php_info_print_box_start(0);
	php_printf("%s", PHP_PLINKER_DESCRIPTION);
	php_info_print_box_end();

	php_info_print_table_start();
	php_info_print_table_header(2, PHP_PLINKER_NAME, "enabled");
	php_info_print_table_row(2, "Author", PHP_PLINKER_AUTHOR);
	php_info_print_table_row(2, "Version", PHP_PLINKER_VERSION);
	php_info_print_table_row(2, "Build Date", __DATE__ " " __TIME__ );
	php_info_print_table_row(2, "Powered by Zephir", "Version " PHP_PLINKER_ZEPVERSION);
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}

static PHP_GINIT_FUNCTION(plinker)
{
	php_zephir_init_globals(plinker_globals TSRMLS_CC);
	php_zephir_init_module_globals(plinker_globals TSRMLS_CC);
}

static PHP_GSHUTDOWN_FUNCTION(plinker)
{

}

PHP_FUNCTION(g_plinker_plinker_client);
ZEND_BEGIN_ARG_INFO_EX(arginfo_g_plinker_plinker_client, 0, 0, 2)
	ZEND_ARG_INFO(0, url)
	ZEND_ARG_INFO(0, secret)
	ZEND_ARG_ARRAY_INFO(0, options, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(g_plinker_plinker_server);
ZEND_BEGIN_ARG_INFO_EX(arginfo_g_plinker_plinker_server, 0, 0, 0)
	ZEND_ARG_ARRAY_INFO(0, options, 1)
ZEND_END_ARG_INFO()


zend_function_entry php_plinker_functions[] = {
ZEND_NAMED_FE(plinker_client, ZEND_FN(g_plinker_plinker_client), arginfo_g_plinker_plinker_client)
ZEND_NAMED_FE(plinker_server, ZEND_FN(g_plinker_plinker_server), arginfo_g_plinker_plinker_server)
ZEND_FE_END

};

zend_module_entry plinker_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	NULL,
	PHP_PLINKER_EXTNAME,
	php_plinker_functions,
	PHP_MINIT(plinker),
#ifndef ZEPHIR_RELEASE
	PHP_MSHUTDOWN(plinker),
#else
	NULL,
#endif
	PHP_RINIT(plinker),
	PHP_RSHUTDOWN(plinker),
	PHP_MINFO(plinker),
	PHP_PLINKER_VERSION,
	ZEND_MODULE_GLOBALS(plinker),
	PHP_GINIT(plinker),
	PHP_GSHUTDOWN(plinker),
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_PLINKER
ZEND_GET_MODULE(plinker)
#endif
