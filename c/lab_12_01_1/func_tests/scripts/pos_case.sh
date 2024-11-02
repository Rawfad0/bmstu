#!/bin/bash

# parameters: app.exe file_stream_in file_stream_out_expect file_args
EXE=$1
FILE_IN=$2
FILE_OUT_EXP=$3
FILE_ARGS=$4

# temp file for file_stream_out
temp=$(basename "$0")
TEMPFILE=$(mktemp /tmp/"$temp".XXXXXX)
trap 'rm -f $TEMPFILE' EXIT

# file_stream_in -> app.exe args -> TEMPFILE
#        file_in -> app.exe args -> file_out
if ! (valgrind --leak-check=full -q ./"$EXE" "$FILE_IN" "$TEMPFILE" $(cat "$FILE_ARGS")) ; then
    exit 2
fi

# comparator
if ./func_tests/scripts/comparator.sh "$TEMPFILE" "$FILE_OUT_EXP" ; then 
    exit 0
fi
exit 1

