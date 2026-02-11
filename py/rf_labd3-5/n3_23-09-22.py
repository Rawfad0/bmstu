# Равашдех Фадей ИУ7-15Б

# Программа по введенным координатам точки вычисляет принадлежит ли точка заданному множеству точек.

# Блок ввода
x = float(input('Введите координату X точки: '))
y = float(input('Введите координату Y точки: '))

# Вычисления и вывод
answer = 'N'
absolute_x = abs(x)
y_UU = (-1)*(absolute_x - 9)**2 / 8 + 8
y_UD = (absolute_x - 1)**2 / 49
y_US = 7*(absolute_x - 8)**2 + 1
y_DU = (-4)*(absolute_x - 1)**2 / 49
y_DD = (absolute_x - 5)**2 / 3 - 7
y_DS = (-2)*(absolute_x - 1)**2 - 2

if -4*x**2 + 4 >= abs(y + 2):                           # Принадлежит ли точка телу
    answer = 'Body'
elif -2 <= x <= 2 and (3*absolute_x / 2 + 2) == y:      # Принадлежит ли точка антеннам
    if x > 0:                                           # Правой
        answer = 'RightAntenna'
    else:                                               # Левой
        answer = 'LeftAntenna'
elif (1 <= absolute_x <= 8 and y_UD <= y <= y_UU) or \
        (8 <= absolute_x <= 9 and y_US <= y <= y_UU):   # Принадлежит ли точка верхним крыльям
    if x > 0:                                           # Правому
        answer = 'UpperRight wing'
    else:                                               # Левому
        answer = 'UpperLeft wing'
elif (1 <= absolute_x <= 2 and y_DS <= y <= y_DU) or \
        (2 <= absolute_x <= 8 and y_DD <= y <= y_DU):   # Принадлежит ли точка нижним крыльям
    if x > 0:                                           # Правому
        answer = 'DownRight wing'
    else:                                               # Левому
        answer = 'DownLeft wing'
print(answer)
