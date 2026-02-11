# Равашдех Фадей ИУ7-15Б
# Найти максимальное значение в квадратной матрице над главной диагональю и минимальное - под побочной диагональю.

# Блок ввода
n = int(input('Введите размер квадратной матрицы: '))

while n <= 0:
    print('Размер должен быть больше 0.')
    n = int(input('Введите размер квадратной матрицы: '))

int_matrix = [[0]*n]*n
print('Вводите элементы построчно через пробел: ')
for i in range(n):
    line = input(f'{i}: ').split()[:n]
    int_matrix[i] = [int(j) for j in line]

print('Введённая матрица: ')
for line in int_matrix:
    print(line)

# Основная часть
mn = None
mx = None
for i in range(n):
    for j in range(n):
        if i == j:
            continue
        elif i < j and (mx is None or int_matrix[i][j] > mx):
            mx = int_matrix[i][j]
        elif i > j and (mn is None or int_matrix[i][j] < mn):
            mn = int_matrix[i][j]

# Блок вывода
print('MIN:', mn)
print('MAX:', mx)
