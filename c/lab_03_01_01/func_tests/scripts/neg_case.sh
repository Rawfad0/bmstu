#!/bin/bash

# parameter: file_stream_in
FILE_IN=$1

# if app.exe return !0 neg_test passed
if ./app.exe < "$FILE_IN" > /dev/null; then
    exit 1;
else
    exit 0;
fi