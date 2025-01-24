from time import time, sleep
import threading

import matplotlib.pyplot as plt
import psycopg2
from config import db_name, user, password, host
import redis
import json
from random import randint

from faker import Faker
faker = Faker('en')

N_REPEATS = 5


class DB:
    def __init__(self):
        try:
            self.connection = psycopg2.connect(
                database=db_name, user=user, password=password, host=host
            )
            # self.connection.autocommit = True
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

    # 2. Написать запрос, получающий статистическую информацию на основе данных БД.
    # Например, получение топ 10 самых покупаемых товаров или
    # получение количества проданных деталей в каждом регионе.
    def get_top10(self):
        redis_client = redis.Redis(host="localhost", port=6379, db=0)
        cache_value = redis_client.get('top_10')
        if cache_value is not None:
            print("from_cache")
            redis_client.close()
            return json.loads(cache_value)
        # top 10 products
        self.cursor.execute("""
            select p.product_id, name, count(p.product_id) as cnt 
            from orders o join products p on o.product_id = p.product_id
            group by p.product_id 
            order by cnt desc 
            limit 10""")
        res = self.cursor.fetchall()

        # print(res)
        redis_client.set("top10", json.dumps(res, default=str))
        redis_client.close()

        return res

    # 2. Приложение выполняет запрос каждые 5 секунд на стороне БД.
    def task_02(self):
        threading.Timer(5.0, self.task_01).start()

        self.cursor.execute("""
            select p.product_id, name, count(p.product_id) as cnt 
            from orders o join products p on o.product_id = p.product_id
            group by p.product_id 
            order by cnt desc 
            limit 10""")

        result = self.cursor.fetchall()

        return result

    # 3. Приложение выполняет запрос каждые 5 секунд через Redis в качестве кэша.
    def task_03(self):
        threading.Timer(5.0, self.task_01).start()

        redis_client = redis.Redis(host="localhost", port=6379, db=0)

        cache_value = redis_client.get("top_10_products")
        if cache_value is not None:
            print("from_cache")
            redis_client.close()
            return json.loads(cache_value)

        self.cursor.execute("""
                    select p.product_id, name, count(p.product_id) as cnt 
                    from orders o join products p on o.product_id = p.product_id
                    group by p.product_id 
                    order by cnt desc 
                    limit 10""")
        result = self.cursor.fetchall()
        # print("OK")
        redis_client.set("top_10_products", json.dumps(result))
        redis_client.close()

        return result

    # Без изменений
    def no_change(self):
        redis_client = redis.Redis(host="localhost", port=6379, db=0)

        t1 = time()
        self.cursor.execute("select user_id, last_name, first_name from users_redis where user_id = 1;")
        t2 = time()
        result = self.cursor.fetchall()

        cache_value = redis_client.get("user1")
        if cache_value is not None:
            pass
        else:
            redis_client.set("user1", json.dumps(result))

        t11 = time()
        redis_client.get("user1")
        t22 = time()

        redis_client.close()
        return t2 - t1, t22 - t11

    # При добавлении
    def ins_user(self, user_id):
        redis_client = redis.Redis()
        # user_id = randint(1, 1000)

        t1 = time()
        self.cursor.execute(f"insert into users_redis values({user_id}, 'Lastname', 'Firstname', 'phonenumber', 'email', '2024-12-12', '2024-12-12');")
        t2 = time()

        self.cursor.execute(f"select user_id from users_redis where user_id={user_id};")
        result = self.cursor.fetchall()
        data = json.dumps(result)

        t11 = time()
        redis_client.set(f"user{user_id}", data)
        t22 = time()

        redis_client.close()
        self.connection.commit()
        return t2 - t1, t22 - t11

    # При удалении
    def del_user(self, user_id):
        redis_client = redis.Redis()
        # user_id = randint(1, 1000)

        t1 = time()
        self.cursor.execute(f"delete from users_redis where user_id = {user_id};")
        t2 = time()

        t11 = time()
        redis_client.delete(f"user{user_id}")
        t22 = time()

        redis_client.close()
        self.connection.commit()
        return t2 - t1, t22 - t11

    # При изменении
    def upd_user(self, user_id):
        redis_client = redis.Redis()
        # user_id = randint(1000, 2000)

        t1 = time()
        self.cursor.execute(f"update users_redis set email = '@' where user_id = {user_id};")
        t2 = time()

        self.cursor.execute(f"select user_id from users_redis where user_id = {user_id};")
        result = self.cursor.fetchall()
        data = json.dumps(result)

        t11 = time()
        redis_client.set("h" + str(user_id), data)
        t22 = time()

        redis_client.close()
        self.connection.commit()
        return t2 - t1, t22 - t11

# гистограммы
    def task_04(self):
        # simple
        t1 = 0
        t2 = 0
        for i in range(1000):
            b1, b2 = self.no_change()
            t1 += b1
            t2 += b2
        print("simple 100 db redis", t1 / 1000, t2 / 1000)
        index = ["БД", "Redis"]
        values = [t1 / 1000, t2 / 1000]
        plt.bar(index, values)
        plt.title("Без изменения данных")
        plt.show()

        # delete
        t1 = 0
        t2 = 0
        for i in range(1, 1001):
            b1, b2 = self.del_user(i)
            t1 += b1
            t2 += b2
        print("delete 100 db redis", t1 / 1000, t2 / 1000)

        index = ["БД", "Redis"]
        values = [t1 / 1000, t2 / 1000]
        plt.bar(index, values)
        plt.title("При удалении строк")
        plt.show()

        # insert
        t1 = 0
        t2 = 0
        for i in range(1, 1001):
            b1, b2 = self.ins_user(i)
            t1 += b1
            t2 += b2
            # sleep(10)
        print("ins_tour 100 db redis", t1 / 1000, t2 / 1000)

        index = ["БД", "Redis"]
        values = [t1 / 1000, t2 / 1000]
        plt.bar(index, values)
        plt.title("При добавлении строк")
        plt.show()

        # update
        t1 = 0
        t2 = 0
        for i in range(1, 1001):
            b1, b2 = self.upd_user(i)
            t1 += b1
            t2 += b2
        print("update 100 db redis", t1 / 1000, t2 / 1000)

        index = ["БД", "Redis"]
        values = [t1 / 1000, t2/ 1000]
        plt.bar(index, values)
        plt.title("При изменении строк")
        plt.show()


def main():
    db = DB()

    print("1. Получение топ 10 самых покупаемых товаров\n"
          "2. Приложение выполняет запрос каждые 5 секунд на стороне БД. (задание 3.1)\n"
          "3. Приложение выполняет запрос каждые 5 секунд через Redis в качестве кэша. (задание 3.2)\n"
          # "4. Результаты сравнений (задание 3.3)\n"
          "0. Выход\n"
          )

    while True:
        choose = int(input("\n\tВыбор: "))
        if choose == 0:
            break

        if choose == 1:
            res = db.get_top10()
            for elem in res:
                print(elem)
        elif choose == 2:
            print("----------------New-----------------")
            res = db.task_02()
            for el in res:
                print(el)
            print("----------------End-----------------")
        elif choose == 3:
            print("----------------New-----------------")
            res = db.task_03()
            for el in res:
                print(el)
            print("----------------End-----------------")
        # elif choose == 4:
        #     db.task_04()
        else:
            print("Ошибка! Неверная команда!\n")
            break


if __name__ == "__main__":
    main()
