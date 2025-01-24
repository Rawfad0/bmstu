-- 4. Выполнить следующие действия:
--    1. Извлечь JSON фрагмент из JSON документа
--    2. Извлечь значения конкретных узлов или атрибутов JSON документа
--    3. Выполнить проверку существования узла или атрибута
--    4. Изменить JSON документ
--    5. Разделить JSON документ на несколько строк по узлам


--    1. Извлечь JSON фрагмент из JSON документа
select user_id,
       personal_data->>'name' as name,
       personal_data->>'birth_date' as birth_date,
from users_json;

--    2. Извлечь значения конкретных узлов или атрибутов JSON документа
select user_id,
       personal_data->'name'->>'last_name' as last_name,
       personal_data->'name'->>'first_name' as first_name,
       personal_data->>'phone_number' as phone_number,
       personal_data->>'birth_date' as birth_date
from users_json;

--    3. Выполнить проверку существования узла или атрибута
select user_id,
       personal_data->'name'->>'last_name' as last_name,
       personal_data->'name'->>'first_name' as first_name,
       personal_data->>'birth_date' as birth_date
from users_json
where personal_data is not NULL and personal_data->'name' is not NULL;

--    4. Изменить JSON документ
update users_json
set personal_data = personal_data || '{"phone_number": "+79991110011"}'::jsonb
where personal_data->'name'->>'first_name' like 'Феликс';

select user_id,
       personal_data->'name'->>'first_name' as first_name,
       personal_data->>'phone_number' as phone_number
from users_json
where personal_data is not NULL and personal_data->'name' is not NULL;

--    5. Разделить JSON документ на несколько строк по узлам

drop table if exists users_json2;
create table if not exists users_json2
(
    user_id serial primary key,
    personal_data jsonb
);
insert into users_json2(user_id, personal_data) values
(1, '{"phone_number": "+79815156818", "email": "konovalovaP1949_00001@mail.ru", "birth_date": "1949-07-10", "reg_date": "2017-03-13", "name": ["\u041a\u043e\u043d\u043e\u0432\u0430\u043b\u043e\u0432\u0430", "\u041f\u0430\u043d\u0444\u0438\u043b"]}'),
(2, '{"phone_number": "+79317572228", "email": "kovalevaA1981_00002@mail.ru", "birth_date": "1981-12-02", "reg_date": "2016-03-29", "name": ["\u041a\u043e\u0432\u0430\u043b\u0435\u0432\u0430", "\u0410\u043d\u0442\u043e\u043d\u0438\u043d"]}'),
(3, '{"phone_number": "+79499999148", "email": "ustinovA1940_00003@mail.ru", "birth_date": "1940-01-15", "reg_date": "2015-02-02", "name": ["\u0423\u0441\u0442\u0438\u043d\u043e\u0432", "\u0410\u043d\u0434\u0440\u0435\u0439"]}'),
(4, '{"phone_number": "+79433972136", "email": "rogovF1971_00004@mail.ru", "birth_date": "1971-01-26", "reg_date": "2019-01-26", "name": ["\u0420\u043e\u0433\u043e\u0432", "\u0424\u0435\u043b\u0438\u043a\u0441"]}'),
(5, '{"phone_number": "+79585703959", "email": "lavrentevaG1957_00005@mail.ru", "birth_date": "1957-10-19", "reg_date": "2019-09-25", "name": ["\u041b\u0430\u0432\u0440\u0435\u043d\u0442\u044c\u0435\u0432\u0430", "\u0413\u043b\u0435\u0431"]}'),
(6, '{"phone_number": "+79203710821", "email": "isakovK1954_00006@mail.ru", "birth_date": "1954-04-11", "reg_date": "2015-08-17", "name": ["\u0418\u0441\u0430\u043a\u043e\u0432", "\u041a\u0438\u0440"]}'),
(7, '{"phone_number": "+79914872321", "email": "scherbakovA1958_00007@mail.ru", "birth_date": "1958-06-09", "reg_date": "2014-10-23", "name": ["\u0429\u0435\u0440\u0431\u0430\u043a\u043e\u0432", "\u0410\u0440\u0435\u0444\u0438\u0439"]}'),
(8, '{"phone_number": "+79375985506", "email": "zhuravlevN1929_00008@mail.ru", "birth_date": "1929-02-07", "reg_date": "2021-05-31", "name": ["\u0416\u0443\u0440\u0430\u0432\u043b\u0435\u0432", "\u041d\u0430\u0440\u043a\u0438\u0441"]}'),
(9, '{"phone_number": "+79787189813", "email": "burovI1966_00009@mail.ru", "birth_date": "1966-12-03", "reg_date": "2018-01-08", "name": ["\u0411\u0443\u0440\u043e\u0432", "\u0418\u043b\u044c\u044f"]}'),
(10, '{"phone_number": "+79110441713", "email": "vladimirovK1949_00010@mail.ru", "birth_date": "1949-03-22", "reg_date": "2024-03-09", "name": ["\u0412\u043b\u0430\u0434\u0438\u043c\u0438\u0440\u043e\u0432", "\u041a\u0430\u0441\u044c\u044f\u043d"]}');

select user_id, name
from users_json2, jsonb_array_elements((personal_data->'name')::jsonb) as name;
