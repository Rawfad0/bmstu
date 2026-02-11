"""
Данный скрипт создает файл data/N с заданным количеством (N) уникальных слов, 
каждое из которых повторяется в разросе P раз.

Запуск:
python3 datagen.py <количество слов>

"""

import sys
import random

# Разброс количества повторений на слово
P = (1, 7)


def gen(n):
    # Создание списка, где каждый элемент от 0 до n записывается P (от a, до b) раз
    word_list = []
    for i in range(n):
        for j in range(random.randint(*P)):
            word_list.append(str(i))

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

