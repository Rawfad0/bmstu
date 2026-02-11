# Равашдех Фадей ИУ7-15Б
# Найти минимум в матрице, обнулить строки и столбцы на пересечении которых находится значение совпадающее с минимумом

# Блок ввода
w = int(input('Ширина: '))
while w <= 0:
    w = int(input('Ширина: '))
h = int(input('Высота: '))
while h <= 0:
    h = int(input('Высота: '))
matrix = [[0 for i in range(w)] for j in range(h)]
for i in range(h):
    line = input(f'{i}: ').split()
    matrix[i] = [int(j) for j in line]
print(*matrix, sep='\n')

# Основная часть
min_ids = []
m_min = None
for i in range(h):
    for j in range(w):
        if m_min is None or matrix[i][j] < m_min:
            m_min = matrix[i][j]
            min_ids = [[i, j]]
        elif matrix[i][j] == m_min:
            min_ids.append([i, j])
# print(min_ids)
for pair in min_ids:
    y = pair[0]
    x = pair[1]
    matrix[y] = [0]*w
    for i in range(w):
        matrix[i][x] = 0
    # print(*matrix, '', sep='\n')

# Блок вывода
print('Результат:', *matrix, sep='\n')
