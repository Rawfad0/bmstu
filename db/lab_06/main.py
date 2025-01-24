# Разработать консольное приложение с меню, состоящее из 10 функций,
# демонстрирующих основные приемы работы с базой данных.
# Все запросы, функции и процедуры должны выполняться на стороне базы данных

import psycopg2
from config import db_name, user, password, host


class DB:
    def __init__(self):
        try:
            self.connection = psycopg2.connect(
                database=db_name, user=user, password=password, host=host
            )
            self.connection.autocommit = True
            self.cursor = self.connection.cursor()
            self.table = []
            print("PostgreSQL connection opened\n")
        except Exception as ex:
            print("Error while connecting with PostgreSQL\n", ex)
            return

    def __del__(self):
        if self.connection:
            self.cursor.close()
            self.connection.close()
            print("PostgreSQL connection closed\n")

    def sql_execute(self, sql_query):
        try:
            self.cursor.execute(sql_query)
        except Exception as err:
            print("PostgreSQL Error: while get query\n", err)
            return

        return sql_query

    # 1. Скалаярный запрос
    def n_1(self):
        print("1. Получить среднее количество товаров в заказе")
        sql_query = """
            SELECT AVG(product_quantity)
            FROM orders;
        """
        if self.sql_execute(sql_query) is not None:
            row = self.cursor.fetchone()
            print(row)

    # 2. Выполнить запрос с несколькими соединениями (JOIN)
    def n_2(self):
        print("2. Получить наименования товаров, которые продаются продавцами со средним рейтингом выше 4.95")
        sql_query = """
            select p.name, s.average_rating  
            from products p
                join stores_products sp on p.product_id = sp.product_id
                join stores s on sp.store_id = s.store_id
            where s.average_rating > 4.95;
        """
        if self.sql_execute(sql_query) is not None:
            table = self.cursor.fetchall()
            print(*table, len(table), sep='\n')

    # 3. Выполнить запрос с ОТВ(CTE) и оконными функциями
    def n_3(self):
        print("3. Получить для каждого пользователя среднюю стоимость его заказов")
        # sql_query = """
        #     with uavg as (
        #         select user_id, AVG(order_price) over (partition by user_id) as avg
        #         from orders
        #     )
        #     select u.user_id, a.avg
        #     from uavg a right outer join users u on a.user_id = u.user_id
        #     order by u.user_id;
        # """

        sql_query = """
            with uavg as (
                select u.user_id, AVG(o.order_price) as avg
                from users u join orders o on u.user_id = o.user_id
                group by u.user_id
                order by u.user_id
            )
            select u.user_id, a.avg
            from uavg a right outer join users u on a.user_id = u.user_id
            order by u.user_id;
        """

        if self.sql_execute(sql_query) is not None:
            table = self.cursor.fetchall()
            print(*table, len(table), sep='\n')

    # 4. Выполнить запрос к метаданным;
    def n_4(self):
        print("4. Вывести названия таблиц")
        sql_query = """
            select *
            from information_schema.tables
            where table_catalog = 'postgres' AND table_schema = 'postgres';
        """

        if self.sql_execute(sql_query) is not None:
            table = self.cursor.fetchall()
            print(*table, len(table), sep='\n')

    # 5 Вызвать скалярную функцию (написанную в третьей лабораторной работе);
    def n_5(self):
        print("5. Вычисление цены всей партии определенного продукта")
        sql_query = """
            SELECT sp_id, calc_total_price(price, product_quantity) as total_price
            FROM stores_products
            ORDER BY sp_id
            LIMIT 20;
        """

        if self.sql_execute(sql_query) is not None:
            table = self.cursor.fetchall()
            print(*table, len(table), sep='\n')

    # 6. Вызвать многооператорную или табличную функцию (написанную в третьей лабораторной работе);
    def n_6(self):
        print("6. Вывести продавцов, которые продают не менее 4 товаров")
        sql_query = """
            SELECT *
            FROM stores_ge_n(4)
            ORDER BY store_id;
        """
        if self.sql_execute(sql_query) is not None:
            table = self.cursor.fetchall()
            print(*table, len(table), sep='\n')

    # 7. Вызвать хранимую процедуру (написанную в третьей лабораторной работе);
    def n_7(self):
        print(". Вывод товаров продающихся у продавца с id=35 ")
        sql_query = """
            select *
            from stores_products sp
            where store_id = 35;
        """
        if self.sql_execute(sql_query) is not None:
            table = self.cursor.fetchall()
            print(*table, len(table), sep='\n')

        print(". Сделать скидку 50% для товаров продающихся у продавца с id=35 ")
        sql_query = """
            call store_discount(35, 0.5);
        """
        self.sql_execute(sql_query)

        print(". Вывод товаров продающихся у продавца с id=35 ")
        sql_query = """
            select *
            from stores_products sp
            where store_id = 35;
        """
        if self.sql_execute(sql_query) is not None:
            table = self.cursor.fetchall()
            print(*table, len(table), sep='\n')

        print(". Увеличить цену в 2 раза для товаров продающихся у продавца с id=35")
        sql_query = """
            call store_up_prices(35, 2);
        """
        self.sql_execute(sql_query)

        print(". Вывод товаров продающихся у продавца с id=35 ")
        sql_query = """
            select *
            from stores_products sp
            where store_id = 35;
        """
        if self.sql_execute(sql_query) is not None:
            table = self.cursor.fetchall()
            print(*table, len(table), sep='\n')

    # 8. Вызвать системную функцию или процедуру;
    def n_8(self):
        print("8. Вывести имя пользователя, имя текущей базы данных и информацию о версии PostgreSQL")
        sql_query = """
            select user, current_database(), version();
        """
        if self.sql_execute(sql_query) is not None:
            table = self.cursor.fetchall()
            print(*table, len(table), sep='\n')

    # 9. Создать таблицу в базе данных, соответствующую тематике БД;
    def n_9(self):
        print("9. Создать таблицу пунктов выдачи заказов")
        sql_query = \
            """
            drop table if exists pick_up_points;
            create table if not exists pick_up_points
            (
                id int primary key,
                address text,
                hours text,
                storage_cap int
            );
            """
        if self.sql_execute(sql_query) is not None:
            print("Done")

    def check_exists(self):
        sql_query = """
                    select *
                    from information_schema.tables
                    where table_schema = 'postgres' and table_name = 'pick_up_points';
                """

        if self.sql_execute(sql_query) is not None:
            table = self.cursor.fetchall()
            # print(*table, len(table), sep='\n')
            return len(table) == 1

    # 10. Выполнить вставку данных в созданную таблицу с использованием инструкции INSERT или COPY
    def n_10(self):
        print("10. Вставка данных в таблицу pick_up_points.")

        if not self.check_exists():
            print("Error: таблица не создана")
            return

        inputs = input("Введите данные (id, address, hours, storage_cap): ").split()
        if len(inputs) != 4:
            print("Error: введено не 4 поля.")
            return
        inputs[0] = int(inputs[0])
        inputs[3] = int(inputs[3])
        sql_query = ("""
            INSERT INTO pick_up_points(id, address, hours, storage_cap) VALUES
            ({}, '{}', '{}', {})
            """.format(*inputs))
        if self.sql_execute(sql_query) is not None:
            print("DONE")

    # Защита. Вывести все поля таблиц
    def n_11(self):
        print("Защита. Вывод полей таблиц.")
        sql_query = """
            select table_name, column_name 
            from information_schema.columns 
            where table_schema='postgres';
        """
        if self.sql_execute(sql_query) is not None:
            table = self.cursor.fetchall()
            print(*table, len(table), sep='\n')


db = DB()

funcs = [
    db.n_1,
    db.n_2,
    db.n_3,
    db.n_4,
    db.n_5,
    db.n_6,
    db.n_7,
    db.n_8,
    db.n_9,
    db.n_10,
    db.n_11,
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
11. Вывести все столбцы таблиц
12. ВЫХОД.
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
