-- 2. Пользовательская агрегатная функция CLR
-- Количество заказов, сделанных пользователем
CREATE OR REPLACE FUNCTION count_user_orders(id integer)
RETURNS integer
AS $$
    orders = plpy.execute("SELECT * FROM orders")
    k = 0
    for order in orders:
        if order['user_id'] == id:
            k += 1
    return k
$$ LANGUAGE plpython3u;

SELECT count_user_orders(101);

SELECT COUNT(user_id)
FROM orders
WHERE user_id = 101;
