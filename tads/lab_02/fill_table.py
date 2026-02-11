# Скрипт для генерации таблиц с заданным количеством случайных записей

# Количество записей в таблице
counter = 1000

# Запуск:
# python3 fill_table.py




from random import *

fields = (
    ("Averiyanov", "Zevakhin", "Novikov", "Podkoritov", "Romanov", "Smirnov", "Fedchenko", "Khalikov"),
    ("Dmitriy", "Mikhail", "Vladimir", "Sergey", "Vladislav", "Petr", "Danil"),
    ("IU7-35B", "MT5-31", "FN12-32", "PS4-34", "E1-31"),
    ("m", "f"),
    ("17", "18", "19", "20", "21", "22", "23"),
    ("2.33", "2.5", "3.0", "3.75", "4.0", "4.25", "4.5", "4.66", "4.75", "5.0"),
    ("19.02.2020", "31.07.2020", "30.03.2020", "31.01.2020", "29.02.2020", "29.02.2019", "28.02.2100"),
)

adress = ("house", "dormitory", "rental_place")
street = ("Aviatorov", "Bolotnaya", "Vitebskya", "Gruzinskiy_Val", "Izmaylovskaya", "Konovalova", 
          "Lesnaya", "Melnikova", "Noviy_Arbat", "Plehanova", "Staropimenovskiy", "Trubnaya", 
          "Utkina", "Fadeeva", "Chertanovskaya")

file = open(f"table/table{counter}.txt", "w")

for i in range(counter):
    for field in fields:
        file.write(f"{field[randint(0, len(field) - 1)]} ")
    housing = adress[randint(0, len(adress) - 1)]
    file.write(f"{housing} ")
    match housing:
        case "house":
            file.write(f"{street[randint(0, len(street) - 1)]} {randint(1, 100)} {randint(1, 9999)} -")
        case "dormitory":
            file.write(f"- {randint(1, 999)} {randint(1, 9999)} -")
        case "rental_place":
            file.write(f"{street[randint(0, len(street) - 1)]} {randint(1, 100)} {randint(1, 9999)} {randint(1, 200000)}")
    file.write("\n")

file.close()
