#!/usr/bin/env python3
import os
import sys

def usage():
    print('Usage: ./file_gen.py <путь_к_файлу> <размер_в_МБ>\nExample: "./file_gen.py files/128 128"')
    sys.exit(1)

if len(sys.argv) != 3:
    usage()

filename = sys.argv[1]
try:
    size_mb = int(sys.argv[2])
except ValueError:
    usage()

size_bytes = size_mb * 1024 * 1024
dir_path = os.path.dirname(filename)
if dir_path:
    os.makedirs(dir_path, exist_ok=True)

with open(filename, "wb") as f:
    for _ in range(size_mb):
        f.write(os.urandom(1024 * 1024))

print(f"Файл {filename} размером {size_mb} МБ создан")
