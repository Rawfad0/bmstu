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
    && [ -f ./func_tests/data/pos_"$TT"_args.txt ]; do
    FILE_IN=func_tests/data/pos_"$TT"_in.txt
    FILE_OUT=func_tests/data/pos_"$TT"_out.txt
    FILE_ARGS=func_tests/data/pos_"$TT"_args.txt

    if ./func_tests/scripts/pos_case.sh "$FILE_IN" "$FILE_OUT" "$FILE_ARGS"; then
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
while [ -f ./func_tests/data/neg_"$TT"_in.txt ] \
    && [ -f ./func_tests/data/neg_"$TT"_out.txt ] \
    && [ -f ./func_tests/data/neg_"$TT"_args.txt ]; do
    FILE_IN=func_tests/data/neg_"$TT"_in.txt
    FILE_OUT=func_tests/data/neg_"$TT"_out.txt
    FILE_ARGS=func_tests/data/neg_"$TT"_args.txt

    if ./func_tests/scripts/neg_case.sh "$FILE_IN" "$FILE_OUT" "$FILE_ARGS"; then
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
