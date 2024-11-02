#!/bin/bash

# parameter: file_stream_in file_args
FILE_IN=$1
FILE_OUT=$2
FILE_ARGS=$3

# if app.exe return !0 neg_test passed
if valgrind --leak-check=full --show-leak-kinds=all -q ./app.exe $(cat "$FILE_ARGS") "$FILE_IN" "$FILE_OUT" > /dev/null; then
    exit 1
else
    exit 0
fi
