#!/bin/bash

# переходим в папку задачи
cd "$(dirname "${BASH_SOURCE[0]}")" || exit

# компиляция
gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -c -g3 *.c

# компоновка
gcc -o app.exe *.o -lm