#!/bin/bash
echo_verbose () {
        if [ $v -eq 1 ]; then
                echo "$1"
        fi
}

usage () {
        [ $v -eq 1 ] && echo "Использование: $PROGNAME file1 file2 [-v]"
        exit 2
}

# parameters
FILE1=""
FILE2=""
v=0
while [[ -n $1 ]]; do
        if [ "$1" == "-v" ]; then
                v=1
                break
        elif [ -z "$FILE1" ]; then
                FILE1=$1
                shift
        elif [ -z "$FILE2" ]; then
                FILE2=$1
                shift
        else
                usage
        fi
done

# check filenames
if [ -z "$FILE1" ]; then
        usage
elif [ -z "$FILE2" ]; then
        usage
fi

# check file exists
[ ! -f "$FILE1" ] && exit 3
[ ! -f "$FILE2" ] && exit 3

# check readable
[ ! -r "$FILE1" ] && exit 3
[ ! -r "$FILE2" ] && exit 3

# # temp files
# temp=$(basename "$0")
# TEMPFILE1=$(mktemp /tmp/"$temp"1.XXXXXX)
# trap 'rm -f $TEMPFILE1' EXIT
# TEMPFILE2=$(mktemp /tmp/"$temp"2.XXXXXX)
# trap 'rm -f $TEMPFILE2' EXIT

# # descriptors
# exec 4<>"$FILE1"
# exec 5<>"$FILE2"
# exec 6<>"$TEMPFILE1"
# exec 7<>"$TEMPFILE2"

# # fill tempfile1
# flag=0
# while read -u 4 -r || [[ -n $REPLY ]]; do
#         if [ $flag -eq 0 ]; then
#                 if echo "$REPLY" | grep -q "Result: "; then
#                         LINE=$REPLY
#                         LINESTART=""
#                         LINEEND=""
#                         while read -n 1; do
#                                 LINESTART=$LINESTART$REPLY
#                                 if echo "$LINESTART" | grep -q "Result: "; then
#                                         LINEEND=$LINEEND$REPLY
#                                 fi
#                         done <<< "$LINE"
#                         echo_verbose "$LINEEND"
#                         echo "$LINEEND" >&6
#                 flag=1
#                 fi
#         elif [ $flag -eq 1 ]; then
#                 echo_verbose "$REPLY"
#                 echo "$REPLY" >&6
#         fi
# done

# # fill tempfile2
# flag=0
# while read -u 5 -r || [[ -n $REPLY ]]; do
#         if [ $flag -eq 0 ]; then
#                 if echo "$REPLY" | grep -q "Result: "; then
#                         LINE=$REPLY
#                         LINESTART=""
#                         LINEEND=""
#                         while read -n 1; do
#                                 LINESTART=$LINESTART$REPLY
#                                 if echo "$LINESTART" | grep -q "Result: "; then
#                                         LINEEND=$LINEEND$REPLY
#                                 fi
#                         done <<< "$LINE"
#                         echo_verbose "$LINEEND"
#                         echo "$LINEEND" >&7
#                 flag=1
#                 fi
#         elif [ $flag -eq 1 ]; then
#                 echo_verbose "$REPLY"
#                 echo "$REPLY" >&7
#         fi
# done

# # compare tempfiles
# opt='-s'
# if [ $v -eq 1 ]; then
#         opt=''
# fi
# if cmp $opt "$TEMPFILE1" "$TEMPFILE2"; then
#         echo_verbose "Последовательности совпали"
#         exit 0
# else
#         echo_verbose "Последовательности не совпали"
#         exit 1
# fi

# compare tempfiles
opt='-s'
if [ $v -eq 1 ]; then
        opt=''
fi
if cmp $opt "$FILE1" "$FILE2"; then
        echo_verbose "Последовательности совпали"
        exit 0
else
        echo_verbose "Последовательности не совпали"
        exit 1
fi
