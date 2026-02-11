# Равашдех Фадей ИУ7-15Б.
# Сформировать матрицу C путём построчного перемножения матриц A и B одинаковой размерности
# (элементы в i-й строке матрицы A умножаются на соответствующие элементы в i-й строке матрицы B),
# потом сложить все элементы в столбцах матрицы C и записать их в массив V. Напечатать матрицы A, B, C и массив V.

# Блок ввода
h = int(input('h: '))
while h <= 0:
    print('h<=0')
    h = int(input('h: '))
w = int(input('w: '))
while w <= 0:
    print('w<=0')
    w = int(input('w: '))
a_matrix = [[0]*w]*h
for i in range(h):
    line = input(f'{i}: ').split()[:w]
    while len(line) < w:
        line = input(f'{i}: ').split()[:w]
    a_matrix[i] = [int(j) for j in line]
print('A', *a_matrix, sep='\n')

b_matrix = [[0]*w]*h
for i in range(h):
    line = input(f'{i}: ').split()[:w]
    while len(line) < w:
        line = input(f'{i}: ').split()[:w]
    b_matrix[i] = [int(j) for j in line]
print('B', *b_matrix, sep='\n')

# Основная часть
c_matrix = [[0 for j in range(w)] for i in range(h)]
v_array = [0]*w
for i in range(h):
    for j in range(w):
        c_matrix[i][j] = a_matrix[i][j]*b_matrix[i][j]
        v_array[j] += c_matrix[i][j]

# Блок вывода
print('C: ', *c_matrix, sep='\n')
print('V: ', v_array, sep='\n')
