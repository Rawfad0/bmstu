# Равашдех Фадей ИУ7-15Б.
# Сформировать матрицу A по формуле ajk = sin(dj+fk). Определить среднее арифметическое положительных чисел
# каждой строки матрицы и количество элементов, меньших среднего арифметического.
# Результаты записать соответственно в массивы AV и L. Напечатать матрицу A в виде матрицы и рядом столбцы AV и L.

import math

# Блок ввода
dn = int(input('Len(D): '))     # rows
while dn <= 0:
    print('dn<=0')
    dn = int(input('Len(D): '))
d = [0]*dn
for i in range(dn):
    d[i] = int(input(f'{i}: '))
fn = int(input('Len(F): '))     # columns
while fn <= 0:
    print('fn<=0')
    fn = int(input('Len(F): '))
f = [0]*fn
for i in range(fn):
    f[i] = int(input(f'{i}: '))

# Основная часть
a = [[0.0 for k in range(fn)] for j in range(dn)]
AV = [0.0]*dn
L = [0]*dn
for j in range(dn):
    for k in range(fn):
        a[j][k] = math.sin(d[j] + f[k])
        AV[j] += a[j][k]
    AV[j] /= fn
    for k in range(fn):
        if a[j][k] < AV[j]:
            L[j] += 1

# Блок вывода
# for j in range(dn):
#     print(*a[j], AV[j], L[j])
for j in range(dn):
    print(f'{j:2}', end=' ')
    for k in range(fn):
        print(f'{a[j][k]: 10.7g}', end=' ')
    print(f'{AV[j]: .7g}', f'{L[j]:2}')
