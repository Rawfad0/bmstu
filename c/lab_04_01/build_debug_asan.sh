#!/bin/bash

# переходим в папку задачи
cd "$(dirname "${BASH_SOURCE[0]}")" || exit

# сборка с address sanitizer
gcc -std=c99 -o app.exe *.c -fsanitize=address -fno-omit-frame-pointer -g -lm
