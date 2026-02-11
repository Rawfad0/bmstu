# Равашдех Фадей ИУ7-15Б.
# Ввести трёхмерный массив (массив матриц размера X*Y*Z),
# вывести из него i-й срез (матрицу - фрагмент трёхмерного массива)
# по второму индексу (нумерация индексов начинается с 1).

# Блок ввода
x = int(input('X: '))
while x <= 0:
    print('x<=0')
    x = int(input('X: '))
y = int(input('Y: '))
while y <= 0:
    print('Y<=0')
    y = int(input('Y: '))
z = int(input('Z: '))
while z <= 0:
    print('Z<=0')
    z = int(input('Z: '))
array_3d = [[[0 for i in range(x)] for j in range(y)] for k in range(z)]
for k in range(z):
    print(f'z = {k}')
    for j in range(y):
        line = input(f'{j}: ').split()[:x]
        while len(line) < x:
            line = input(f'{j}: ').split()[:x]
        array_3d[k][j] = [int(i) for i in line]
# for k in range(z):
#     print(k, *array_3d[k], sep='\n')
i_slice = int(input('i_slice matrix (2 id):'))
while i_slice <= 0:
    print('i_slice<=0')
    i_slice = int(input('i_slice matrix (2 id):'))

# Основная часть
matrix = [[array_3d[k][i_slice][i] for i in range(x)] for k in range(z)]

# Блок вывода
print(*matrix, sep='\n')
