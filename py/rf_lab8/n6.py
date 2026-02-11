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
for i in range(n):
    for j in range(i, n):
        int_matrix[i][j], int_matrix[j][i] = int_matrix[j][i], int_matrix[i][j]

# Блок вывода
print('Результат: ')
for line in int_matrix:
    print(line)
