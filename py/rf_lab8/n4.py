# Равашдех Фадей ИУ7-15Б
# Переставить местами столбцы с максимальной и минимальной суммой элементов.

# Блок ввода
w = int(input('Введите количество элементов в строке: '))
h = int(input('Введите количество элементов в столбце: '))

while w <= 0:
    print('Количество элементов в строке должно быть больше 0.')
    w = int(input('Введите количество элементов списка: '))
while h <= 0:
    print('Количество элементов в строке должно быть больше 0.')
    h = int(input('Введите количество элементов списка: '))

int_matrix = [[0]*w]*h
print('Вводите элементы построчно через пробел: ')
for i in range(h):
    line = input(f'{i}: ').split()[:w]
    int_matrix[i] = [int(j) for j in line]

print('Введённая матрица: ')
for line in int_matrix:
    print(line)

# Основная часть
mn_sum = None
mn_i = None
mx_sum = None
mx_i = None
for i in range(w):
    col_sum = 0
    for j in range(h):
        col_sum += int_matrix[j][i]
    if mn_sum is None or col_sum < mn_sum:
        mn_sum = col_sum
        mn_i = i
    if mx_sum is None or col_sum > mx_sum:
        mx_sum = col_sum
        mx_i = i

if not (mn_i is None) or not (mx_i is None) or mn_i != mx_i:
    for i in range(h):
        int_matrix[i][mn_i], int_matrix[i][mx_i] = int_matrix[i][mx_i], int_matrix[i][mn_i]

# Блок вывода
print('Результат: ')
for line in int_matrix:
    print(*line)
