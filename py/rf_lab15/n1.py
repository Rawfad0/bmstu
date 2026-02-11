# Равашдех Фадей ИУ7-15Б.
# Написать 3 независимые программы для работы с бинарными файлами из целых
# 32-битных чисел, каждая из которых будет реализовывать ввод чисел в файл (если
# файл существует - перезаписывать), соответствующее задание и вывод изменённого
# содержимого файла.
# 1. Удалить все положительные числа за один проход по файлу.

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
path = 'file1.bin'
with open(path, 'wb') as f:
    counter = 0
    while not ((number := input_int32(f'Введите {counter}-е число (пустую строку для завершения): ')) is None):
        packed_num = struct.pack('l', number)
        f.write(packed_num)
        counter += 1

# Основная часть
with open(path, 'rb+') as f:
    f.seek(1, 2)
    length = f.tell() // 4
    f.seek(0)

    shift_counter = 0
    for counter in range(length):
        packed_num = f.read(4)
        num = struct.unpack('l', packed_num)[0]
        f.seek(4*(counter - shift_counter))
        f.write(struct.pack('l', num))
        f.seek(4*(counter + 1))
        if num > 0:
            shift_counter += 1
    f.truncate(4*(length - shift_counter))

# Блок вывода
print('Результат')
with open(path, 'rb') as f:
    counter = 0
    shift_counter = 0
    while (packed_number := f.read(4)) != b'':
        num = struct.unpack('l', packed_number)[0]
        print(num)
