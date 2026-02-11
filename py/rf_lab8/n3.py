# Равашдех Фадей ИУ7-15Б
# Найти столбец, имеющий определённое свойство по варианту.
# 2. Наименьшее количество отрицательных элементов.

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
m_counter = None
m_i = None
for i in range(w):
    counter = 0
    for j in range(h):
        if int_matrix[j][i] < 0:
            counter += 1
    if m_counter is None or counter < m_counter:
        m_counter = counter
        m_i = i

# Блок вывода
print('Найденный столбец: ')
for i in range(h):
    print(int_matrix[i][m_i])
