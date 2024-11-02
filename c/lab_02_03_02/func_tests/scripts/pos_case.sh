#!/bin/bash

# parameters: file_stream_in file_stream_out_expect
FILE_IN=$1
FILE_OUT_EXP=$2

# temp file for file_stream_out
temp=$(basename "$0")
TEMPFILE=$(mktemp /tmp/"$temp".XXXXXX)
trap 'rm -f $TEMPFILE' EXIT

# file_stream_in -> app.exe -> TEMPFILE
./app.exe < "$FILE_IN" > "$TEMPFILE"

# comparator
if ./func_tests/scripts/comparator.sh "$TEMPFILE" "$FILE_OUT_EXP"; then
    exit 0;
else
    exit 1;
fi
