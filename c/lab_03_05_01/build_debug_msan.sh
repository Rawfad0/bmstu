#!/bin/bash

# сборка с memory sanitizer
clang -std=c99 -o app.exe *.c -fsanitize=memory -fPIE -pie -fno-omit-frame-pointer -g -lm