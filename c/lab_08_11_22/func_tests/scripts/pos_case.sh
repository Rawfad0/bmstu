#!/bin/bash

# parameters: file_stream_in file_stream_out_expect file_args
FILE_IN=$1
FILE_OUT_EXP=$2
FILE_ARGS=$3

# temp file for file_stream_out
temp=$(basename "$0")
TEMPFILE=$(mktemp /tmp/"$temp".XXXXXX)
trap 'rm -f $TEMPFILE' EXIT

# file_stream_in -> app.exe args -> TEMPFILE
#        file_in -> app.exe args -> file_out
if !(valgrind --leak-check=full --show-leak-kinds=all -q ./app.exe $(cat "$FILE_ARGS") "$FILE_IN" "$TEMPFILE"); then
    exit 2
fi

# comparator
if ./func_tests/scripts/comparator.sh "$TEMPFILE" "$FILE_OUT_EXP" ; then 
    exit 0
fi
exit 1
