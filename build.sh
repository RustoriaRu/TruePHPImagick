#!/bin/sh

phpize
./configure --enable-nw_util
make
make install