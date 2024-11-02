#!/bin/bash

# сборка с undefined behavior sanitizer
gcc -std=c99 -o app.exe *.c -fsanitize=undefined -fno-omit-frame-pointer -g -lm