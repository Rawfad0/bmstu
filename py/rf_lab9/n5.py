# Равашдех Фадей ИУ7-15Б.
# Дана матрица символов. Заменить в ней все гласные английские буквы на точки.
# Напечатать матрицу до и после преобразования.

# Блок ввода
h = int(input('h: '))
while h <= 0:
    print('h<=0')
    h = int(input('h: '))
w = int(input('w: '))
while w <= 0:
    print('w <= 0')
    w = int(input('w: '))
matrix = [['']*w]*h
for i in range(h):
    line = input(f'{i}: ')[:w]
    while len(line) < w:
        line = input(f'{i}: ')[:w]
    matrix[i] = list(line)
print(*matrix, sep='\n')

# Основная часть
vowels = 'aeiouAEIOU'
for i in range(h):
    for j in range(w):
        if matrix[i][j] in vowels:
            matrix[i][j] = '.'

# Блок вывода
print(*matrix, sep='\n')
