-- 21. Инструкция DELETE с вложенным коррелированным подзапросом в предложении WHERE.
-- Пример для базы данных AdventureWorks

INSERT INTO products (product_id, category, name, description, average_rating, review_number)
VALUES (1001, 'NULL', 'NULL', NULL, 1.0, 1);

INSERT INTO orders (order_id, user_id, product_id, delivery_days, product_quantity, order_price)
VALUES (1001, 1001, 1001, 1, 1, 1000);

DELETE FROM orders
WHERE product_id IN ( SELECT O.product_id
    FROM orders O LEFT OUTER JOIN products P ON P.product_id = O.product_id
    WHERE P.description IS NULL);