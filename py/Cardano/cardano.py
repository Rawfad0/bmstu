import os
import random


def create_matrix8x8():
    matrix8x8 = [[0 for i in range(8)] for j in range(8)]
    for i in range(4):
        for j in range(4):
            matrix8x8[i][j] = 4*i + j + 1
            matrix8x8[j][7 - i] = 4 * i + j + 1
            matrix8x8[7 - j][i] = 4 * i + j + 1
            matrix8x8[7 - i][7 - j] = 4 * i + j + 1
    print(*matrix8x8, sep='\n')
    return matrix8x8


def matrix_rotate(matrix):
    l = len(matrix)
    rotated_matrix = [[matrix[l - 1 - i][j] for i in range(l)] for j in range(l)]
    return rotated_matrix


def create_8x8_matrix():
    matrix = []
    counter = 1
    for i in range(4):
        matrix.append([])
        for j in range(4):
            matrix[i].append(counter)
            counter += 1
    # print(*matrix, sep='\n')
    matrix8x8 = [[0 for i in range(8)] for j in range(8)]
    for i in range(4):
        for j in range(4):
            matrix8x8[i][j] = matrix[i][j]
    matrix = matrix_rotate(matrix)
    for i in range(4):
        for j in range(4):
            matrix8x8[i][j + 4] = matrix[i][j]
    matrix = matrix_rotate(matrix)
    for i in range(4):
        for j in range(4):
            matrix8x8[i + 4][j + 4] = matrix[i][j]
    matrix = matrix_rotate(matrix)
    for i in range(4):
        for j in range(4):
            matrix8x8[i + 4][j] = matrix[i][j]
    # print(*matrix8x8, sep='\n')
    return matrix8x8


def choose_16():
    zero_matrix8x8 = [['0' for i in range(8)] for j in range(8)]
    for i in range(4):
        for j in range(4):
            ch_i, ch_j = [(i, j), (j, 7 - i), (7 - j, i), (7 - i, 7 - j)][random.randint(0, 3)]
            zero_matrix8x8[ch_i][ch_j] = '1'
    # print(*zero_matrix8x8, sep='\n')
    return zero_matrix8x8


def key_encode(matrix):
    key_array = []
    for i in range(8):
        key_array.append(int(''.join(matrix[i]), 2))
    return key_array


def key_decode(key_array):
    matrix = [list(bin(key_array[i]))[2:] for i in range(8)]
    for i in range(8):
        line = bin(key_array[i])[2:]
        line = (8 - len(line))*'0'+line
        matrix[i] = list(line)
    # print(*matrix, sep='\n')
    return matrix


def write_key(path, key_array):
    with open(path, 'w') as f:
        for key in key_array:
            f.write(str(key)+'\n')


def read_key(path):
    key_array = [0]*8
    with open(path, 'r') as f:
        for i in range(8):
            key_array[i] = int(f.readline())
    return key_array


def read_message(path):
    text = ['']*4
    counter64 = 0
    counter = 0
    with open(path, 'r', encoding='UTF-8') as f:
        while line := f.readline():
            line = line.rstrip('\n')
            for ch in line:
                if ch.isalpha():
                    counter += 1
                    text[counter64] += ch
                    if counter == 64:
                        counter = 0
                        counter64 += 1
                        if counter64 == 4:
                            # print(*text, sep='\n')
                            return text
    for i in range(4):
        text[i] = text[i] + ' '*(64 - len(text[i]))
    return text     # -> ['', '', '', '']


def message_encode(message, key_array):
    # alphabet = 'абвгдеёжзийклмнопрстуфхцчшщьъыэюяАБВГДЕЁЖЗИЁКЛМНОПРСТУФХЦЧШЩЬЪЫЭЮЯ'
    alphabet = 'абвгдеёжзийклмнопрстуфхцчшщьъыэюя'
    key_matrix = key_decode(key_array)
    matrix = [['.' for i in range(8)] for j in range(8)]
    # for p in range(4):
    for k in range(4):
        for i in range(4):
            for j in range(4):
                for pair in [(i, j), (j, 7 - i), (7 - j, i), (7 - i, 7 - j)]:
                    if key_matrix[pair[0]][pair[1]] == '1':
                        if message[k][4*i + j] == ' ':
                            matrix[pair[0]][pair[1]] = random.choice(list(alphabet))
                        else:
                            matrix[pair[0]][pair[1]] = message[k][4*i + j]
        key_matrix = matrix_rotate(key_matrix)
    return matrix


def write_encoded_message(path, matrix):
    with open(f'encoded{path}', 'w') as f:
        for i in range(8):
            f.write(''.join(matrix[i])+'\n')


while inp_path := input('Введите путь к сообщению (пустая строка для выхода): '):
    if os.path.exists(inp_path):
        mtrx = choose_16()
        print(*mtrx, sep='\n')
        key_arr = key_encode(mtrx)
        write_key(f'key{inp_path}.txt', key_arr)
        print('Ключ:\n', key_arr)
        msg = read_message(inp_path)
        print('Подготовленное сообщение: ', *msg, sep='\n')
        key_arr = read_key(f'key{inp_path}.txt')
        encoded_message = message_encode(msg, key_arr)
        print('Закодированное сообщение: ', *encoded_message, sep='\n')
        write_encoded_message(inp_path, encoded_message)
        print(f'Закодированное сообщение сохранено в файл encoded{inp_path}')
    elif inp_path == '':
        break
    else:
        print('Файл не найден.')
print('Программа завершена.')
