# Равашдех Фадей ИУ7-15Б
# Поиск элемента в списке строк по варианту.
# 5. Поиск элемента наибольшей длины, не содержащего цифр

# Блок ввода
n = int(input('Введите количество элементов списка: '))
while n <= 0:
    print('Количество элементов должно быть больше 0.')
    n = int(input('Введите количество элементов списка: '))
str_list = ['0']*n
print('Вводите элементы: ')
for i in range(n):
    str_list[i] = input(f'{i}: ')

# Основной блок
max_str_no_dgt = None       # Стока наибльшей длины, не содержащая цифр
max_str_len = 0             # Её длина
for line in str_list:       #
    is_any_digits = False   # Есть ли в строке цифры
    for ch in line:         # Обход символов в строке
        if ch in '0123456789':      # Проверка является ли символ цифрой
            is_any_digits = True
            break

    if not is_any_digits and len(line) > max_str_len:   # Если в строке нет цифр и её длина
        max_str_no_dgt = line                           # больше длины текущей наибольшей строки
        max_str_len = len(line)

# Блок вывода
if max_str_no_dgt is None:
    print('Такого элемента не нашлось')
else:
    print(max_str_no_dgt)
