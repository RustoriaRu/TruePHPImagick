#!/bin/sh

php -c /etc/php.ini -r "echo \"PHP RUNING TEST:\n\";"
#php -c /etc/php.ini -r "echo \"[\".imagemagick_convert(\"$1\").\"]\n\";"
php -c /etc/php.ini -r "\$a = ''; \$res = imagemagick_convert(\"$1\", \$a); echo \"a: [\$a]\n\"; echo \"res: \$res\n\"; "
php -c /etc/php.ini -r "\$a = ''; \$res = imagemagick_convert(\"$1\", null); echo \"a: [\$a]\n\"; echo \"res: \$res\n\"; "