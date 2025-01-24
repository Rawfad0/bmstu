import sqlalchemy
# from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Column, Integer, Text, Date, JSON, Float
from sqlalchemy import PrimaryKeyConstraint
from sqlalchemy import create_engine, text, MetaData, select, insert, update, delete, func
from sqlalchemy.orm import registry, Session, sessionmaker, class_mapper
from sqlalchemy.orm import declarative_base


from json import dumps, load

from config import host, user, password, db_name, port

print("Версия SQL Alchemy:", sqlalchemy.__version__)
engine = create_engine(f"postgresql+psycopg2://{user}:{password}@{host}:{port}/{db_name}")
try:
    engine.connect()
    print("БД успешно подключена!")
except:
    print("Ошибка соединения к БД!")
    exit()

Session = sessionmaker(bind=engine)
session = Session()
# meta = MetaData()
# meta.reflect(bind=engine, schema='postgres')


"""
class User(object):
    def __init__(self, user_id, last_name, first_name, phone_number, email, birth_date, reg_date):
        self.user_id = user_id
        self.last_name = last_name
        self.first_name = first_name
        self.phone_number = phone_number
        self.email = email
        self.birth_date = birth_date
        self.reg_date = reg_date


class Product(object):
    def __init__(self, product_id, category, name, description, average_rating, review_number):
        self.product_id = product_id
        self.category = category
        self.name = name
        self.description = description
        self.average_rating = average_rating
        self.review_number = review_number


class Store(object):
    def __init__(self, store_id, name, orgnip, ip, average_rating, review_number):
        self.store_id = store_id
        self.name = name
        self.orgnip = orgnip
        self.ip = ip
        self.average_rating = average_rating
        self.review_number = review_number


class StoreProduct(object):
    def __init__(self, sp_id, store_id, product_id, price, delivery_days, product_quantity):
        self.sp_id = sp_id
        self.store_id = store_id
        self.product_id = product_id
        self.price = price
        self.delivery_days = delivery_days
        self.product_quantity = product_quantity


class Order:
    def __init__(self, order_id, user_id, product_id, store_id, delivery_days, product_quantity, order_price):
        self.order_id = order_id
        self.user_id = user_id
        self.product_id = product_id
        self.store_id = store_id
        self.delivery_days = delivery_days
        self.product_quantity = product_quantity
        self.order_price = order_price

# class User:
#     pass
# registry.map_imperatively(User, meta.tables['postgres.users'])
# registry.map_imperatively(Product, meta.tables['products'])
# registry.map_imperatively(Store, meta.tables['stores'])
# registry.map_imperatively(StoreProduct, meta.tables['stores_products'])
# registry.map_imperatively(Order, meta.tables['orders'])
"""

Base = declarative_base()


class Users(Base):
    __tablename__ = 'users'
    __table_args__ = {"schema": "postgres"}
    user_id = Column(Integer, primary_key=True)
    last_name = Column(Text)
    first_name = Column(Text)
    phone_number = Column(Text)
    email = Column(Text)
    birth_date = Column(Date)
    reg_date = Column(Date)


class Products(Base):
    __tablename__ = 'products'
    __table_args__ = {"schema": "postgres"}
    product_id = Column(Integer, primary_key=True)
    category = Column(Text)
    name = Column(Text)
    description = Column(Text)
    email = Column(Text)
    average_rating = Column(Float)
    review_number = Column(Integer)


class Stores(Base):
    __tablename__ = 'stores'
    __table_args__ = {"schema": "postgres"}
    store_id = Column(Integer, primary_key=True)
    name = Column(Text)
    orgnip = Column(Text)
    ip = Column(Text)
    email = Column(Text)
    average_rating = Column(Float)
    review_number = Column(Integer)


class StoresProducts(Base):
    __tablename__ = 'stores_products'
    __table_args__ = {"schema": "postgres"}
    sp_id = Column(Integer, primary_key=True)
    store_id = Column(Integer)
    product_id = Column(Integer)
    price = Column(Integer)
    delivery_days = Column(Integer)
    product_quantity = Column(Integer)


class Orders(Base):
    __tablename__ = 'orders'
    __table_args__ = {"schema": "postgres"}
    order_id = Column(Integer, primary_key=True)
    user_id = Column(Integer)
    product_id = Column(Integer)
    store_id = Column(Integer)
    delivery_days = Column(Integer)
    product_quantity = Column(Integer)
    order_price = Column(Integer)


# LINQ to Object. Создать не менее пять запросов с использованием всех ключевых слов выражения запроса.
# Object - коллекция объектов, структура которых полностью соответствует одной из таблиц БД,
# реализованной в первой лабораторной работе
# 1.
def n_1_1():
    rows = session.query(Users).where(Users.reg_date.between('2020-01-01', '2020-03-31')).all()
    for row in rows:
        print(row.user_id, row.last_name, row.first_name, row.reg_date)


def n_1_2():
    # rows = session.query(
    #     Users.user_id, Users.last_name, Users.first_name, func.count(Users.user_id)
    # ).join(Orders).group_by(Users.user_id).all()
    rows = session.query(Users).join(Orders).join(Orders).all()
    for row in rows:
        print(row.user_id, row.last_name, row.first_name)

    # select
    # u.user_id, last_name as "Фамилия", first_name as "Имя", COUNT(u.user_id) as "Количество заказов"
    # from users u
    # join
    # orders
    # o
    # on
    # u.user_id = o.user_id
    # group
    # by
    # u.user_id
    # order
    # by
    # "Количество заказов"
    # desc;


def n_1_3():
    pass


def n_1_4():
    pass


def n_1_5():
    pass


funcs = [
    n_1_1,
    n_1_2,
]


def print_menu():
    print("""МЕНЮ:
1.  Выполнить скалярный запрос;
2.  Выполнить запрос с несколькими соединениями (JOIN);
3.  Выполнить запрос с ОТВ(CTE) и оконными функциями;
4.  Выполнить запрос к метаданным;
5.  Вызвать скалярную функцию (написанную в третьей лабораторной работе);
6.  Вызвать многооператорную или табличную функцию (написанную в третьей лабораторной работе);
7.  Вызвать хранимую процедуру (написанную в третьей лабораторной работе);
8.  Вызвать системную функцию или процедуру;
9.  Создать таблицу в базе данных, соответствующую тематике БД;
10. Выполнить вставку данных в созданную таблицу с использованием инструкции INSERT или COPY;
11. ВЫХОД.
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