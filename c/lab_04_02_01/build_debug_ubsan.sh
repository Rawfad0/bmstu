#!/bin/bash

# переходим в папку задачи
cd "$(dirname "${BASH_SOURCE[0]}")" || exit

# сборка с undefined behavior sanitizer
gcc -std=c99 -o app.exe *.c -fsanitize=undefined -fno-omit-frame-pointer -g -lm