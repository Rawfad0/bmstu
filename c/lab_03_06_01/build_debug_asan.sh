#!/bin/bash

# сборка с address sanitizer
gcc -std=c99 -o app.exe *.c -fsanitize=address -fno-omit-frame-pointer -g -lm
