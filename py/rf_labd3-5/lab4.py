# Равашдех Фадей ИУ7-15Б

# Программа принимает на вход начальное значение аргумента, конечное значение и шаг разбиения данного отрезка.
# Выводит таблицу значений аргумента и заданных функций, строит график одной из этих функций.

import math as m

# # Блок ввода значений
# a_0 = float(input('Введите начальное значение аргумента: '))    # начальное значение аргумента
# a_n = float(input('Введите конечное значение аргумента: '))     # конечное значение аргумента
# h = float(input('Введите шаг разбиения отрезка: '))             # шаг разбиения отрезка
a_0 = 0
a_n = 2
h = 0.5
# Блок рассчёта аргументов и значений функций
arguments = []
p_values = []
r_values = []
argument = a_0
a_length = round(a_n - a_0, 8)
n_val = int(a_length / h) + 1            # количество значений
for i in range(n_val):
    argument = round(argument, 8)           # округление до 8 знака после запятой
    arguments.append(argument)

    p_value = round(0.471*m.exp(-argument)*m.cos(m.pi*pow(argument, 2)), 5)
    p_values.append(p_value)

    r_value = round(0.21 - 2.52*argument + pow(argument, 3), 5)
    r_values.append(r_value)

    argument += h

# Значения ширины столбцов таблицы
x_col_size = 6      # ширина первого столбца
y1_col_size = 9     # ширина второго столбца
y2_col_size = 9     # ширина третьего столбца
# Вывод таблицы
print('-'*(x_col_size + y1_col_size + y2_col_size + 10) + '\n' +        # вывод "шапки" таблицы
      f'| {"x".center(x_col_size)} | {"y1".center(y1_col_size)} | {"y2".center(y2_col_size)} |\n' +
      '|' + '-'*(x_col_size + y1_col_size + y2_col_size + 8) + '|')
for i in range(n_val):
    print(f'| {f"{arguments[i]:.5g}".ljust(x_col_size)} '       # форматированный вывод первого столбца
          f'| {f"{p_values[i]: .7g}".ljust(y1_col_size)} '      # форматированный вывод второго столбца
          f'| {f"{r_values[i]: .7g}".ljust(y2_col_size)} |')    # форматированный вывод третьего столбца
print('-'*(x_col_size + y1_col_size + y2_col_size + 10))

# Вывод графика
chosen_function = 2     # выбранная функция для построения графика
# n_notch = int(input('Введите количество засечек (от 4 до 8): '))
n_notch = 4
width = 80              # ширина графика

values = [p_values, r_values][chosen_function - 1]
max_value = p_values[0]
min_value = r_values[0]
for value in values:
    if value > max_value:
        max_value = value
    if value < min_value:
        min_value = value
notch_step = (max_value - min_value) / (n_notch - 1)
scale_bar = ' '*x_col_size
for i in range(n_notch):
    notch = min_value + i*notch_step
    scale_bar += f'{f"{notch:.7g}".ljust(80//(n_notch - 1))}'
print(scale_bar)

