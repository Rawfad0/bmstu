import json
import psycopg2
import sys
from datetime import datetime
from config import *
from peewee import *

# Подключение к базе
con = PostgresqlDatabase(
    database=db_name,
    user=user,
    password=password,
    host=host,
    port=port
)


# Базовая модель
class BaseModel(Model):
    class Meta:
        database = con


class Users(BaseModel):
    user_id = IntegerField(primary_key=True)
    last_name = CharField(max_length=255)
    first_name = CharField(max_length=255)
    phone_number = CharField(max_length=255)
    email = CharField(max_length=255)
    birth_date = DateField()
    reg_date = DateField()


class Stores(BaseModel):
    store_id = IntegerField(primary_key=True)
    name = CharField(max_length=255)
    ogrnip = CharField(max_length=255)
    ip = CharField(max_length=255)
    average_rating = FloatField()
    review_number = FloatField()


class Products(BaseModel):
    product_id = IntegerField(primary_key=True)
    category = CharField(max_length=255)
    name = CharField(max_length=255)
    description = CharField(max_length=255)
    average_rating = FloatField()
    review_number = FloatField()


class Orders(BaseModel):
    order_id = IntegerField(primary_key=True)
    user = ForeignKeyField(Users, column_name='user_id')
    product = ForeignKeyField(Products, column_name='product_id')
    store = ForeignKeyField(Stores, column_name='store_id')
    delivery_days = IntegerField()
    product_quantity = IntegerField()
    order_price = IntegerField()


# 1. Однотабличный запрос на выборку.
def select_products():
    products = (Products
                .select(Products.product_id,
                        Products.name,
                        Products.review_number).limit(10)
                .order_by(Products.product_id.desc())
                .where(Products.review_number > 200))
    for product in products:
        print(product.product_id, product.name, product.review_number)
    return products


# 2. Многотабличный запрос на выборку.
def select_orders():
    orders = (Orders
                 .select(Orders, Users, Products, Stores)
                 .join(Users, on=(Users.user_id == Orders.user))
                 .join(Products, on=(Products.product_id == Orders.store))
                 .join(Stores, on=(Stores.store_id == Orders.product))
                 .limit(10))

    for order in orders:
        print(order.order_id, '|', order.user.last_name, order.user.first_name, '|', order.product.name, '|', order.store.name)
    return orders


# 3.1. Добавление
def add_user(user_id, last_name, first_name, phone_number, email, birth_date=None):
    new_user = Users.create(
        user_id=user_id,
        last_name=last_name,
        first_name=first_name,
        phone_number=phone_number,
        email=email,
        birth_date=birth_date,
        reg_date=datetime.now().date())
    print(f"Added USER: ID: {new_user.user_id}, LastName: {new_user.last_name}")
    return new_user.user_id


# 3.2. Обновление
def update_user(user_id, new_email):
    user = Users.get(Users.user_id == user_id)
    user.email = new_email
    user.save()
    print(f"Updated USER: ID: {user.user_id}, New Email: {user.email}")
    return user.user_id


# 3.3. Удаление
def delete_user(user_id):
    user = Users.get(Users.user_id == user_id)
    user.delete_instance()
    user.save()
    print(f"Deleted USER: ID: {user_id}")
    return user_id


# 4. Доступ к данным через хранимую процедуру
def table_data():
    cursor = con.cursor()
    try:
        orders = Orders.select().where(Orders.order_id == 35)
        for order in orders:
            print(order.order_id, order.product_quantity)
        cursor.execute("call order_add_product(35, 3)")
        # print("Процедура выполнена")
        orders = Orders.select().where(Orders.order_id == 35)
        for order in orders:
            print(order.order_id, order.product_quantity)
    except psycopg2.ProgrammingError as e:
        print("Ошибка:", e)
    finally:
        cursor.close()


def print_menu():
    print("""МЕНЮ:
1. Однотабличный запрос
2. Многотабличный
3. Добавление
4. Изменение
5. Удаление
6. Хранимая процедура
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

    while not (0 < (func := get_command()) <= 7):
        print("Попробуй еще раз!")

    if func == 1:
        select_products()
    elif func == 2:
        select_orders()
    elif func == 3:
        id = int(input("user_id: "))
        last_name = input("last name: ")
        first_name = input("first name: ")
        phone = input("phone: ")
        email = input("email: ")
        try:
            add_user(id, last_name, first_name, phone, email,)
        except Exception as e:
            print(e)
    elif func == 4:
        id = int(input("user_id: "))
        email = input("new email: ")
        update_user(id, email)
    elif func == 5:
        try:
            id = int(input("user_id: "))
            delete_user(id)
        except:
            print("Users уже удален")
    elif func == 6:
        table_data()
