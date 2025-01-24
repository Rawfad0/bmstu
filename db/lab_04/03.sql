-- 3. Определяемая пользователем табличная функция CLR
-- Возвращает пользователей, сделавших не менее N заказов
CREATE OR REPLACE FUNCTION get_users_with_orders_count_ge_n(min_n integer)
RETURNS TABLE (user_id integer, email text, order_count integer)
AS $$
    users = plpy.execute("SELECT * FROM users")
    orders = plpy.execute("SELECT * FROM orders")
    res = []
    for user in users:
        k = 0
        for order in orders:
            if user['user_id'] == order['user_id']:
                k += 1
        if k >= min_n:
            res.append(
                {
                    'user_id': user['user_id'],
                    'email': user['email'],
                    'order_count': k
                }
            )
    return res
$$ LANGUAGE plpython3u;

SELECT *
FROM get_users_with_orders_count_ge_n(4)
ORDER BY order_count DESC;

