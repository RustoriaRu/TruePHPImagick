#!/bin/sh

php -c /etc/php.ini -r "echo \"PHP RUNING TEST:\";"
php -c /etc/php.ini -r "echo \"[\".imagemagic_convert(\"$1\").\"]\n\";"