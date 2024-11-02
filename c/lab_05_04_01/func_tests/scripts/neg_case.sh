#!/bin/bash

# parameter: file_stream_in file_args file_in
FILE_STDIN=$1
FILE_ARGS=$2
FILE_IN=$3

# text in_file to bin in_file
./app.exe "t2b" "$FILE_IN" file_in.bin

# if app.exe return !0 neg_test passed
if ./app.exe $(cat "$FILE_ARGS") < "$FILE_STDIN" > /dev/null; then
    exit 1
else
    exit 0
fi