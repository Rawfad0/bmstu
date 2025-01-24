-- 5. Триггер CLR
-- Если пользователь покупает товар с самой низкой оценкой, то пользователь удаляется

-- Функция для триггера
-- Удалить пользователя, если товар в заказе имеет наименьшую оценку
CREATE OR REPLACE FUNCTION remove_user_trig_func_py ()
RETURNS TRIGGER
AS $$
    product_ids = plpy.execute("""select product_id
        from products
        where average_rating = (
            select min(average_rating)
            from products
        )"""
    )
    product_ids_arr = [id['product_id'] for id in product_ids]

    if TD['new']['product_id'] in product_ids_arr:
        plpy.execute(f"""
            delete from users
            where users.user_id = {TD['new']['user_id']};
            """
        )
    return None
$$ LANGUAGE plpython3u;

-- Сам триггер
CREATE OR REPLACE TRIGGER delete_user_trigger_py
AFTER INSERT ON orders
FOR EACH ROW EXECUTE FUNCTION remove_user_trig_func_py();

-- Добавить 4х пользователей в таблицу
INSERT INTO users VALUES
(1001, 'Name1', 'Name1', '+7999999999', '2000-01-01', '2000-01-01'),
(1002, 'Name2', 'Name2', '+7999999999', '2000-01-01', '2000-01-01'),
(1003, 'Name3', 'Name3', '+7999999999', '2000-01-01', '2000-01-01'),
(1004, 'Name4', 'Name4', '+7999999999', '2000-01-01', '2000-01-01');

-- Вывести продукты c наименьшей оценкой
select product_id, average_rating
from products
where average_rating = (
    select min(average_rating)
    from products
);
-- Вывести все заказы с товарами с наименьшей оценкой
select order_id, product_id
from orders
where product_id in (
    select product_id
    from products
    where average_rating = (
        select min(average_rating)
        from products
    )
);

select *
from users
where user_id > 1000;

-- Добавить 4 заказа
INSERT INTO orders VALUES
(1001, 1001, 482, 1001, 1, 10, 100),
(1002, 1002, 100, 1001, 1, 10, 100),
(1003, 1003, 101, 1001, 1, 10, 100),
(1004, 1004, 482, 1001, 1, 10, 100);

select *
from users
where user_id > 1000;

delete from orders
where user_id > 1000;

delete from users
where user_id > 1000;

drop trigger delete_user_trigger_py on orders;