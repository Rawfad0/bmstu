# Равашдех Фадей ИУ7-15Б
# Переставить местами строки с наибольшим и наименьшим количеством отрицательных элементов.

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
mx_i = None         # Номер строки с наибольшим количеством отрицательных чисел
mx_counter = None   # Наибольшее количество отрицательных чисел
mn_i = None         # Номер строки с наименьшим количеством отрицательных чисел
mn_counter = None   # Наименьшее количество отрицательных чисел
for i in range(h):
    counter = 0     # Счётчик соответствующих элементов в строке
    for j in int_matrix[i]:
        if j < 0:   # Элемент меньше нуля
            counter += 1
    if (mn_counter is None) or counter < mn_counter:    # Если нашлось новое наименьшее
        mn_counter = counter
        mn_i = i
    if (mx_counter is None) or mx_counter < counter:    # Если нашлось новое наибольшее
        mx_counter = counter
        mx_i = i

if not (mn_i is None) or not (mx_i is None) or mn_i != mx_i:    # Посимвольная перестановка элементов двух строк
    # int_matrix[mn_i], int_matrix[mx_i] = int_matrix[mx_i], int_matrix[mn_i]
    for i in range(w):
        int_matrix[mn_i][i], int_matrix[mx_i][i] = int_matrix[mx_i][i], int_matrix[mn_i][i]

# Блок вывода
print('Результат: ')
for line in int_matrix:
    print(*line)
