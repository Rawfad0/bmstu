#!/bin/bash

# переходим в папку задачи
cd "$(dirname "${BASH_SOURCE[0]}")" || exit

# сборка со статистикой покрытия
gcc -std=c99 -o app.exe *.c -lm --coverage

# сбор данных по тестированию с помощью
./func_tests/scripts/func_tests.sh

# gcov для получения данных в читаемом виде
gcov *