-- 2. Выполнить загрузку и сохранение JSON файла в таблицу.
-- Созданная таблица после всех манипуляций должна соответствовать таблице базы данных,
-- созданной в первой лабораторной работе.

drop table if exists users_from_json;
drop table if exists users_from_json_tmp;
create table if not exists users_from_json
(
    user_id int primary key,
    last_name varchar(100),
    first_name varchar(100),
    phone_number varchar(15),
    email varchar(50),
    birth_date date,
    reg_date date,
    constraint rd_after_bd_json check (reg_date > birth_date)
);

create table if not exists users_from_json_tmp
(
    data jsonb
);
copy users_from_json_tmp(data) from '/Users/Shared/users.json';

insert into users_from_json(
    user_id,
    last_name,
    first_name,
    phone_number,
    email,
    birth_date,
    reg_date
)
select (data->'user_id')::int,
    data->>'last_name',
    data->>'first_name',
    data->>'phone_number',
    data->>'email',
    (data->>'birth_date')::date,
    (data->>'reg_date')::date
from users_from_json_tmp;
