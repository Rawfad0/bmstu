import psycopg2
from config import db_name, user, password, host


class DataBase:
    def __init__(self):
        try:
            self.connection = psycopg2.connect(database=db_name, user=user, password=password, host=host)
            self.cursor = self.connection.cursor()
            print("PostgreSQL connected")

            self.cursor.execute(
                "SELECT version();"
            )
            print(f"Server version: {self.cursor.fetchone()}")
        except Exception as ex:
            print("PostgreSQL connection error\n", ex)

    def __del__(self):
        if self.connection is not None:
            self.cursor.close()
            self.connection.close()

    def create_tables(self):
        try:
            self.cursor.execute(
                """
                
                create table if not exists users
                (
                    id serial primary key,
                    last_name VARCHAR(100),
                    first_name VARCHAR(100),
                    phone_number varchar(15),
                    email varchar(50),
                    birth_date date,
                    reg_date date
                );
                
                create table if not exists products
                (
                    id serial primary key,
                    category varchar(100),
                    name text,
                    description text,
                    average_rating float,
                    review_number float
                );
                
                create table if not exists stores
                (
                    id serial primary key,
                    name text,
                    ogrnip varchar(15),
                    ip text,
                    average_rating float,
                    review_number float
                );
                
                create table if not exists stores_products
                (
                    id serial primary key,
                    store_id int,
                    product_id int,
                    price int,
                    delivery_days int,
                    product_amount int
                );
                
                """
            )
            print("Tables created")
        except Exception as ex:
            print("ERROR in function create_tables\n", ex)

    def copy_tables(self):
        try:
            self.cursor.execute(
                """
                --sql
                
                copy users(
                    id,
                    last_name,
                    first_name,
                    phone_number,
                    email,
                    birth_date,
                    reg_date
                ) from '/Users/Shared/users.csv' delimiter ',' csv;
                
                copy products(
                    id,
                    category,
                    name,
                    description,
                    average_rating,
                    review_number
                ) from '/Users/Shared/products.csv' delimiter ',' csv;
                
                copy stores(
                    id,
                    name,
                    ogrnip,
                    ip,
                    average_rating,
                    review_number
                ) from '/Users/Shared/stores.csv' delimiter ',' csv;

                """
            )
            print("Tables copied")
        except Exception as ex:
            print("ERROR in function copy_tables\n", ex)

    def trunc_tables(self):
        try:
            resp = self.cursor.execute(
                """
                truncate table users, products, stores, stores_products;
                """
            )
            print("Tables truncated")
            print(resp)
        except Exception as ex:
            print("ERROR in function copy_tables\n", ex)

    # def func(self):
    #     self.cursor.execute('SELECT * FROM users')
    #     all_users = self.cursor.fetchall()
    #     print(*all_users, sep='\n')

    def drop_tables(self):
        try:
            self.cursor.execute(
                """
               --sql

               drop table if exists users, products, stores, stores_products
               """
            )
            print("Tables dropped")
        except Exception as ex:
            print("ERROR in function create_tables\n", ex)

    def copy_data(self):
        pass


def main():
    db = DataBase()
    # db.create_tables()
    # db.copy_tables()
    # db.func()
    # db.drop_tables()
    db.trunc_tables()


if __name__ == "__main__":
    main()
