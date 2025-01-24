import json
import sys
from py_linq import Enumerable
from datetime import datetime

users = []

# Открываем файл с JSON-данными
with open('/Users/Shared/users.json', 'r', encoding='utf-8') as file:

    # Читаем файл построчно
    for line in file:
        # Преобразуем каждую строку в JSON объект
        try:
            # print(line)
            user = json.loads(line.strip())
            # print(user["user_id"])
            users.append(user)
        except json.JSONDecodeError as e:
            print(f"Ошибка декодирования JSON на строке: {line.strip()} - {e}")

# print([item["user_id"] for item in users])

# Преобразование данных в список объектов
users_data = Enumerable([{
    "user_id": item["user_id"],
    "last_name": item["last_name"],
    "first_name": item["first_name"],
    "phone_number": item["phone_number"],
    "email": item["email"],
    "birth_date": datetime.strptime(item["birth_date"], '%Y-%m-%d').date(),
    "reg_date": datetime.strptime(item["reg_date"], '%Y-%m-%d').date(),
} for item in users])


def n_1():
    # Запрос, который выбирает все поля для каждого пользователя
    query = users_data.select(lambda x: x)

    for user in query:
        print(user)
    print(len(query))


def n_2():
    # Выбор пользователей, которые зарегистрировались позже 2024-06-01
    query = users_data.where(lambda x: x['reg_date'] > datetime(2024, 6, 1).date())

    for user in query:
        print(user)
    print(len(query))


def n_3():
    # Сортировка пользователей по дате рождения
    query = users_data.order_by(lambda x: x['birth_date'])
    # .select(lambda x: (x['user_id'], x['birth_date']))

    for user in query:
        print(user)
    print(len(query))


def n_4():
    # Проверить, есть ли хотя бы один пользователь с именем Александр
    query = users_data.any(lambda x: "Саша" in x['first_name'])
    print(f"Есть ли пользователь с именем Саша: {query}")
    query = users_data.any(lambda x: "Александр" in x['first_name'])
    print(f"Есть ли пользователь с именем Александр: {query}")


def n_5():
    # Подсчет количества пользователей, зарегистрировавшихся позже 2024-06-01
    query10 = users_data.count(lambda x: x['reg_date'] > datetime(2024, 6, 1).date())
    print(f"Количество пользователей, зарегистрировавшихся позже 2024-06-01 года: {query10}")


def n_6():
    # Все пары людей, родившихся в один день
    query = users_data.join(users_data,
                            lambda x: x['birth_date'],
                            lambda x: x['birth_date']).where(lambda x: x[0]['user_id'] > x[1]['user_id'])
    for user in query:
        print(user)
    print(len(query))


funcs = [
    n_1,
    n_2,
    n_3,
    n_4,
    n_5,
    n_6
]


def print_menu():
    print("""МЕНЮ:
1. Запрос, который выбирает все поля для каждого пользователя
2. Выбор пользователей, которые зарегистрировались позже 2024-06-01
3. Сортировка пользователей по дате рождения
4. Проверить, есть ли хотя бы один пользователь с именем Александр
5. Подсчет количества пользователей, зарегистрировавшихся позже 2024-06-01
6. Все уникальные пары людей, родившихся в один день
7. Выход
""")


def get_command():
    try:
        command = int(input('enter command: '))
    except Exception:
        command = 0
    return command


if __name__ == "__main__":
    print_menu()
    while not (0 < (func := get_command()) <= len(funcs) + 1):
        print("Попробуй еще раз!")
    if func != len(funcs) + 1:
        funcs[func - 1]()