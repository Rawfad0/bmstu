#!/bin/bash

# компиляция
gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -c *.c

# компоновка
gcc -o app.exe *.o -lm