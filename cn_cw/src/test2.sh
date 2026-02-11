#!/bin/bash
for i in 4 8 16 32 64 100; do
    echo "=== $i connections ==="
    ./load_test2 $i /1 >> ./res/2_8.csv
done
