# Равашдех Фадей ИУ7-15Б.
# Подсчитать в каждой строке матрицы D кол-во элементов, превышающих суммы элементов соответствующих строк матрицы Z.
# Разместить эти количества в массиве G, умножить матрицу D на максимальный элемент массива G.
# Напечатать матрицу Z, матрицу D до и после преобразования, а также массив G.

# Блок ввода
Dh = int(input('Dh: '))
while Dh <= 0:
    print('Dh<=0')
    Dh = int(input('Dh: '))
Dw = int(input('Dw: '))
while Dw <= 0:
    print('Dw<=0')
    Dw = int(input('Dw: '))
d_matrix = [[0]*Dw]*Dh
for i in range(Dh):
    line = input(f'{i}: ').split()[:Dw]
    while len(line) < Dw:
        line = input(f'{i}: ').split()[:Dw]
    d_matrix[i] = [int(j) for j in line]
print('D', *d_matrix, sep='\n')

Zh = Dh     # По определению
Zw = int(input('Zw: '))
while Zw <= 0:
    print('Zw<=0')
    Zw = int(input('Zw: '))
z_matrix = [[0]*Zw]*Zh
for i in range(Zh):
    line = input(f'{i}: ').split()[:Zw]
    while len(line) < Zw:
        line = input(f'{i}: ').split()[:Zw]
    z_matrix[i] = [int(j) for j in line]
print('Z', *z_matrix, sep='\n')

# Основная часть
z_sum = [0]*Zh
g = [0]*Dh
g_max = None
for i in range(Dh):
    for j in range(Zw):
        z_sum[i] += z_matrix[i][j]
    for j in range(Dw):
        if d_matrix[i][j] > z_sum[i]:
            g[i] += 1
    if g_max is None or g_max < g[i]:
        g_max = g[i]

for i in range(Dh):
    for j in range(Dw):
        d_matrix[i][j] *= g_max

# Блок вывода
print('D:', *d_matrix, sep='\n')
print('G:', g)
