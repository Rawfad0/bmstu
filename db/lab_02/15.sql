-- 15. Инструкция SELECT, консолидирующая данные с помощью предложения GROUP BY и предложения HAVING.
-- Получить список категорий цен, средняя оценка которых больше общей средней оценки продуктов

SELECT Price, AVG(average_rating) as "Average Rating"
FROM (
    SELECT name, average_rating,
        CASE
            WHEN price < 10000 THEN 'Inexpensive'
            WHEN price < 50000 THEN 'Fair'
            WHEN price < 80000 THEN 'Expensive'
            ELSE 'Very Expensive'
        END AS Price
    FROM products JOIN stores_products ON products.product_id = stores_products.product_id
) as prices
GROUP BY Price
HAVING AVG(average_rating) > (SELECT AVG(average_rating)
    FROM products)
