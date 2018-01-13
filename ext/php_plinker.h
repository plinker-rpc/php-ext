
/* This file was generated automatically by Zephir do not modify it! */

#ifndef PHP_PLINKER_H
#define PHP_PLINKER_H 1

#ifdef PHP_WIN32
#define ZEPHIR_RELEASE 1
#endif

#include "kernel/globals.h"

#define PHP_PLINKER_NAME        "Plinker RPC"
#define PHP_PLINKER_VERSION     "0.0.1"
#define PHP_PLINKER_EXTNAME     "plinker"
#define PHP_PLINKER_AUTHOR      "Lawrence Cherone"
#define PHP_PLINKER_ZEPVERSION  "0.10.6-f58caac89e"
#define PHP_PLINKER_DESCRIPTION "Plinker PHP RPC client/server makes it really easy to link and execute PHP component classes on remote systems, while maintaining the feel of a local method call."



ZEND_BEGIN_MODULE_GLOBALS(plinker)

	int initialized;

	/* Memory */
	zephir_memory_entry *start_memory; /**< The first preallocated frame */
	zephir_memory_entry *end_memory; /**< The last preallocate frame */
	zephir_memory_entry *active_memory; /**< The current memory frame */

	/* Virtual Symbol Tables */
	zephir_symbol_table *active_symbol_table;

	/** Function cache */
	HashTable *fcache;

	zephir_fcall_cache_entry *scache[ZEPHIR_MAX_CACHE_SLOTS];

	/* Cache enabled */
	unsigned int cache_enabled;

	/* Max recursion control */
	unsigned int recursive_lock;

	
ZEND_END_MODULE_GLOBALS(plinker)

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_EXTERN_MODULE_GLOBALS(plinker)

#ifdef ZTS
	#define ZEPHIR_GLOBAL(v) ZEND_MODULE_GLOBALS_ACCESSOR(plinker, v)
#else
	#define ZEPHIR_GLOBAL(v) (plinker_globals.v)
#endif

#ifdef ZTS
	void ***tsrm_ls;
	#define ZEPHIR_VGLOBAL ((zend_plinker_globals *) (*((void ***) tsrm_get_ls_cache()))[TSRM_UNSHUFFLE_RSRC_ID(plinker_globals_id)])
#else
	#define ZEPHIR_VGLOBAL &(plinker_globals)
#endif

#define ZEPHIR_API ZEND_API

#define zephir_globals_def plinker_globals
#define zend_zephir_globals_def zend_plinker_globals

extern zend_module_entry plinker_module_entry;
#define phpext_plinker_ptr &plinker_module_entry

#endif
