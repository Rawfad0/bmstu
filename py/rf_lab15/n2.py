# Равашдех Фадей ИУ7-15Б.
# Написать 3 независимые программы для работы с бинарными файлами из целых
# 32-битных чисел, каждая из которых будет реализовывать ввод чисел в файл (если
# файл существует - перезаписывать), соответствующее задание и вывод изменённого
# содержимого файла.
# 2. После каждого чётного числа добавить его удвоенное значение (допускается два прохода по файлу).

import struct

# print(struct.pack('l', 2147483647))
# print(struct.pack('l', -2147483648))
# print(struct.pack('l', 1073741823*2))
# print(struct.pack('l', -1073741824*2))


# Ввод 32-битного числа с проверкой
def input_int32(prompt_line):
    while True:
        try:
            inp = input(prompt_line)
            if inp == '':
                return None
            arg = int(inp)
            if not (-2_147_483_648 <= arg <= 2_147_483_647):
                raise ValueError('Аргумент должен входить в отрезок [−2_147_483_648, +2_147_483_647].')
            if (arg % 2 == 0) and not (-1_073_741_824 <= arg <= +1_073_741_823):
                raise ValueError('Так как число чётное, то оно будет умножено на два в процессе выполнения программы.\n'
                                 'Поэтому аргумент должен входить в отрезок [−1_073_741_824, +1_073_741_823].')
        except ValueError as ex:
            print('Ошибка ввода.\n', ex)
        else:
            return arg


# Блок ввода
path = 'file2.bin'
with open(path, 'wb') as f:
    counter = 0
    while not ((number := input_int32(f'Введите {counter}-е число (пустую строку для завершения): ')) is None):
        packed_num = struct.pack('l', number)
        f.write(packed_num)
        counter += 1

# Основная часть
with open(path, 'rb+') as f:
    f.seek(0, 2)
    length = f.tell() // 4
    f.seek(0)
    # print(length)

    # Подсчёт четных чисел
    even_counter = 0
    for counter in range(length):
        packed_num = f.read(4)
        num = struct.unpack('l', packed_num)[0]
        if num % 2 == 0:
            even_counter += 1
    # Расширение файла на количество четных чисел
    for i in range(even_counter):
        f.write(struct.pack('l', 0))
    # Добавление удвоенных четных
    shift_counter = 0
    for counter in range(length):
        f.seek(4*(length - counter - 1))
        packed_num = f.read(4)
        num = struct.unpack('l', packed_num)[0]
        if num % 2 == 0:
            f.seek(-4 * (counter + shift_counter + 2), 2)
            f.write(struct.pack('2l', num, 2*num))
            shift_counter += 1
        else:
            f.seek(-4*(counter + shift_counter + 1), 2)
            f.write(struct.pack('l', num))

# Блок вывода
print('Результат')
with open(path, 'rb') as f:
    counter = 0
    shift_counter = 0
    while (packed_number := f.read(4)) != b'':
        num = struct.unpack('l', packed_number)[0]
        print(num)
