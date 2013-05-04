/*
 *  cams.c
 *
 *  Copyright (c) 2002 Sauer L.
 *
 *  This source file is covered by the Library General Public License (LGPL) 
 *  published by the GNU. A copy of the LGPL should have been included within
 *  this file, if not, please have a look at www.gnu.org
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <windows.h>

#include "pt_ioctl.c"

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"

#include "php_cams.h"

#define cams_MODULE_NAME		"cams"
#define cams_MODULE_VERSION		"0.1"

/* 
   LUT with function names as used in php and its c equivalent,
   usually expanded to zif_funcname
*/
zend_function_entry cams_functions[] = {
	ZEND_FE(cams_open,		NULL)
	ZEND_FE(cams_close,		NULL)
	ZEND_FE(cams_outp,		NULL)
	ZEND_FE(cams_inp,		  NULL)
	ZEND_FE(cams_getport,	NULL)
	{NULL,		NULL,		NULL}
};

/* 
   This block contains all necessary information to describe the contents
   of this module to Zend.
*/
zend_module_entry cams_module_entry = {
	STANDARD_MODULE_HEADER,				/* we're keeping to standards	*/
	cams_MODULE_NAME,					    /* module's name				      */
	cams_functions,						    /* points to function LUT		  */
	NULL,								          /* PHP_MINIT(cams)				    */
	NULL,								          /* PHP_MSHUTDOWN(cams)			  */
	NULL,								          /* PHP_RINIT(cams)				    */
	NULL,							          	/* PHP_RSHUTDOWN(cams)			  */
	PHP_MINFO(cams),	    				/* module info function			  */
	cams_MODULE_VERSION,				  /* version number				      */
	STANDARD_MODULE_PROPERTIES		/* skip the rest				      */
};

/* 
   This should always be present, due the dynamic loading capabilities 
   Zend provides PHP > 4.x with, thus the  surrounding by an conditional 
   expression, since this function is only required if your module is built 
   as a dynamic extension. >>Have a look at php's dl() function!
*/
#ifdef COMPILE_DL_cams
	ZEND_GET_MODULE(cams)
#endif

/* 
   Sets module informations printed out by functions as php's 'phpinfo()'
*/
PHP_MINFO_FUNCTION(cams) {
	php_info_print_table_start();
	php_info_print_table_row(2, "cams support", "enabled");
	php_info_print_table_row(2, "version", cams_module_entry.version);
	php_info_print_table_end();
}


/* EXPORT FUNCTIONS DEFINITIONS 
   ----------------------------
ZEND_FUNCTIONS expands through invocation to: 
    'void zif_my_function(int ht, zval *return_value, zval *this_ptr, int return_value_used, zend_executor_globals *executor_globals);'
*/

/* initialize & uninitializes cams */
ZEND_FUNCTION(cams_open) {
	OpenPortTalk();

	RETVAL_TRUE;
}

ZEND_FUNCTION(cams_close) {
	ClosePortTalk();

	RETVAL_TRUE;
}

void zend_minit_cams(){
	OpenPortTalk();

}

void zm_mshutdown_cams(){
	ClosePortTalk();

}


/* outport and inport functions: iop(Uint8 port, Uint8 data ) */
ZEND_FUNCTION(cams_outp) {
	zval **port, **data;

	/* check for parameters and address 'em */
	switch (ZEND_NUM_ARGS()) {
		case 2:
			if (zend_get_parameters_ex(2, &port, &data) != SUCCESS) {
				ZEND_WRONG_PARAM_COUNT();
			}
			break;
		default:
			ZEND_WRONG_PARAM_COUNT();
	}

	/* make sure we got the right types passed */
	if ( Z_TYPE_PP(port) != IS_LONG && Z_TYPE_PP(data) != IS_LONG ) {
		zend_error(E_WARNING, "cams_test() - invalid variable type");
		RETURN_NULL();
	}

    outportb((Uint16) Z_LVAL_PP(port), (Uint8) Z_LVAL_PP(data));

	RETVAL_TRUE;
}

ZEND_FUNCTION(cams_inp) {
	zval **port, **data;
	Uint8 value;

	/* check for parameters and address 'em */
	switch (ZEND_NUM_ARGS()) {
		case 2:
			if (zend_get_parameters_ex(2, &port, &data) != SUCCESS) {
				ZEND_WRONG_PARAM_COUNT();
			}
			break;
		default:
			ZEND_WRONG_PARAM_COUNT();
	}

	/* make sure we got the right types passed */
	if ( Z_TYPE_PP(port) != IS_LONG && Z_TYPE_PP(data) != IS_LONG ) {
		zend_error(E_WARNING, "cams_test() - invalid variable type");
		RETURN_NULL();
	}

    value = inportb((Uint16) Z_LVAL_PP(port));
	Z_LVAL_PP(data) = value;

	RETVAL_LONG( value );
}

ZEND_FUNCTION(cams_getport) {
	zval *return_array;
	unsigned int far *ptraddr;  /* Pointer to location of Port Addresses */
	unsigned int address;       /* Address of Port */
	int a;

	MAKE_STD_ZVAL(return_array);

	if(array_init(return_array) != SUCCESS){
		RETURN_FALSE;
	}

	ptraddr = (unsigned int far *)0x00000408;

	for (a = 0; a < 3; a++)
	{
		address = *ptraddr;
		/*
		if (address == 0)
			printf("No port found for LPT%d \n",a+1);
		else
			printf("Address assigned to LPT%d is %Xh\n",a+1,address);
		*/
		add_next_index_long(return_array, address);
		*ptraddr++;
	}
}

/* binary to integer (LE) */
inline int b2i(char *num){
	int retval=0, i=0, j=0, pos=0;

	if(strlen(num) < 1){
		return 0;
	}

	//Little Endian
	i=strlen(num);
	while(i--){
		if(num[pos++] == 49){
			retval += (1 << i);
		}
	}

	return retval;
}

/* integer to binary (LE) */
char *i2b(int num){
	short rvlen=1, rvpos=0;
	int tmp=0;
	char *retval=NULL;

	//evaluate str length
	tmp = num;
	do {
		rvlen++;
	}while( tmp/=2 );

	//alloc and set
	retval = (char*) malloc(rvlen);
	memset(retval, 0, rvlen);

	tmp = num;
	//let str terminator
	rvlen--;
	do {
		retval[--rvlen] = 48+(tmp%2);
	}while( tmp/=2 );

	return retval;
}





/**/