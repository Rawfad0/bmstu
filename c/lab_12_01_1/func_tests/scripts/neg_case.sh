#!/bin/bash

# parameter: app.exe file_stream_in file_args
EXE=$1
FILE_IN=$2
FILE_OUT=$3
FILE_ARGS=$4

# if app.exe return !0 neg_test passed
if valgrind --leak-check=full -q ./"$EXE" "$FILE_IN" "$FILE_OUT" $(cat "$FILE_ARGS") > /dev/null; then
    exit 1
else
    exit 0
fi
