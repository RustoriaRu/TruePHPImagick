
#include "ext/standard/php_smart_str.h"
#include "php.h"

PHP_FUNCTION(imagemagick_convert);


const zend_function_entry nw_util_functions[] =
 {
  PHP_FE(imagemagick_convert, NULL)
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

/*
  function: imagemagick_convert
  php parameters:
       1. cmd (String): convert parameters string
       2. result_string (String): out parameter for collect system out buffer
  execution variants:
       1. $res = imagemagick_convert("-version", $rbuf);
       2. $res = imagemagick_convert("-addjoin file1.png file2.png", null);
*/
PHP_FUNCTION(imagemagick_convert)
{
 extern FILE *popen(); // DECLARE LIBRARY FUNCTION

 char		*param;
 int		param_len;
 char		*execstr=NULL;
 int		res=0;
 char		*cmd_pre="convert ", *cmd_post=" 2>&1";
 int		cmd_pre_len=strlen(cmd_pre), cmd_post_len=strlen(cmd_post);
 char		*cptr=NULL;
 zval		*to_zval = NULL;
 FILE		*in;
 char		buff[512];
 smart_str	text = {0};

 // Parse function parameters
 if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|z", &param, &param_len, &to_zval) == FAILURE) {
  return;
 }

 // Allocate formatted exec string
 execstr = malloc(cmd_pre_len+param_len+cmd_post_len+1);
 cptr=execstr;
 // Copy pre, cmd, post to exec string
 memcpy(cptr, cmd_pre, cmd_pre_len);   cptr+=cmd_pre_len;
 memcpy(cptr, param, param_len);       cptr+=param_len;
 memcpy(cptr, cmd_post, cmd_post_len); cptr+=cmd_post_len;
 *cptr='\0';

 // Try to execute exec string
 // popen    http://www.sw-at.com/blog/2011/03/23/popen-execute-shell-command-from-cc/
 if (!(in = popen(execstr, "r")))
  {
   // If out variable defined and type of it STRING
   if (to_zval!=NULL && Z_TYPE_P(to_zval) == IS_STRING)
    {
     // Create STRING object and fill it
     smart_str_append(&text, "Can't open process: ");
     smart_str_append(&text, strerror(errno));
     ZVAL_STRINGL(to_zval, text.c, text.len, 1);
    }
   RETURN_LONG(-1);
  }

 // Reading out buffer to smart string variable
 while (fgets(buff, sizeof(buff), in)!=NULL)
  {
   if (strstr(buff, "command not found")!=NULL)
    res=-1;
   smart_str_appendl(&text, buff, strlen(buff));
  }

 if (to_zval!=NULL && Z_TYPE_P(to_zval) == IS_STRING)
   // Update out variable
   ZVAL_STRINGL(to_zval, text.c, text.len, 1);

 pclose(in);
 free(execstr);

 RETURN_LONG(res);
}
