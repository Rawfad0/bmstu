#!/bin/bash
for i in 16 32 64 128 256 512 1024; do
    echo "=== $i connections ==="
    ./load_test1 $i /1 >> ./res/1.csv
done
