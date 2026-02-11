#!/bin/bash

# Скрипт сборки программы

# переходим в папку задачи
cd "$(dirname "${BASH_SOURCE[0]}")" || exit

# компиляция
gcc -std=c99 -Wall -Werror -Wfloat-equal -Wfloat-conversion -c *.c

# компоновка
gcc -o app.exe *.o -lm

# удаление объектных файлов 
rm *.o
