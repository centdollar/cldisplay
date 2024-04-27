#!/bin/sh

Compiler_opts="-Wall -Wextra -Werror"

gcc $Compiler_opts -o cldisplay cldisplay.c 

./cldisplay
