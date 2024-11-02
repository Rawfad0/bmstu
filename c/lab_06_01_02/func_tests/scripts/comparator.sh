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

# compare files
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
