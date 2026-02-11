# Равашдех Фадей ИУ7-15Б
# Из файла в котором есть записи вида имя,возраст получить новый файл,
# в котором пользователи будут отфильтрованы по возрасту
# Возраст вводит пользователь

import re

# Пути файлов
input_path = 'input.txt'
output_path = 'output.txt'

# Ввод возраста с проверкой
while True:
    age = input('Введите возраст: ')
    try:
        age = int(age)
    except ValueError:
        print('Должно быть введено целое число.')
    else:
        break


def check_db(path):
    try:
        fields = ['Имя', 'Возраст']
        reg_expr = ['^[А-Яа-яЁё]*$',
                    '^[0-9]*$']
        with open(path, 'r', encoding='UTF-8') as f:
            while (line := f.readline()) != '':
                line = line.split(',')
                if len(line) != 2:
                    print(f'{line}\nЗапись должна состоять из двух полей.')
                    return False
                else:
                    for i in range(len(line)):
                        if re.match(reg_expr[i], line[i]) is None:
                            print(f'{line[i]}Поле записи {fields[i]} не соответствует шаблону {reg_expr[i]}')
                            return False
            return True
    except Exception as ex:
        print(ex)


def print_db(path):
    try:
        # print('ok')
        # Подсчёт ширины столбцов
        column_size = [3, 7]
        fields = ['Имя', 'Возраст']
        # print('ok')
        with open(path, 'r', encoding='UTF-8') as f:
            # print('ok')
            while (line := f.readline()) != '':
                # print('ok1')
                line = line.split(',')
                for i in range(len(line)):
                    if len(line[i]) > column_size[i]:
                        column_size[i] = len(line[i])

        for i in range(len(fields)):
            print(fields[i].center(column_size[i]), end=' ')
        print()

        with open(path, 'r', encoding='UTF-8') as f:
            while (line := f.readline()) != '':
                line = line.split(',')
                for i in range(len(line)):
                    print(line[i].rstrip('\n').rjust(column_size[i]), end=' ')
                print()

    except Exception as ex:
        print(ex)


# Основная часть
is_db = check_db(input_path)    # проверка на базу данных
if is_db:
    try:
        # Вывод файла исходных данных
        print(f'Исходный файл {input_path}:')
        print_db(input_path)
        # Чтение файла входных данных и запись в файл выходных данных
        with open(input_path, 'r', encoding='UTF-8') as input_file, open(output_path, 'w', encoding='UTF-8') as output_file:
            # print(f'Исходный файл {input_path}:')
            while (line := input_file.readline()) != '':
                line = line.split(',')
                # print(line[0], line[1], end='')
                if int(line[1].rstrip('\n')) > age:
                    output_file.write(','.join(line))

        # Вывод результата фильтра из файла выходных данных
        print(f'\nОтфильтрованный файл {output_path}:')
        print_db(output_path)
        # with open(output_path, 'r') as output_file:
        #     print(f'\nОтфильтрованный файл {output_path}:')
        #     while (line := output_file.readline()) != '':
        #         line = line.split(',')
        #         print(line[0], line[1], end='')
    except Exception as ex:
        print(ex)
else:
    print('Файл не является подходящей базой данных или поврежден.')
