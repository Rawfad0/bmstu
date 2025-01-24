-- 3. Создать таблицу, в которой будет атрибут(-ы) с типом JSON,
-- или добавить атрибут с типом JSON к уже существующей таблице.
-- Заполнить атрибут правдоподобными данными с помощью команд INSERT или UPDATE.

drop table if exists users_json;

create table if not exists users_json
(
    user_id serial primary key,
    personal_data jsonb
);

--copy users_json(personal_data) from '/Users/Shared/users_json.json';
insert into users_json(user_id, personal_data) values
(1, '{"phone_number": "+79815156818", "email": "konovalovaP1949_00001@mail.ru", "birth_date": "1949-07-10", "reg_date": "2017-03-13", "name": {"last_name": "\u041a\u043e\u043d\u043e\u0432\u0430\u043b\u043e\u0432\u0430", "first_name": "\u041f\u0430\u043d\u0444\u0438\u043b"}}'),
(2, '{"phone_number": "+79317572228", "email": "kovalevaA1981_00002@mail.ru", "birth_date": "1981-12-02", "reg_date": "2016-03-29"}'),
(3, NULL),
(4, '{"phone_number": "+79433972136", "email": "rogovF1971_00004@mail.ru", "birth_date": "1971-01-26", "reg_date": "2019-01-26", "name": {"last_name": "\u0420\u043e\u0433\u043e\u0432", "first_name": "\u0424\u0435\u043b\u0438\u043a\u0441"}}'),
(5, '{"phone_number": "+79585703959", "email": "lavrentevaG1957_00005@mail.ru", "birth_date": "1957-10-19", "reg_date": "2019-09-25", "name": {"last_name": "\u041b\u0430\u0432\u0440\u0435\u043d\u0442\u044c\u0435\u0432\u0430", "first_name": "\u0413\u043b\u0435\u0431"}}'),
(6, '{"phone_number": "+79203710821", "email": "isakovK1954_00006@mail.ru", "birth_date": "1954-04-11", "reg_date": "2015-08-17", "name": {"last_name": "\u0418\u0441\u0430\u043a\u043e\u0432", "first_name": "\u041a\u0438\u0440"}}'),
(7, '{"phone_number": "+79914872321", "email": "scherbakovA1958_00007@mail.ru", "birth_date": "1958-06-09", "reg_date": "2014-10-23", "name": {"last_name": "\u0429\u0435\u0440\u0431\u0430\u043a\u043e\u0432", "first_name": "\u0410\u0440\u0435\u0444\u0438\u0439"}}'),
(8, '{"phone_number": "+79375985506", "email": "zhuravlevN1929_00008@mail.ru", "birth_date": "1929-02-07", "reg_date": "2021-05-31", "name": {"last_name": "\u0416\u0443\u0440\u0430\u0432\u043b\u0435\u0432", "first_name": "\u041d\u0430\u0440\u043a\u0438\u0441"}}'),
(9, '{"phone_number": "+79787189813", "email": "burovI1966_00009@mail.ru", "birth_date": "1966-12-03", "reg_date": "2018-01-08", "name": {"last_name": "\u0411\u0443\u0440\u043e\u0432", "first_name": "\u0418\u043b\u044c\u044f"}}'),
(10, '{"phone_number": "+79110441713", "email": "vladimirovK1949_00010@mail.ru", "birth_date": "1949-03-22", "reg_date": "2024-03-09", "name": {"last_name": "\u0412\u043b\u0430\u0434\u0438\u043c\u0438\u0440\u043e\u0432", "first_name": "\u041a\u0430\u0441\u044c\u044f\u043d"}}'),
(11, '{"phone_number": "+79312221688", "email": "koshelevaL1975_00011@mail.ru", "birth_date": "1975-04-21", "reg_date": "2021-05-28", "name": {"last_name": "\u041a\u043e\u0448\u0435\u043b\u0435\u0432\u0430", "first_name": "\u041b\u0430\u0434\u0438\u0441\u043b\u0430\u0432"}}'),
(12, '{"phone_number": "+79838818054", "email": "anisimovM1964_00012@mail.ru", "birth_date": "1964-03-08", "reg_date": "2016-11-27", "name": {"last_name": "\u0410\u043d\u0438\u0441\u0438\u043c\u043e\u0432", "first_name": "\u041c\u0430\u0440\u0442\u044b\u043d"}}'),
(13, '{"phone_number": "+79375501536", "email": "novikovR1951_00013@mail.ru", "birth_date": "1951-07-04", "reg_date": "2015-10-28", "name": {"last_name": "\u041d\u043e\u0432\u0438\u043a\u043e\u0432", "first_name": "\u0420\u0443\u0441\u043b\u0430\u043d"}}'),
(14, '{"phone_number": "+79907700598", "email": "koshelevM1933_00014@mail.ru", "birth_date": "1933-10-04", "reg_date": "2015-05-25", "name": {"last_name": "\u041a\u043e\u0448\u0435\u043b\u0435\u0432", "first_name": "\u041c\u0438\u043b\u0430\u043d"}}'),
(15, '{"phone_number": "+79898713812", "email": "samojlovaD2008_00015@mail.ru", "birth_date": "2008-10-05", "reg_date": "2020-01-29", "name": {"last_name": "\u0421\u0430\u043c\u043e\u0439\u043b\u043e\u0432\u0430", "first_name": "\u0414\u0430\u0440\u044c\u044f"}}'),
(16, '{"phone_number": "+79868835402", "email": "burovL1953_00016@mail.ru", "birth_date": "1953-07-20", "reg_date": "2023-08-19", "name": {"last_name": "\u0411\u0443\u0440\u043e\u0432", "first_name": "\u041b\u0443\u043a\u0438\u044f"}}'),
(17, '{"phone_number": "+79124203451", "email": "bespalovaJa1983_00017@mail.ru", "birth_date": "1983-04-02", "reg_date": "2021-05-22", "name": {"last_name": "\u0411\u0435\u0441\u043f\u0430\u043b\u043e\u0432\u0430", "first_name": "\u042f\u043a\u043e\u0432"}}'),
(18, '{"phone_number": "+79829907606", "email": "maslovaM1994_00018@mail.ru", "birth_date": "1994-10-31", "reg_date": "2019-12-21", "name": {"last_name": "\u041c\u0430\u0441\u043b\u043e\u0432\u0430", "first_name": "\u041c\u0438\u043d\u0430"}}'),
(19, '{"phone_number": "+79173439782", "email": "zhdanovaA1992_00019@mail.ru", "birth_date": "1992-11-11", "reg_date": "2017-09-09", "name": {"last_name": "\u0416\u0434\u0430\u043d\u043e\u0432\u0430", "first_name": "\u0410\u043d\u0436\u0435\u043b\u0438\u043a\u0430"}}'),
(20, '{"phone_number": "+79370009463", "email": "turovaA1976_00020@mail.ru", "birth_date": "1976-09-30", "reg_date": "2021-12-10", "name": {"last_name": "\u0422\u0443\u0440\u043e\u0432\u0430", "first_name": "\u0410\u043d\u0434\u0440\u043e\u043d"}}')

-- Удалил имя у пользователя с id=2
-- "name": {"last_name": "\u041a\u043e\u0432\u0430\u043b\u0435\u0432\u0430", "first_name": "\u0410\u043d\u0442\u043e\u043d\u0438\u043d"}

-- Удалил атрибут personal_data у пользователя с id=3
-- '{"phone_number": "+79499999148", "email": "ustinovA1940_00003@mail.ru", "birth_date": "1940-01-15", "reg_date": "2015-02-02", "name": {"last_name": "\u0423\u0441\u0442\u0438\u043d\u043e\u0432", "first_name": "\u0410\u043d\u0434\u0440\u0435\u0439"}}'


