# coding=windows-1251
import os
import re
import struct


def print_db_line_note():
    print("""Запись имеет вид: Фамилия,Имя,Личное дело,Дата рождения
            Фамилия       Равашдех  ^[А-ЯЁ][-а-яё]{0,15}$
            Имя           Фадей     ^[А-ЯЁ][а-яё]{0,15}$
            Личное дело   22У287    ^[0-9]{2}[А-Я][0-9]{3,4}$
            Дата рождения 20040210  ^[1-9][0-9]{7}$
            """)


# Соответствует ли строка файла заданной форме
def is_line_db(line, quite=True):
    try:
        columns = ['Фамилия', 'Имя', 'Личное дело', 'Дата рождения']
        reg_expr = ['^[А-ЯЁ][-а-яё]{0,15}$',
                    '^[А-ЯЁ][а-яё]{0,15}$',
                    '^[0-9]{2}[А-Я][0-9]{3,4}$',
                    '^[1-9][0-9]{7}$']
        line = line.split(',')
        # print(line)
        if len(line) != 4:
            if not quite:
                print(f'{line}\nЗапись должна содержать 4 элементов (3 запятых).')
            return False
        else:
            for i in range(len(line)):
                if re.match(reg_expr[i], line[i]) is None:
                    if not quite:
                        print(f'{line}\nПоле записи {columns[i]} не соответствуют форме.')
                    return False
        return True
    except Exception as ex:
        print(ex)
        print('В процессе выполнения is_line_db возникла ошибка.')
        return None


def is_db_check(path, quite_flag=True):
    try:
        is_db = True
        with open(path, 'rb') as f:
            while (line := f.read(44)) != b'':
                # print(line)
                unpacked_line = list(struct.unpack('16s16s8sL', line))
                # print(line)
                unpacked_line[:3] = [el.rstrip(b'\x00').decode('windows-1251') for el in unpacked_line[:3]]
                unpacked_line[3] = str(unpacked_line[3])
                line = ','.join(unpacked_line)
                # print(line)
                is_line = is_line_db(line, quite=quite_flag)
                if is_line is None:
                    is_db = None
                    break
                elif not is_line:
                    is_db = False
                    break
        # print(is_db)
        return is_db
    except PermissionError:
        print('Ошибка доступа. У пользователя нет прав на чтение этого файла.')
    except UnicodeDecodeError:
        print('Нельзя вывести содержимое. Файл имеет неподходящую кодировку.')
    except struct.error as ex:
        print(ex)
        print('Файл не является базой данных или база данных повреждена.')
    except SyntaxError:
        print('Файл не является базой данных или база данных повреждена.')
    except Exception as ex:
        print(ex)
        print('В процессе выполнения is_db_check возникла ошибка.')


# 1. Выбрать файл для работы
def choose_file():
    path = input('Введите путь к файлу (пустая строка для выхода): ')
    file_name = None
    # print(oct(os.stat(path).st_mode))
    if path == '':
        return None
    if not os.path.exists(path):
        print('Файл не найден.')
    elif not os.path.isfile(path):
        print('Не является файлом.')
    else:
        file_name = path
    return file_name


# 2 Инициализация базы данных
def init_db():
    print('Если файла не существует, то он будет создан.\n'
          'Если файл существует, то он будет перезаписан.')
    path = input('Введите путь к файлу: ')
    if not (path.endswith('.py') and os.path.exists(path)):
        try:
            with open(path, 'wb') as f:
                print_db_line_note()
                print('Вводите записи построчно (разделение по запятой, пустая строка для прекращения): ')
                while (line := input()) != '':
                    if is_line_db(line, quite=False):
                        line = line.split(',')
                        line[3] = int(line[3])
                        line[:3] = [i.encode('windows-1251') for i in line[:3]]
                        packed_line = struct.pack('16s16s8sL', *line)
                        f.write(packed_line)
                print('Не забудьте выбрать файл для работы (Действие 1).')
        except FileNotFoundError:
            print('Нельзя создать файл. Директории не существует.')
        except PermissionError:
            print('Ошибка доступа. Нельзя перезаписать файл. У пользователя нет прав на запись этого файла.')
        except Exception as ex:
            print(ex)
            print('В процессе выполнения init_db возникла ошибка.')
    else:
        print('Перезапись файлов этого типа недоступна.')


# 3. Вывести содержимое базы данных
def db_print(path):
    try:
        is_db = is_db_check(path, quite_flag=False)
        if is_db is None:
            pass
        elif is_db:   # Файл соответствует форме
            # Узнаем ширину столбца найдя самый длинный элемент столбца
            column_sizes = [3, 7, 3, 11, 13]
            with open(path, 'rb') as f:
                while (line := f.read(44)) != b'':
                    unpacked_line = list(struct.unpack('16s16s8sL', line))
                    unpacked_line[:3] = [el.rstrip(b'\x00').decode('windows-1251') for el in unpacked_line[:3]]
                    unpacked_line[3] = str(unpacked_line[3])
                    line = ','.join(unpacked_line)
                    line = line.split(',')
                    for i in range(len(line)):
                        if len(line[i]) > column_sizes[1 + i]:
                            column_sizes[1 + i] = len(line[i])

            # Вывод шапки таблицы
            header_fields = ['№', 'Фамилия', 'Имя', 'Личное дело', 'Дата рождения']
            for size in column_sizes:
                print('+', '-' * size, end=' ')
            print('+')
            for i in range(len(header_fields)):
                print('|', header_fields[i].ljust(column_sizes[i]), end=' ')
            print('|')
            for size in column_sizes:
                print('+', '-' * size, end=' ')
            print('+')

            # Вывод в виде таблицы
            with open(path, 'rb') as f:
                counter = 1
                while (line := f.read(44)) != b'':
                    unpacked_line = list(struct.unpack('16s16s8sL', line))
                    unpacked_line[:3] = [el.rstrip(b'\x00').decode('windows-1251') for el in unpacked_line[:3]]
                    unpacked_line[3] = str(unpacked_line[3])
                    line = ','.join(unpacked_line)
                    line = line.split(',')
                    print('|', str(counter).rjust(3), end=' ')
                    for i in range(len(line)):
                        print('|', line[i].replace('\n', '').ljust(column_sizes[1 + i]), end=' ')
                    print('|')
                    counter += 1

            # Дно таблицы
            for size in column_sizes:
                print('+', '-' * size, end=' ')
            print('+')
        else:
            print('Файл не является базой данных')
        # else:
        #     print('Файл не соответствует форме. Будет выведен без форматирования.')
        #     print('_' * 120)
        #     with open(path, 'r') as f:
        #         while (line := f.readline()) != '':
        #             print(line, end='')
        #         print()
    except FileNotFoundError:
        print('Нельзя вывести содержимое. Файла не найден.')
    except UnicodeDecodeError:
        print('Нельзя вывести содержимое. Файл имеет неподходящую кодировку.')
    except PermissionError:
        print('Ошибка доступа. У пользователя нет прав на чтение этого файла.')
    except Exception as ex:
        print(ex)
        print('В процессе выполнения db_print возникла ошибка.')


def insert_line(path, ins_line, n):
    i = 0
    with open(path, 'rb') as f:
        while (line := f.read(44)) != b'':
            i += 1
    m = i
    print(m)
    with open(path, 'rb') as f:
        while i != 0:
            line = f.read(44)
            i -= 1
    with open(path, 'ab') as f:
        f.write(line)

    for i in range(m - n + 1):
        # j = m - i
        with open(path, 'rb+') as f:
            f.seek(44*(m - 1 - i))
            temp_line = f.read(44)
            f.write(temp_line)
    with open(path, 'rb+') as f:
        f.seek((n - 1)*44)
        line = ins_line.split(',')
        line[3] = int(line[3])
        line[:3] = [i.encode('windows-1251') for i in line[:3]]
        packed_line = struct.pack('16s16s8sL', *line)
        f.write(packed_line)


# 4. Добавить запись в произвольное место базы данных
def db_add_line(path):
    try:
        is_db = is_db_check(path, quite_flag=False)
        if is_db is None:
            pass
        elif is_db:
            while True:
                print_db_line_note()
                ins_line = input('Введите добавляемую запись (пустую строку для выхода): ')
                if ins_line:
                    is_line_correct = is_line_db(ins_line, quite=False)
                    if is_line_correct is None:
                        pass
                    elif is_line_correct:
                        nm = 0
                        with open(path, 'rb') as f:
                            while (line := f.read(44)) != b'':
                                nm += 1
                        while True:
                            n = input('Введите номер будущей записи (пустую строку для выхода): ')
                            if n:
                                try:
                                    n = int(n)
                                except ValueError as ex:
                                    print('Ошибка ввода.\n', ex)

                                if 0 <= n <= nm + 1:
                                    insert_line(path, ins_line, n)
                                    break
                                else:
                                    print('Номер должен быть больше или равен нулю и',
                                          'не быть больше чем количество записей + 1')
                            else:
                                break
                        break
                else:
                    break
        else:
            print('Файл не соответствует форме. Добавление записи недоступно.')
    except FileNotFoundError:
        print('Нельзя вывести содержимое. Файла не найден.')
    except PermissionError:
        print('Ошибка доступа. У пользователя нет прав на запись этого файла.')
    except Exception as ex:
        print(ex)
        print('В процессе выполнения db_add_line возникла ошибка.')


# 5. Удалить произвольную запись из базы данных (пользователь указывает номер удаляемой записи)
def db_del_line(path):
    try:
        is_db = is_db_check(path, quite_flag=False)
        if is_db is None:
            pass
        elif is_db:
            nm = 0
            with open(path, 'rb') as f:
                while (line := f.read(44)) != b'':
                    nm += 1
            print(nm)
            while True:
                n = input('Введите номер удаляемой записи (пустую строку для выхода): ')
                if n:
                    try:
                        n = int(n)
                    except ValueError as ex:
                        print('Ошибка ввода.\n', ex)
                    else:
                        if 0 < n <= nm:
                            for i in range(n, nm):
                                with open(path, 'rb+') as f:
                                    f.seek(44*i)
                                    temp_line = f.read(44)
                                    # print(struct.unpack('16s16s8sL', line))
                                    f.seek(44*(i - 1))
                                    f.write(temp_line)
                            with open(path, 'rb+') as f:
                                f.truncate((nm - 1)*44)
                            break
                        else:
                            print('Номер должен быть больше нуля и не быть больше чем количество записей.')
                else:
                    break

        else:
            print('Файл не является базой данных')
    except FileNotFoundError:
        print('Нельзя вывести содержимое. Файла не найден.')
    except PermissionError:
        print('Ошибка доступа. У пользователя нет прав на запись этого файла.')
    except Exception as ex:
        print(ex)
        print('В процессе выполнения db_del_line возникла ошибка.')


# 6. Поиск по одному полю
def db_search_1_field(path):
    try:
        is_db = is_db_check(path, quite_flag=False)
        if is_db is None:
            pass
        elif is_db:
            fields = ['Фамилия', 'Имя', 'Личное дело', 'Дата рождения']
            # search_field = input('Введите искомое поле: ')
            search_field = 'Имя'
            find_value = input(f'Введите искомое в поле {search_field} значение: ')
            field_i = None
            for i in range(len(fields)):
                if fields[i] == search_field:
                    field_i = i
            if field_i is None:
                print('Такого поля не существует.')
            else:
                # Узнаем ширину столбца найдя самый длинный элемент столбца
                column_sizes = [3, 7, 3, 11, 13]
                with open(path, 'rb') as f:
                    while (line := f.read(44)) != b'':
                        unpacked_line = list(struct.unpack('16s16s8sL', line))
                        unpacked_line[:3] = [el.rstrip(b'\x00').decode('windows-1251') for el in unpacked_line[:3]]
                        unpacked_line[3] = str(unpacked_line[3])
                        line = ','.join(unpacked_line)
                        line = line.split(',')
                        for i in range(len(line)):
                            if len(line[i]) > column_sizes[1 + i]:
                                column_sizes[1 + i] = len(line[i])

                # Вывод шапки таблицы
                header_fields = ['№', 'Фамилия', 'Имя', 'Личное дело', 'Дата рождения']
                for size in column_sizes:
                    print('+', '-' * size, end=' ')
                print('+')
                for i in range(len(header_fields)):
                    print('|', header_fields[i].ljust(column_sizes[i]), end=' ')
                print('|')
                for size in column_sizes:
                    print('+', '-' * size, end=' ')
                print('+')

                # with open(path, 'r') as f:
                #     while (line := f.readline()) != '':
                #         line = line.split(',')
                #         if line[field_i] == find_value:
                #             for i in range(len(line)):
                #                 print('|', line[i].replace('\n', '').ljust(column_sizes[i]), end=' ')
                #             print('|')

                # Вывод в виде таблицы
                with open(path, 'rb') as f:
                    counter = 1
                    while (line := f.read(44)) != b'':
                        unpacked_line = list(struct.unpack('16s16s8sL', line))
                        unpacked_line[:3] = [el.rstrip(b'\x00').decode('windows-1251') for el in
                                             unpacked_line[:3]]
                        unpacked_line[3] = str(unpacked_line[3])
                        line = ','.join(unpacked_line)
                        line = line.split(',')
                        if line[field_i] == find_value:
                            print('|', str(counter).rjust(3), end=' ')
                            for i in range(len(line)):
                                print('|', line[i].replace('\n', '').ljust(column_sizes[1 + i]), end=' ')
                            print('|')
                            counter += 1

                # Дно таблицы
                for size in column_sizes:
                    print('+', '-' * size, end=' ')
                print('+')
        else:
            print('Файл не соответствует форме. Поиск недоступен.')
    except FileNotFoundError:
        print('Нельзя вывести содержимое. Файла не найден.')
    except PermissionError:
        print('Ошибка доступа. У пользователя нет прав на чтение этого файла.')
    except UnicodeDecodeError:
        print('Нельзя вывести содержимое. Файл имеет неподходящую кодировку.')
    except Exception as ex:
        print(ex)
        print('В процессе выполнения db_search_1_field возникла ошибка.')


# 7. Поиск по двум полям
def db_search_2_field(path):
    try:
        is_db = is_db_check(path, quite_flag=False)
        if is_db is None:
            pass
        elif is_db:
            fields = ['Фамилия', 'Имя', 'Личное дело', 'Дата рождения']
            search_field_1 = 'Фамилия'
            search_field_2 = 'Имя'
            find_value_1 = input(f'Введите искомое в поле {search_field_1} значение: ')
            find_value_2 = input(f'Введите искомое в поле {search_field_2} значение: ')
            field_i_1 = None
            for i in range(len(fields)):
                if fields[i] == search_field_1:
                    field_i_1 = i
            field_i_2 = None
            for i in range(len(fields)):
                if fields[i] == search_field_2:
                    field_i_2 = i
            if field_i_1 is None:
                print(f'Поля {search_field_1} не существует.')
            elif field_i_2 is None:
                print(f'Поля {search_field_2} не существует.')
            else:
                # Узнаем ширину столбца найдя самый длинный элемент столбца
                column_sizes = [3, 7, 3, 11, 13]
                with open(path, 'rb') as f:
                    while (line := f.read(44)) != b'':
                        unpacked_line = list(struct.unpack('16s16s8sL', line))
                        unpacked_line[:3] = [el.rstrip(b'\x00').decode('windows-1251') for el in unpacked_line[:3]]
                        unpacked_line[3] = str(unpacked_line[3])
                        line = ','.join(unpacked_line)
                        line = line.split(',')
                        for i in range(len(line)):
                            if len(line[i]) > column_sizes[1 + i]:
                                column_sizes[1 + i] = len(line[i])

                # Вывод шапки таблицы
                header_fields = ['№', 'Фамилия', 'Имя', 'Личное дело', 'Дата рождения']
                for size in column_sizes:
                    print('+', '-' * size, end=' ')
                print('+')
                for i in range(len(header_fields)):
                    print('|', header_fields[i].ljust(column_sizes[i]), end=' ')
                print('|')
                for size in column_sizes:
                    print('+', '-' * size, end=' ')
                print('+')

                # Вывод в виде таблицы
                with open(path, 'rb') as f:
                    counter = 1
                    while (line := f.read(44)) != b'':
                        unpacked_line = list(struct.unpack('16s16s8sL', line))
                        unpacked_line[:3] = [el.rstrip(b'\x00').decode('windows-1251') for el in
                                             unpacked_line[:3]]
                        unpacked_line[3] = str(unpacked_line[3])
                        line = ','.join(unpacked_line)
                        line = line.split(',')
                        if line[field_i_1] == find_value_1 and line[field_i_2] == find_value_2:
                            print('|', str(counter).rjust(3), end=' ')
                            for i in range(len(line)):
                                print('|', line[i].ljust(column_sizes[1 + i]), end=' ')
                            print('|')
                            counter += 1

                # Дно таблицы
                for size in column_sizes:
                    print('+', '-' * size, end=' ')
                print('+')
        else:
            print('Файл не соответствует форме. Поиск недоступен.')
    except FileNotFoundError:
        print('Нельзя вывести содержимое. Файла не найден.')
    except PermissionError:
        print('Ошибка доступа. У пользователя нет прав на чтение этого файла.')
    except UnicodeDecodeError:
        print('Нельзя вывести содержимое. Файл имеет неподходящую кодировку.')
    except Exception as ex:
        print(ex)
        print('В процессе выполнения db_search_2_field возникла ошибка.')
