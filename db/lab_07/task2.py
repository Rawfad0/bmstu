import json
import psycopg2
import sys
from py_linq import Enumerable
from datetime import datetime
from config import *


# # Подключение к базе данных PostgreSQL
# def fetch_data_from_db():
#     conn = psycopg2.connect(
#         dbname=db_name,
#         user=user,
#         password=password,
#         host=host,
#         port=port
#     )
#     cursor = conn.cursor()
#
#     # Выполнение запроса SELECT для извлечения данных
#     cursor.execute("select user_id, last_name, first_name, phone_number, email, birth_date, reg_date from users")
#     records = cursor.fetchall()
#
#     # Преобразование данных в список словарей
#     users = []
#     for record in records:
#         users.append({
#             "user_id": record[0],
#             "last_name": record[1],
#             "first_name": record[2],
#             "phone_number": record[3],
#             "email": record[4],
#             "birth_date": record[5].strftime('%Y-%m-%d'),
#             "reg_date": record[6].strftime('%Y-%m-%d')
#         })
#     # Закрытие соединения с базой данных
#     cursor.close()
#     conn.close()
#     return users


# Чтение данных из JSON файла
def read_json(filename='/Users/Shared/users_copy.json'):
    users = []
    with open(filename, 'r', encoding='utf-8') as file:
        for line in file:
            users.append(json.loads(line.strip()))
    return users


# Запись данных в JSON файл
def write_to_json(users, filename='/Users/Shared/users_copy.json'):
    # print("write to json")
    with open(filename, 'w', encoding='utf-8') as file:
        for user in users:
            # print(user)
            file.write(json.dumps(user, ensure_ascii=False) + '\n')


# Обновление JSON файла (обновляем поле email для определенного пользователя)
def update_json(user_id, new_email, filename='/Users/Shared/users_copy.json'):
    users = read_json(filename)
    for user in users:
        if user["user_id"] == user_id:
            user["email"] = new_email
            break
    # Запись обновленных данных обратно в файл
    write_to_json(users, filename)


# Добавление новой записи в JSON файл
def add_to_json(new_user, filename='/Users/Shared/users_copy.json'):
    users = read_json(filename)
    users.append(new_user)
    # Запись обновленных данных обратно в файл
    write_to_json(users, filename)


# Реализуем три запроса на JSON
def linq_to_json(func):
    # 1. Чтение данных из JSON
    if func == 1:
        users_data = Enumerable(read_json())
        print("Все данные из JSON файла:")
        for user in users_data.select(lambda x: x):
            print(user)

    # 2. Обновление данных в JSON (обновим email для пользователя)
    if func == 2:
        id = int(input("ID: "))
        email = input("new email: ")
        update_json(id, email)
        print(f"\nДанные после обновления email для пользователя с user_id={id}:")
        users_data = Enumerable(read_json())
        q = users_data.where(lambda x: x['user_id'] == id)
        for elem in q:
            print(elem)

    # 3. Добавление новой записи в JSON
    if func == 3:
        users_data = Enumerable(read_json())
        new_id = len(users_data) + 1
        new_user = {
            "user_id": new_id,
            "last_name": input("last_name: "),
            "first_name": input("first_name: "),
            "phone_number": input("phone_number: "),
            "email": input("email: "),
            "birth_date": "1900-01-01",
            "reg_date": datetime.now().strftime('%Y-%m-%d'),
        }
        add_to_json(new_user)
        print("\nДанные после добавления нового производителя:")
        users_data = Enumerable(read_json())
        q = users_data.where(lambda x: x['user_id'] == new_id)
        for elem in q:
            print(elem)


def print_menu():
    print("""МЕНЮ:
1. Чтение
2. Обновление
3. Добавление
4. Выход
""")


def get_command():
    try:
        command = int(input('enter command: '))
    except Exception:
        command = 0
    return command


if __name__ == "__main__":
    # users_from_db = fetch_data_from_db()
    # write_to_json(users_from_db)
    print_menu()

    while not (0 < (func := get_command()) <= 4):
        print("Попробуй еще раз!")
    if func != 4:
        linq_to_json(func)
