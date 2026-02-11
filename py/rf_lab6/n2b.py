# Равашдех Фадей ИУ7-15Б
# 2b. Удалить элемент с заданным индексом алгоритмически.

# Блок ввода
int_list = [int(i) for i in input('Введите элементы списка через пробел: ').split()]
index = int(input('Введите индекс удаляемого элемента: '))

list_length = len(int_list)
if list_length == 0:
    print('Список не должен быть пуст.')
elif index < 0:
    print('Индекс не должен быть меньше нуля.')
elif index >= list_length:
    print('Индекс должен быть меньше длины списка.')
else:  # Удаление элемента i-го индекса
    for i in range(index, list_length - 1):     # Поочередный сдвиг элементов на одну позицию влево
        int_list[i] = int_list[i + 1]           # от искомого индекса до конца
    int_list.pop()                              # Удаление последнего элемента

    # Блок вывода
    for num, el in enumerate(int_list):
        print(f'{num:3}| {el:5}')
