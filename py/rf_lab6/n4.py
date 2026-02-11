# Равашдех Фадей ИУ7-15Б
# 4. Найти наиболее длинную непрерывную последовательность по варианту.
# 4. Убывающая последовательность простых чисел.

# Блок ввода
n = int(input('Введите количество элементов списка: '))
while n <= 0:
    print('Количество элементов должно быть больше 0.')
    n = int(input('Введите количество элементов списка: '))
int_list = [0]*n
print('Вводите элементы: ')
for i in range(n):
    int_list[i] = int(input(f'{i}:'))

# Основной блок
list_length = len(int_list)
counter = 0                 # Счётчик длины текущей последовательности
max_length = 0              # Длина наиболее длинной последовательности
seq = []                    # Наиболее длинная последовательность
for i in range(list_length):
    x = int_list[i]         # Текущее число

    is_prime = True         # Простота текущего числа
    if x < 2:               # Минимальное простое число - 2
        is_prime = False
    else:
        for j in range(2, int(pow(x, 0.5) + 1)):    # Проверка на простоту
            if x % j == 0:
                is_prime = False
                break

    is_lower = False        # Текущее число меньше предыдущего
    if i == 0 or int_list[i] < int_list[i - 1]:     # Проверка на убывание
        is_lower = True

    if (not is_lower) or (not is_prime) or i == list_length - 1:    # Прерывание последовательности
        if is_prime and is_lower:   # Увеличение счётчика в случае последнего элемента списка
            counter += 1
        if counter > max_length:    # Счётчик превысил длину предыдущей наибольшей последовательности
            max_length = counter                            # Наибольшая длина
            # Наибольшая последовательность:
            seq = int_list[(i - counter + (is_prime and is_lower)):(i + (is_prime and is_lower))]
        if is_prime:    # Начало следующей последовательности
            counter = 1
        else:
            counter = 0
    else:   # Продолжение последовательности
        counter += 1
    # print(i, int_list[i], counter, is_prime, is_lower)

# Блок вывода
if len(seq):
    print(f'Наиболее длинная непрерывная последовательность: ', *seq)
else:
    print('Последовательность пуста.')
# for i in seq:
#     print(seq[i])
