# Равашдех Фадей ИУ7-15Б
# 1a. Добавить элемент в заданное место списка (по индексу)
# с использованием любых средств Python.

# Блок ввода
int_list = [int(i) for i in input('Введите элементы списка через пробел: ').split()]
x = int(input('Введите добавляемый элемент: '))
index = int(input('Введите индекс добавляемого элемента: '))

list_length = len(int_list)
if list_length == 0:
    print('Список не должен быть пуст.')
elif index < 0:
    print('Индекс не должен быть меньше нуля.')
elif index > list_length:
    print('Индекс не должен быть больше длины списка.')
else:   # Добавление элемента х в i-й индекс
    int_list.insert(index, x)

    # Блок вывода
    for num, el in enumerate(int_list):
        print(f'{num:3}| {el:5}')
