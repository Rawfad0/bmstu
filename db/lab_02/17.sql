-- 17. Многострочная инструкция INSERT, выполняющая вставку в таблицу результирующего набора данных вложенного подзапроса.
INSERT INTO orders (order_id, user_id, product_id, delivery_days, product_quantity, order_price)
SELECT
    (SELECT MAX(order_id)+1
        FROM orders),
    1001, 100, 10,
    1 as product_quantity,
    1*(SELECT MIN(price)
        FROM products JOIN stores_products ON products.product_id = stores_products.product_id
        WHERE products.product_id = 100)