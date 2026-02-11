"""
Данный скрипт создает файл data/N с заданным количеством (N) уникальных слов.

Запуск:
python3 datagen.py <количество слов>

"""

import sys
import random

# alphabet = "0123456789abcdefghijklmnopqrstuvwxyz"
alphabet = "abcdefghijklmnopqrstuvwxyz"
a_len = len(alphabet)


def int2str(x):
    s = ''
    if (x == 0):
        s += alphabet[0]
    else:
        while x > 0:
            s = alphabet[x % a_len] + s
            x //= a_len
    return s


def gen(n):
    # Создание списка, где каждый элемент от 0 до n записывается P (от a, до b) раз
    word_list = []
    for i in range(n):
            word_list.append(int2str(i))

    # Перемешивание списка
    random.shuffle(word_list)

    # Запись в файл
    with open(f"data/{n}", 'w') as f:
        # f.write('\n'.join(word_list))
        for word in word_list:
            f.write(f"{word}\n")

if __name__ == "__main__":
    if len(sys.argv) > 1:
        gen(int(sys.argv[1]))
    else:
        print("Не введено количество элементов.\n")
