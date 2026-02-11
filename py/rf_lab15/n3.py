# Равашдех Фадей ИУ7-15Б.
# Написать 3 независимые программы для работы с бинарными файлами из целых
# 32-битных чисел, каждая из которых будет реализовывать ввод чисел в файл (если
# файл существует - перезаписывать), соответствующее задание и вывод изменённого
# содержимого файла.
# 3. Сортировка методом Шелла.

import struct

# print(struct.pack('l', 2147483647))
# print(struct.pack('l', -2147483648))


# Ввод 32-битного числа с проверкой
def input_int32(prompt_line):
    while True:
        try:
            inp = input(prompt_line)
            if inp == '':
                return None
            arg = int(inp)
            if not (-2_147_483_647 <= arg <= 2_147_483_647):
                raise ValueError('Аргумент должен входить в отрезок [−2,147,483,647, +2,147,483,647].')
        except ValueError as ex:
            print('Ошибка ввода.\n', ex)
        else:
            return arg


# Блок ввода
path = 'file3.bin'
with open(path, 'wb') as f:
    counter = 0
    while not ((number := input_int32(f'Введите {counter}-е число (пустую строку для завершения): ')) is None):
        packed_num = struct.pack('l', number)
        f.write(packed_num)
        counter += 1

# Основная часть
with open(path, 'rb+') as f:
    f.seek(1, 2)
    n = f.tell() // 4
    f.seek(0)
    step = n // 2  # шаг
    # while (packed_number := f.read(4)) != b'':
    #     print(struct.unpack('l', packed_number)[0], end=' ')
    # print()
    while step > 0:
        for i in range(step, n):
            curr = i                                # индекс текущего элемента
            prev = i - step                         # индекс предыдущего элемента (шаг назад)
            # чтение пары элементов
            f.seek(4*prev, 0)                       # позиция предыдущего элемента
            a = struct.unpack('l', f.read(4))[0]    # предыдущий элемент
            f.seek(4*curr, 0)                       # позиция текущего элемента
            b = struct.unpack('l', f.read(4))[0]    # текущий элемент
            while prev >= 0 and a > b:                  # пока предыдущий больше текущего
                # элементы меняются местами
                f.seek(4*prev, 0)                       # позиция предыдущего
                f.write(struct.pack('l', b))            # записывается текущий
                f.seek(4*curr, 0)                       # позиция текущего
                f.write(struct.pack('l', a))            # записывается предыдущий

                # Вывод по действиям
                # f.seek(0)
                # while (packed_number := f.read(4)) != b'':
                #     print(struct.unpack('l', packed_number)[0], end=' ')

                curr = prev     # предыдущий становится настоящим (делает шаг назад)
                prev -= step    # предыдущий делает шаг назад
                # чтение следующей пары элементов
                if prev >= 0:
                    f.seek(4*prev, 0)  # позиция предыдущего элемента
                    a = struct.unpack('l', f.read(4))[0]  # предыдущий элемент
                    f.seek(4*curr, 0)  # позиция текущего элемента
                    b = struct.unpack('l', f.read(4))[0]  # текущий элемент

        step //= 2  # шаг уменьшается


# Блок вывода
print('Результат')
with open(path, 'rb') as f:
    counter = 0
    shift_counter = 0
    while (packed_number := f.read(4)) != b'':
        num = struct.unpack('l', packed_number)[0]
        print(num)
