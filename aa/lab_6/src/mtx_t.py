from random import randint


# ввод матрицы
def input_matrix(size):
    matrix = []
    print("\nВведите матрицу стоимостей:")
    for i in range(size):
        matrix.append([])
        for j in range(size):
            matrix[i].append(int(input()))
    return matrix


# вывод матрицы
def print_matrix(matrix):
    for i in range(len(matrix[0])):
        for j in range(len(matrix[0])):
            print(matrix[i][j], end=" ")
        print("")


# случайная матрица
def get_random_matrix(size, low, top):
    matrix = [[0 for i in range(size)] for j in range(size)]
    for i in range(size):
        for j in range(i + 1, size):
            value = randint(low, top)
            matrix[i][j] = value
            value = randint(low, top)
            matrix[j][i] = value
    return matrix


# матрица из файла
def get_file_matrix(file, size):
    f = open(file, "r")
    matrix = [[0 for i in range(size)] for j in range(size)]
    i = 0
    for row in f.readlines():
        j = 0
        for num in row.split():
            matrix[i][j] = int(num)
            j += 1
        i += 1
    f.close()
    return matrix


# рандом матрица в файл
def write_random_matrix_to_file(filename, size, low, top):
    matrix = get_random_matrix(size, low, top)
    with open(filename, 'w') as file:
        for row in matrix:
            file.write(' '.join(str(elem) for elem in row) + '\n')


write_random_matrix_to_file("../data/m2.txt", 10, 1, 9)
