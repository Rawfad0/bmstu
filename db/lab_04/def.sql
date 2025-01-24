-- Для пользователя средняя, медианная и квадратичная цена купленных товаров

CREATE OR REPLACE FUNCTION avg_medium_sq_avg()
RETURNS TABLE (user_id integer, avg float, median float, sq_avg float)
AS $$
    import statistics
    users = plpy.execute("SELECT * FROM users")
    orders = plpy.execute("SELECT * FROM orders")
    res = []
    for user in users:
        user_order_prices = [order['order_price'] for order in orders if order['user_id'] == user['user_id']]
        k = len(user_order_prices)
        # plpy.notice(user_order_prices, sum(user_order_prices), k)
        sq = 0
        for price in user_order_prices:
            sq += price**2
        if k == 1:
            res.append(
                {
                    'user_id': user['user_id'],
                    'avg': user_order_prices[0],
                    'median': user_order_prices[0],
                    'sq_avg': user_order_prices[0]
                }
            )
        elif k > 0:
            res.append(
                {
                    'user_id': user['user_id'],
                    'avg': statistics.mean(user_order_prices),
                    'median': statistics.median(user_order_prices),
                    'sq_avg': statistics.stdev(user_order_prices, 0) * ((k-1)/k)**0.5
                }
            )
        else:
            res.append(
                {
                    'user_id': user['user_id'],
                    'avg': None,
                    'median': None,
                    'sq_avg': None
                }
            )
    return res
$$ LANGUAGE plpython3u;

-- 'median': user_order_prices[k//2] if k % 2 == 1 else (user_order_prices[k//2 - 1] + user_order_prices[k//2]) / 2,
-- (sq / k)**0.5
-- statistics.stdev(user_order_prices, 0) * ((k-1)/k)**0.5
-- (statistics.variance(user_order_prices, 0) * (k - 1) / k)**0.5
-- id=7: [5496, 10444, 369136]
SELECT *
FROM avg_medium_sq_avg()
LIMIT 30;

select order_id, user_id, order_price
from orders
where user_id = 7;


select order_id, user_id, order_price
from orders
where user_id = 8;