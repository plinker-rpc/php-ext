PHP_ARG_ENABLE(plinker, whether to enable plinker, [ --enable-plinker   Enable Plinker])

if test "$PHP_PLINKER" = "yes"; then

	
	AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
	if test "x$PKG_CONFIG" = "xno"; then
		AC_MSG_RESULT([pkg-config not found])
		AC_MSG_ERROR([Please reinstall the pkg-config distribution])
	fi


	AC_MSG_CHECKING([for openssl])
	if $PKG_CONFIG --exists openssl; then
		PHP_OPENSSL_VERSION=`$PKG_CONFIG openssl --modversion`
		PHP_OPENSSL_PREFIX=`$PKG_CONFIG openssl --variable=prefix`

		if $PKG_CONFIG --atleast-version=0.0.0 openssl; then
			AC_MSG_RESULT([found version $PHP_OPENSSL_VERSION, under $PHP_OPENSSL_PREFIX])
			PHP_OPENSSL_LIBS=`$PKG_CONFIG openssl --libs`
			PHP_OPENSSL_INCS=`$PKG_CONFIG openssl --cflags`

			PHP_EVAL_LIBLINE($PHP_OPENSSL_LIBS, PLINKER_SHARED_LIBADD)
			PHP_EVAL_INCLINE($PHP_OPENSSL_INCS)
		else
			AC_MSG_ERROR(Requested 'openssl >= 0.0.0' but version of openssl is $PHP_OPENSSL_VERSION)
		fi
	else
		AC_MSG_ERROR(Unable to find openssl installation)
	fi


	AC_MSG_CHECKING([for libcurl])
	if $PKG_CONFIG --exists libcurl; then
		PHP_LIBCURL_VERSION=`$PKG_CONFIG libcurl --modversion`
		PHP_LIBCURL_PREFIX=`$PKG_CONFIG libcurl --variable=prefix`

		if $PKG_CONFIG --atleast-version=0.0.0 libcurl; then
			AC_MSG_RESULT([found version $PHP_LIBCURL_VERSION, under $PHP_LIBCURL_PREFIX])
			PHP_LIBCURL_LIBS=`$PKG_CONFIG libcurl --libs`
			PHP_LIBCURL_INCS=`$PKG_CONFIG libcurl --cflags`

			PHP_EVAL_LIBLINE($PHP_LIBCURL_LIBS, PLINKER_SHARED_LIBADD)
			PHP_EVAL_INCLINE($PHP_LIBCURL_INCS)
		else
			AC_MSG_ERROR(Requested 'libcurl >= 0.0.0' but version of libcurl is $PHP_LIBCURL_VERSION)
		fi
	else
		AC_MSG_ERROR(Unable to find libcurl installation)
	fi



	if ! test "x" = "x"; then
		PHP_EVAL_LIBLINE(, PLINKER_SHARED_LIBADD)
	fi

	AC_DEFINE(HAVE_PLINKER, 1, [Whether you have Plinker])
	plinker_sources="plinker.c kernel/main.c kernel/memory.c kernel/exception.c kernel/debug.c kernel/backtrace.c kernel/object.c kernel/array.c kernel/string.c kernel/fcall.c kernel/require.c kernel/file.c kernel/operators.c kernel/math.c kernel/concat.c kernel/variables.c kernel/filter.c kernel/iterator.c kernel/time.c kernel/exit.c plinker/client.zep.c
	plinker/endpoint/system.zep.c
	plinker/lib/curl.zep.c
	plinker/lib/signer.zep.c
	plinker/server.zep.c "
	PHP_NEW_EXTENSION(plinker, $plinker_sources, $ext_shared,,  $PHP_OPENSSL_INCS $PHP_LIBCURL_INCS )
	PHP_SUBST(PLINKER_SHARED_LIBADD)

	old_CPPFLAGS=$CPPFLAGS
	CPPFLAGS="$CPPFLAGS $INCLUDES"

	AC_CHECK_DECL(
		[HAVE_BUNDLED_PCRE],
		[
			AC_CHECK_HEADERS(
				[ext/pcre/php_pcre.h],
				[
					PHP_ADD_EXTENSION_DEP([plinker], [pcre])
					AC_DEFINE([ZEPHIR_USE_PHP_PCRE], [1], [Whether PHP pcre extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	AC_CHECK_DECL(
		[HAVE_JSON],
		[
			AC_CHECK_HEADERS(
				[ext/json/php_json.h],
				[
					PHP_ADD_EXTENSION_DEP([plinker], [json])
					AC_DEFINE([ZEPHIR_USE_PHP_JSON], [1], [Whether PHP json extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	CPPFLAGS=$old_CPPFLAGS

	PHP_INSTALL_HEADERS([ext/plinker], [php_PLINKER.h])

fi
