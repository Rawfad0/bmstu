#!/bin/bash

# parameters: file_stream_in file_stream_out_expect file_args file_in file_out_expect
FILE_STDIN=$1
FILE_STDOUT_EXP=$2
FILE_ARGS=$3
FILE_IN=$4
FILE_OUT_EXP=$5

# temp file for file_stream_out
temp=$(basename "$0")
TEMPFILE=$(mktemp /tmp/"$temp".XXXXXX)
trap 'rm -f $TEMPFILE' EXIT

# text in_file to bin in_file
./app.exe "t2b" "$FILE_IN" file_in.bin

# file_stream_in -> app.exe args -> TEMPFILE
#        file_in -> app.exe args -> file_out
./app.exe "$(cat "$FILE_ARGS")" < "$FILE_STDIN" > "$TEMPFILE"

# bin out_file to text out_file
if [ -f file_out.bin ]; then
    ./app.exe "b2t" file_out.bin file_out.txt 
fi

# comparator
if [ -f file_out.bin ]; then
    if ./func_tests/scripts/comparator.sh "$TEMPFILE" "$FILE_STDOUT_EXP" && \
        ./func_tests/scripts/comparator.sh "file_out.txt" "$FILE_OUT_EXP" ; then
        exit 0;
    fi
else
    if ./func_tests/scripts/comparator.sh "$TEMPFILE" "$FILE_STDOUT_EXP" ; then 
        exit 0;
    fi
fi
exit 1;
