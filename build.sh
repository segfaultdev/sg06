#!/usr/bin/sh

gcc -O3 -s sg06.c -Llib -Iinclude -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o sg06
gcc -O3 -s sgforth.c -Llib -Iinclude -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o sgforth
