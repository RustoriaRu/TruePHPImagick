#!/bin/sh

php -c /etc/php.ini -r "echo \"PHP RUNING TEST:\";"
php -c /etc/php.ini -r "echo \"[\".imagemagick_convert(\"$1\").\"]\n\";"