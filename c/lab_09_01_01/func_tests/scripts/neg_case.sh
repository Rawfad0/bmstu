#!/bin/bash

# parameter: file_stream_in file_args
FILE_IN=$1
FILE_ARGS=$2

# if app.exe return !0 neg_test passed
if valgrind --leak-check=full --show-leak-kinds=all -q ./app.exe "$FILE_IN" $(cat "$FILE_ARGS"); then
    exit 1
else
    exit 0
fi
