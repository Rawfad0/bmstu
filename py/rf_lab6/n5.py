# Равашдех Фадей ИУ7-15Б
# 5. Поменять местами элементы с характеристиками по варианту.
# 7. Последний нулевой и максимальный отрицательный.

# Блок ввода
n = int(input('Введите количество элементов списка: '))
while n <= 0:
    print('Количество элементов должно быть больше 0.')
    n = int(input('Введите количество элементов списка: '))
int_list = [0]*n
print('Вводите элементы: ')
for i in range(n):
    int_list[i] = int(input(f'{i}: '))

# Основной блок
list_length = len(int_list)
i1 = None   # Индекс последнего нулевого
i2 = None   # Индекс максимального отрицательного
for i in range(list_length):
    x = int_list[i]         # Текущее число
    if x == 0:
        i1 = i              # П
    if i2 is None and x < 0:
        i2 = i
    if 0 > x > int_list[i2]:
        i2 = i

# Блок вывода
if i1 is None or i2 is None:
    print('Как минимум один из элементов не был найден.\n'
          'Поэтому поменять их местами нельзя.\n'
          'Будет выведен исходный список.')
    for num, el in enumerate(int_list):
        print(f'{num:3}| {el:5}')
else:
    int_list[i1], int_list[i2] = int_list[i2], int_list[i1]
    for num, el in enumerate(int_list):
        print(f'{num:3}| {el:5}')
