import os.path
from random import random, choices, choice
import time
from datetime import date, datetime
from faker import Faker
from transliterate import translit, slugify
from csv import writer, reader
import json
from string import ascii_lowercase, ascii_uppercase
import codecs


class UniqRealData:
    def __init__(self,
                 real_data='./Yandex_Market_electronica.csv',
                 products_data='./products.json',
                 stores_data='./stores.json'):
        self.real_data = real_data
        self.products_data = products_data
        self.stores_data = stores_data

        self.products = self.load_products_from_file()
        self.stores = self.load_stores_from_file()

    def parse_real_data(self):
        if not os.path.exists(self.real_data):
            print("No real data file.")
            return False
        else:
            print("Ok")
            with (open(self.real_data, 'r', newline='', encoding='cp1251') as src,
                  codecs.open(self.products_data, 'w', encoding='utf-8') as dst_p,
                  codecs.open(self.stores_data, 'w', encoding='utf-8') as dst_s):
                src.readline()
                src.readline()
                products = []
                stores = []
                csv_reader = reader(src, delimiter=';')
                for row in csv_reader:
                    product = {
                        "category": row[2],
                        "name": row[3],
                        "descr": row[6]
                    }
                    if product["category"] != "" and product["name"] != "" and product["descr"] != "":
                        products.append(product)
                    stores_json_str = row[12]
                    if stores_json_str == "":
                        continue
                    stores_json = json.loads(stores_json_str)
                    stores.extend([store_json['ShopName']
                                   for store_json in stores_json
                                   if store_json['ShopName'] is not None])
                stores = list(set(stores))
                stores_x3 = []  # Т.к. всего 351 уникальный магазин, то пришлось размножить их в три раза
                for store in stores:
                    stores_x3.extend(["001_"+store, "002_"+store, "003_"+store])

                json.dump(products, dst_p, ensure_ascii=False)
                json.dump(stores_x3, dst_s, ensure_ascii=False)

                # print(*products, sep='\n')
                print("Товаров добавлено: ", len(products))
                # print(*stores_x3, sep='\n')
                print("Магазинов добавлено:", len(stores_x3))
            return True

    def load_products_from_file(self):
        if (not os.path.exists(self.products_data)) and (not self.parse_real_data()):
            return []
        with open(self.products_data, 'r') as f:
            products_json = json.load(f)
            products = [
                {
                    "category": product["category"],
                    "name": product["name"],
                    "descr": product["descr"]
                }
                for product in products_json]
        return products

    def load_stores_from_file(self):
        if (not os.path.exists(self.stores_data)) and (not self.parse_real_data()):
            return []
        with open(self.stores_data, 'r') as f:
            stores_json = json.load(f)
            stores = [store for store in stores_json]
        # print(*stores, sep='\n')
        return stores

    def get_unique_product(self):
        product = choice(self.products)
        self.products.remove(product)
        return product

    def get_unique_store(self):
        store = choice(self.stores)
        self.stores.remove(store)
        return store


class UserData:
    def __init__(self, user_id, last_name, first_name, phone_number, email, birth_date, reg_date):
        self.user_id = user_id
        self.last_name = last_name
        self.first_name = first_name
        self.phone_number = phone_number
        self.email = email
        self.birth_date = birth_date
        self.reg_date = reg_date

    def __repr__(self):
        return ', '.join([str(self.user_id),
                          self.last_name,
                          self.first_name,
                          self.phone_number,
                          self.email,
                          self.birth_date,
                          self.reg_date])


class UserDataGenerator:
    def __init__(self, user_id=0, last_name_path='', first_name_path=''):
        self.user_id = user_id
        self.last_name_path = last_name_path
        self.first_name_path = first_name_path
        self.fake = Faker("ru_RU")
        self.date_format = '%Y-%m-%d'

    @staticmethod
    def random_date(begin, end, time_format):
        begin_time = time.mktime(time.strptime(begin, time_format))
        end_time = time.mktime(time.strptime(end, time_format))

        ptime = begin_time + random() * (end_time - begin_time)
        return time.strftime(time_format, time.localtime(ptime))

    @staticmethod
    def date_add_years(d, years):
        try:
            return d.replace(year=d.year + years)
        except ValueError:
            return d + (date(d.year + years, 1, 1) - date(d.year, 1, 1))

    def user_id_gen(self):
        self.user_id += 1
        return self.user_id

    def last_name_gen(self):
        if self.last_name_path == '':
            return self.fake.last_name()
        else:
            pass

    def first_name_gen(self):
        if self.first_name_path == '':
            return self.fake.first_name()
        else:
            pass

    @staticmethod
    def phone_number_gen():
        random_part = int(899_999_999 * random()) + 100_000_000
        phone_number = "+79" + str(random_part)
        return phone_number

    def email_gen(self, last_name, first_name, birth_date):
        # year = birth_date[-4:]
        year = datetime.strptime(birth_date, self.date_format).year
        # random_chars = ''.join([choice(ascii_letters) for _ in range(8)])
        # print(random_chars)
        translit_last_name = slugify(last_name)
        # translit_last_name = translit(last_name, language_code='ru', reversed=True)
        translit_first_name = translit(first_name[0], language_code='ru', reversed=True)
        email = f'{translit_last_name}{translit_first_name}{year}_{self.user_id:05g}@mail.ru'
        return email

    def birth_date_gen(self):
        cur_date = date.today()
        begin_date = self.date_add_years(cur_date, -100).strftime(self.date_format)  # cur_date - 100
        end_date = self.date_add_years(cur_date, -14).strftime(self.date_format)  # cur_date - 14
        random_date = self.random_date(begin_date, end_date, self.date_format)
        return random_date

    def reg_date_gen(self):
        cur_date = date.today()
        begin_date = self.date_add_years(cur_date, -10).strftime(self.date_format)
        random_date = self.random_date(begin_date, cur_date.strftime(self.date_format), self.date_format)
        return random_date

    def generate(self):
        user_id = self.user_id_gen()
        last_name = self.last_name_gen()
        first_name = self.first_name_gen()
        phone_number = self.phone_number_gen()
        birth_date = self.birth_date_gen()
        email = self.email_gen(last_name, first_name, birth_date)
        reg_date = self.reg_date_gen()
        # user_data = UserData(user_id=user_id,
        #                      last_name=last_name,
        #                      first_name=first_name,
        #                      phone_number=phone_number,
        #                      email=email,
        #                      birth_date=birth_date,
        #                      reg_date=reg_date)
        user_data = [user_id,
                     last_name,
                     first_name,
                     phone_number,
                     email,
                     birth_date,
                     reg_date]
        return user_data

    def generate_num(self, num: int):
        users_data = [self.generate() for _ in range(num)]
        return users_data


class ProductData:
    def __init__(self, product_id, category, name, description, average_rating, review_number):
        self.product_id = product_id
        self.category = category
        self.name = name
        self.description = description
        self.average_rating = average_rating
        self.review_number = review_number

    def __repr__(self):
        return ', '.join([str(self.product_id),
                          self.category,
                          self.name,
                          self.description,
                          str(self.average_rating),
                          str(self.review_number)])


class ProductDataGenerator:
    def __init__(self, uniq=None, product_id=0, category_path='', name_path='', description_path=''):
        self.product_id = product_id
        self.category_path = category_path
        self.name_path = name_path
        self.description_path = description_path
        self.uniq = uniq

    def product_id_gen(self):
        self.product_id += 1
        return self.product_id

    def category_gen(self):
        if self.category_path == '':
            return 'Category'
        else:
            pass

    def name_gen(self):
        if self.name_path == '':
            return 'ProductName_' + ''.join(choices(ascii_uppercase + ascii_lowercase, k=10))
        else:
            pass

    def description_gen(self):
        if self.description_path == '':
            return 'Description'
        else:
            pass

    def get_from_unique_product(self):
        product = self.uniq.get_unique_product()
        return product["category"], product["name"], product["descr"]

    @staticmethod
    def average_rating_gen():
        rating = 4 * random() + 1
        return rating

    @staticmethod
    def review_number_gen():
        rating = int(300 * random())
        return rating

    def generate(self):
        product_id = self.product_id_gen()
        category, name, description = self.get_from_unique_product()
        # category = self.category_gen()
        # name = self.name_gen()
        # description = self.description_gen()
        average_rating = self.average_rating_gen()
        review_number = self.review_number_gen()
        # product_data = ProductData(product_id=product_id,
        #                            category=category,
        #                            name=name,
        #                            description=description,
        #                            average_rating=average_rating,
        #                            review_number=review_number)
        product_data = [product_id,
                        category,
                        name,
                        description,
                        average_rating,
                        review_number]
        return product_data

    def generate_num(self, num: int):
        products_data = [self.generate() for _ in range(num)]
        return products_data


class StoreData:
    def __init__(self, store_id, name, ogrnip, ip, average_rating, review_number):
        self.store_id = store_id
        self.name = name
        self.ogrnip = ogrnip
        self.ip = ip
        self.average_rating = average_rating
        self.review_number = review_number

    def __repr__(self):
        return ', '.join([str(self.store_id),
                          self.name,
                          self.ogrnip,
                          self.ip,
                          str(self.average_rating),
                          str(self.review_number)])


class StoreDataGenerator:
    def __init__(self, uniq=None, store_id=0, name_path='', ip_path=''):
        self.store_id = store_id
        self.name_path = name_path
        self.ip_path = ip_path
        self.fake = Faker("ru_RU")
        self.uniq = uniq

    def store_id_gen(self):
        self.store_id += 1
        return self.store_id

    def name_gen(self):
        if self.name_path == '':
            return 'StoreName' + ''.join(choices(ascii_uppercase + ascii_lowercase, k=10))
        else:
            pass

    @staticmethod
    def ogrnip_gen():
        return str(int(899_999_999_999_999 * random()) + 100_000_000_000_000)

    def ip_gen(self):
        if self.ip_path == '':
            return self.fake.name()
        else:
            pass

    @staticmethod
    def average_rating_gen():
        rating = 4 * random() + 1
        return rating

    @staticmethod
    def review_number_gen():
        rating = int(10000 * random())
        return rating

    def get_from_unique_store(self):
        store = self.uniq.get_unique_store()
        return store

    def generate(self):
        store_id = self.store_id_gen()
        name = self.get_from_unique_store()
        # name = self.name_gen()
        ogrnip = self.ogrnip_gen()
        ip = self.ip_gen()
        average_rating = self.average_rating_gen()
        review_number = self.review_number_gen()
        # store_data = StoreData(store_id=store_id,
        #                        name=name,
        #                        ogrnip=ogrnip,
        #                        ip=ip,
        #                        average_rating=average_rating,
        #                        review_number=review_number)
        store_data = [store_id,
                      name,
                      ogrnip,
                      ip,
                      average_rating,
                      review_number]
        return store_data

    def generate_num(self, num: int):
        stores_data = [self.generate() for _ in range(num)]
        return stores_data


class StoreProduct:
    pass


class StoreProductGenerator:
    def __init__(self, store_product_id=0, store_id=0, product_id=0):
        self.store_product_id = store_product_id
        self.store_id = store_id
        self.product_id = product_id

    def store_product_id_gen(self):
        self.store_product_id += 1
        return self.store_product_id

    def store_id_gen(self):
        return int(self.store_id * random())

    def product_id_gen(self):
        return int(self.product_id * random())

    @staticmethod
    def price_gen():
        return int(100_000 * random())

    @staticmethod
    def delivery_days_gen():
        return int(90 * random())

    @staticmethod
    def product_quantity_gen():
        return int(1000 * random())

    def generate(self):
        store_product_id = self.store_product_id_gen()
        store_id = self.store_id_gen()
        product_id = self.product_id_gen()
        price = self.price_gen()
        delivery_days = self.delivery_days_gen()
        product_quantity = self.product_quantity_gen()
        stores_products_data = [store_product_id,
                                store_id,
                                product_id,
                                price,
                                delivery_days,
                                product_quantity]
        return stores_products_data

    def generate_num(self, num: int):
        products_stores_data = [self.generate() for _ in range(num)]
        return products_stores_data


class OrdersGenerator:
    def __init__(self, order_id=0, user_id=0, product_id=0):
        self.order_id = order_id
        self.user_id = user_id
        self.product_id = product_id

    def order_id_gen(self):
        self.order_id += 1
        return self.order_id

    def user_id_gen(self):
        return int(self.user_id * random())

    def product_id_gen(self):
        return int(self.product_id * random())

    @staticmethod
    def delivery_days_gen():
        return int(90 * random())

    @staticmethod
    def product_quantity_gen():
        return int((5 - 1) * random()) + 1

    @staticmethod
    def price_gen(product_quantity):
        return int(100_000 * random()) * product_quantity

    def generate(self):
        order_id = self.order_id_gen()
        user_id = self.user_id_gen()
        product_id = self.product_id_gen()
        delivery_days = self.delivery_days_gen()
        product_quantity = self.product_quantity_gen()
        price = self.price_gen(product_quantity)
        orders_data = [order_id,
                                user_id,
                                product_id,
                                delivery_days,
                                product_quantity,
                                price,]
        return orders_data

    def generate_num(self, num: int):
        orders_data = [self.generate() for _ in range(num)]
        return orders_data


def main():
    path = "/Users/Shared/"
    uniq = UniqRealData()

    # users = UserDataGenerator().generate_num(1000)
    # with open(f"{path}users.csv", "w", newline="") as file:
    #     csv_writer = writer(file)
    #     csv_writer.writerows(users)
    # print(*users, '', sep='\n')
    #
    # products = ProductDataGenerator(uniq=uniq).generate_num(1000)
    # with open(f"{path}products.csv", "w", newline="") as file:
    #     csv_writer = writer(file)
    #     csv_writer.writerows(products)
    # print(*products, '', sep='\n')

    stores = StoreDataGenerator(uniq=uniq).generate_num(1000)
    with open(f"{path}stores.csv", "w", newline="") as file:
        csv_writer = writer(file)
        csv_writer.writerows(stores)
    print(*stores, sep='\n')

    # stores_products = StoreProductGenerator(0, 1000, 1000).generate_num(1000)
    # with open(f"{path}stores_products.csv", "w", newline="") as file:
    #     csv_writer = writer(file)
    #     csv_writer.writerows(stores_products)
    # print(*stores_products, sep='\n')

    orders = OrdersGenerator(0, 1000, 1000).generate_num(1000)
    with open(f"{path}orders.csv", "w", newline="") as file:
        csv_writer = writer(file)
        csv_writer.writerows(orders)
    print(*orders, sep='\n')


if __name__ == "__main__":
    main()
