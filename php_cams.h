/*
 *  php_cams.h
 *
 *  Copyright (c) 2002 Sauer L.
 *
 *  This source file is covered by the Library General Public License (LGPL) 
 *  published by the GNU. A copy of the LGPL should have been included within
 *  this file, if not, please have a look at www.gnu.org
 *
 */

#ifndef PHP_cams_H
#define PHP_cams_H

extern zend_module_entry cams_module_entry;
#define phpext_cams_ptr &cams_module_entry

#ifdef PHP_WIN32
#define PHP_cams_API __declspec(dllexport)
#else
#define PHP_cams_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

typedef unsigned char	Uint8;
typedef unsigned short	Uint16;
typedef unsigned int	Uint23;

/*
PHP_MINIT_FUNCTION(cams);
PHP_MSHUTDOWN_FUNCTION(cams);
PHP_RINIT_FUNCTION(cams);
PHP_RSHUTDOWN_FUNCTION(cams);
*/
PHP_MINFO_FUNCTION(cams);

ZEND_FUNCTION(cams_open);
ZEND_FUNCTION(cams_close);
ZEND_FUNCTION(cams_outp);
ZEND_FUNCTION(cams_inp);
ZEND_FUNCTION(cams_getport);

#ifdef ZTS
#define cams_G(v) TSRMG(cams_globals_id, zend_cams_globals *, v)
#else
#define cams_G(v) (cams_globals.v)
#endif

#endif	/* PHP_cams_H */
