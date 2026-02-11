# Равашдех Фадей ИУ7-15Б.
# Задана матрица D и массив I, содержащий номера строк, для которых необходимо определить максимальный элемент.
# Значения максимальных элементов запомнить в массиве R.
# Определить среднее арифметическое вычисленных максимальных значений.
# Напечатать матрицу D, массивы I и R, среднее арифметическое значение.

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
print('D:', *d_matrix, sep='\n')

In = int(input('In: '))
while In <= 0:
    print('In<=0')
    In = int(input('In: '))
i_list = [0]*In
for i in range(In):
    x = int(input(f'{i}: '))
    while x < 0 or x >= Dh:
        x = int(input(f'{i}: '))
    i_list[i] = x
print('I:', i_list)

# Основная часть
r_list = [0]*In
r_sum = 0
for ii in range(In):
    i = i_list[ii]
    for j in range(Dw):
        x = d_matrix[i][j]
        if j == 0:
            r_list[ii] = x
        if r_list[ii] < x:
            r_list[ii] = x
    r_sum += r_list[ii]
r_sum /= In

# Блок вывода
print('R:', r_list)
print('R average:', r_sum)
