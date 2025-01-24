import json
import os
from faker import Faker
from random import random, choices, choice
import time
from datetime import date, datetime
from transliterate import translit, slugify

id_user = 0
id = 0  # идентификатор файла


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
        user_data = [user_id,
                     last_name,
                     first_name,
                     phone_number,
                     email,
                     birth_date,
                     reg_date]
        return user_data


udg = UserDataGenerator()


def generate_json(count):
    global id_user
    users = []
    for i in range(count):
        user = udg.generate()
        user_json = {
            "user_id": id_user + i + 1,
            "last_name": user[1],
            "first_name": user[2],
            "phone_number": user[3],
            "email": user[4],
            "birth_date": user[5],
            "reg_date": user[6]}
        users.append(user_json)
    id_user += count
    return json.dumps(users, ensure_ascii=False, indent=4)


def main():
    dirpath = '/Users/rf9/Downloads/nifi-1.28.1/in_file/'
    global id
    if not os.path.exists(dirpath):
        os.makedirs(dirpath)
    while True:
        file_name = f"users_nifi_{id}_{datetime.now().strftime('%Y-%m-%d-%H.%M.%S')}.json"
        with open(dirpath + file_name, "w", encoding='utf-8') as f:
            s = generate_json(10)
            # print(s)
            f.write(s)
        print("Create file: ", dirpath + file_name)
        id += 1
        time.sleep(300)


if __name__ == "__main__":
    main()
