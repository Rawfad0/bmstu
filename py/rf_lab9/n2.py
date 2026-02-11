# Равашдех Фадей ИУ7-15Б.
# Повернуть квадратную целочисленную матрицу на 90 градусов по часовой
# стрелке, затем на 90 градусов против часовой стрелки. Вывести исходную,
# промежуточную и итоговую матрицы. Дополнительных матриц и массивов не
# вводить. Транспонирование не применять.

# Блок ввода
n = int(input('n: '))
while n <= 0:
    print('n<=0')
    n = int(input('n: '))
matrix = [[0]*n]*n
for i in range(n):
    line = input(f'{i}: ').split()[:n]
    while len(line) < n:
        line = input(f'{i}: ').split()[:n]
    matrix[i] = [int(j) for j in line]
print('Начальная:', *matrix, sep='\n')

# Основная часть
for i in range(n//2):
    for j in range(n - 2*i - 1):
        matrix[i][i + j], matrix[i + j][n - 1 - i], matrix[n - 1 - i][n - 1 - i - j], matrix[n - 1 - i - j][i] = \
            matrix[n - 1 - i - j][i], matrix[i][i + j], matrix[i + j][n - 1 - i], matrix[n - 1 - i][n - 1 - i - j]
print('По часовой: ', *matrix, sep='\n')
for i in range(n//2):
    for j in range(n - 2*i - 1):
        matrix[i][i + j], matrix[i + j][n - 1 - i], matrix[n - 1 - i][n - 1 - i - j], matrix[n - 1 - i - j][i] = \
            matrix[n - 1 - i][n - 1 - i - j], matrix[n - 1 - i - j][i], matrix[i][i + j], matrix[i + j][n - 1 - i]

# Блок вывода
print('Против часовой (на 180):', *matrix, sep='\n')
