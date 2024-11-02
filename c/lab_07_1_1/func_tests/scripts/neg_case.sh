#!/bin/bash

# parameter: file_stream_in file_args
FILE_IN=$1
FILE_OUT=$2
FILE_ARGS=$3

# if app.exe return !0 neg_test passed
if ./app.exe "$FILE_IN" "$FILE_OUT" $(cat "$FILE_ARGS") > /dev/null; then
    exit 1
else
    exit 0
fi
