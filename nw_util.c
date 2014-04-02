#include "php.h"

PHP_FUNCTION(imagemagic_convert);


const zend_function_entry nw_util_functions[] =
 {
  PHP_FE(imagemagic_convert, NULL)
  {NULL, NULL, NULL}
 };

zend_module_entry nw_util_module_entry =
 {
  STANDARD_MODULE_HEADER,
  "nw_util",
  nw_util_functions,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NO_VERSION_YET,
  STANDARD_MODULE_PROPERTIES
 };
 
ZEND_GET_MODULE(nw_util);

PHP_FUNCTION(imagemagic_convert)
{
 char	*params;
 int	plen;
 char	*execstr=NULL;
 int	res=0;
 char	*cmd="convert ", *pcmd=" > /dev/null 2>&1";
 int	clen=strlen(cmd), pclen=strlen(pcmd);
 char	*cptr=NULL;

 if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &params, &plen) == FAILURE) {
  return;
 }
 
 execstr = malloc(plen+clen+pclen+1);
 cptr=execstr;
 memcpy(cptr, cmd, clen); cptr+=clen;
 memcpy(cptr, params, plen); cptr+=plen;
 memcpy(cptr, pcmd, pclen); cptr+=pclen;
// printf("execstr: [%s]\n", execstr);
 *cptr='\0';
 
 // popen    http://www.sw-at.com/blog/2011/03/23/popen-execute-shell-command-from-cc/
 
 res = system(execstr);
 free(execstr);
// printf("res: %d\n", res);
// RETURN_STRING(params, 1);
 RETURN_LONG(res);
// RETURN_STRING(execstr, 1);
}
