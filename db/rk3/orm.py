# import time
# from sqlalchemy.orm import declarative_base
# from sqlalchemy.orm import relationship
# from sqlalchemy import Column, Integer, ForeignKey, Text, Time, CheckConstraint, Date
# from sqlalchemy import func
#
# from sqlalchemy import create_engine
# from sqlalchemy.orm import sessionmaker
# from operator import and_
from time import *
from peewee import *
import datetime

from datetime import *


con = PostgresqlDatabase(
    database="postgres",
    user="postgres",
    password="12345",
    host="127.0.0.1",  # Адрес сервера базы данных.
    port=5432	   # Номер порта.
)


class Base(Model):
    class Meta:
        database = con


class Satellite(Base):
    s_id = IntegerField(column_name='s_id')
    name = CharField(column_name='name')
    prod_date = DateField(column_name='prod_date')
    country = CharField(column_name='country')

    class Meta:
        table_name = 'satellite'



class Flight(Base):
    s_id = IntegerField(column_name='s_id')
    name = CharField(column_name='name')
    launch_date = DateField(column_name='launch_date')
    launch_time = DateField(column_name='launch_time')
    day = CharField(column_name='day')
    type = IntegerField(column_name='type')

    class Meta:
        table_name = 'flight'


# 1. Найти все страны с самыми новыми спутниками
def n_1_sql():
    global con

    print("Задание 1:")
    cur = con.cursor()
    cur.execute("""
        select country 
        from satellite 
        where prod_date = (
            select max(prod_date)
            from satellite
        );
    """)
    table = cur.fetchall()
    print(*table, len(table), sep='\n')


# 2. Найти спутник, который отправлен в этом году позже всех
def n_2_sql():
    global con

    print("Задание 2:")
    cur = con.cursor()
    cur.execute("""
            select f.s_id, name
            from flight f join satellite s on f.s_id = s.s_id
            where launch_date = (
                select max(launch_date)
                from flight
                where type=1 and date_part('year', launch_date) = date_part('year', (select current_timestamp))
            )
            order by launch_time
            limit 1;
        """)
    table = cur.fetchall()
    print(*table, len(table), sep='\n')


# 3. Найти все аппараты, вернувшиеся на землю не позднее 10 дней с 2024-01-01
def n_3_sql():
    global con

    print("Задание 3:")
    cur = con.cursor()
    cur.execute("""
        select name, launch_date
        from satellite s join flight f on s.s_id = f.s_id
        where type = 0 and launch_date <= '2024-01-11';
    """)
    table = cur.fetchall()
    print(*table, len(table), sep='\n')


# 1. Найти все страны с самыми новыми спутниками
def n_1_orm():
    pass
    # query = (
    #     Satellite
    #     .select(Satellite.country)
    #     .where(Satellite.prod_date = (
    #         Satellite
    #         .select(fn.max(Sattelite.prod_date))
    #         .from(Satellite)
    #     ))
    # )
    #
    # table = query.dicts().execute()
    # print(*table, len(table), sep='\n')


# 2. Найти спутник, который отправлен в этом году позже всех
def n_2_orm():
    print("Не успел")


# 3. Найти все аппараты, вернувшиеся на землю не позднее 10 дней с 2024-01-01
def n_3_orm():
    date_limit = datetime(2024, 1, 1) + timedelta(days=10)
    query = (
        Flight
        .select(Satellite.name, Flight.launch_date)
        .join(Satellite, on=(Satellite.s_id == Flight.s_id))
        .where(Flight.type == 0)
        .where(Flight.launch_date <= date_limit.date())
    )
    table = query.dicts().execute()
    print(*table, len(table), sep='\n')


funcs = [
    n_1_sql,
    n_2_sql,
    n_3_sql,
    n_1_orm,
    n_2_orm,
    n_3_orm
]


def print_menu():
    print("""МЕНЮ:
1.  1 sql;
2.  2 sql;
3.  3 sql;
4.  1 orm;
5.  2 orm;
6.  3 orm;
7. ВЫХОД.
""")


def get_command():
    try:
        command = int(input('enter command: '))
    except Exception:
        command = 0
    return command


if __name__ == "__main__":
    print_menu()
    while not (0 < (func := get_command()) < 8):
        print("Пункта меню нет.")
    if func != 11:
        funcs[func - 1]()
