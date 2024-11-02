#!/bin/bash

# функция конвертирует число в число вида NN; Пример: 1 -> 01
num_TT () {
    if [ "$1" -lt 10 ]; then
        TT="0$1"
    else
        TT="$1"
    fi
}

# переходим в папку задачи
cd "$(dirname "${BASH_SOURCE[0]}")"/../.. || exit

# Количество проваленных тестов
counter=0

# pos cases
i=1
num_TT $i
while [ -f ./func_tests/data/pos_"$TT"_in.txt ] \
    && [ -f ./func_tests/data/pos_"$TT"_out.txt ] \
    && [ -f ./func_tests/data/pos_"$TT"_file_in.txt ] \
    && [ -f ./func_tests/data/pos_"$TT"_file_out.txt ] \
    && [ -f ./func_tests/data/pos_"$TT"_args.txt ]; do
    FILE_STDIN=func_tests/data/pos_"$TT"_in.txt
    FILE_STDOUT=func_tests/data/pos_"$TT"_out.txt
    FILE_ARGS=func_tests/data/pos_"$TT"_args.txt
    FILE_IN=func_tests/data/pos_"$TT"_file_in.txt
    FILE_OUT=func_tests/data/pos_"$TT"_file_out.txt

    if ./func_tests/scripts/pos_case.sh "$FILE_STDIN" "$FILE_STDOUT" "$FILE_ARGS" "$FILE_IN" "$FILE_OUT"; then
        echo "POS_TEST $TT - PASSED"
    else
        echo "POS_TEST $TT - FAILED"
        counter=$((counter+1))
    fi

    i=$((i + 1))
    num_TT $i
done
echo

# neg cases
i=1
num_TT $i
while [ -f ./func_tests/data/neg_"$TT"_in.txt ]; do
    FILE_STDIN=func_tests/data/neg_"$TT"_in.txt
    FILE_ARGS=func_tests/data/neg_"$TT"_args.txt
    FILE_IN=func_tests/data/neg_"$TT"_file_in.txt

    if ./func_tests/scripts/neg_case.sh "$FILE_STDIN" "$FILE_ARGS" "$FILE_IN"; then
        echo "NEG_TEST $TT - PASSED"
    else
        echo "NEG_TEST $TT - FAILED"
        counter=$((counter+1))
    fi

    i=$((i+1))
    num_TT $i
done

# exit
exit $counter