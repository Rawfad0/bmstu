#!/bin/bash

# parameter: file_stream_in file_args
FILE_IN=$1
FILE_ARGS=$2

# if app.exe return !0 neg_test passed
if ./app.exe "$(cat "$FILE_ARGS")" < "$FILE_IN" > /dev/null; then
    exit 1;
else
    exit 0;
fi