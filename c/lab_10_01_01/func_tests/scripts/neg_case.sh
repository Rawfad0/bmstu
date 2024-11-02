#!/bin/bash

# parameter: file_stream_in file_args
FILE_STDIN=$1

# if app.exe return !0 neg_test passed
if ./app.exe "$FILE_IN" /dev/null; then
    exit 1
else
    exit 0
fi
