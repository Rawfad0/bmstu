"""
Данный скрипт создает файл data/N с матрицей смежности графа на заданном количестве вершин N.

Запуск:
python3 graphgen.py <количество вершин>

"""

import sys
import random


def gen(n):
    # Создание матрицы смежности свзяности графа
    matrix = [[0]*n for i in range(n)]
    for i in range(n):
        for j in range(n):
            if j < i:
                matrix[i][j] = matrix[j][i]
            elif j > i:
                matrix[i][j] = random.randint(1, 20)
            else:
                matrix[i][j] = 0

    # Вывод матрицы смежности
    if n < 20:
        print("Матрица смежности графа:")
        for i in range(n):
            for j in range(n):
                print(f"{str(matrix[i][j]):>2}", end=' ')
            print()

    # Запись в файл
    with open(f"data/{n}", 'w') as f:
        f.write(f"{n} {n} {n*(n - 1)}\n")
        for i in range(n):
            for j in range(n):
                if i != j:
                    f.write(f"{i} {j} {matrix[i][j]}\n") 
    print("Записана в файл " + f"data/{n}")

if __name__ == "__main__":
    if len(sys.argv) > 1:
        gen(int(sys.argv[1]))
    else:
        print("Не введено количество элементов.\n")
