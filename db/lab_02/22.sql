-- 22. Инструкция SELECT, использующая простое обобщенное табличное выражение
WITH SPQ (store_id, product_quantity) AS (
    SELECT store_id, COUNT(*) AS Total
    FROM stores_products
    GROUP BY store_id
)
SELECT AVG(product_quantity) AS "Ср. кол-во разных товаров у продавцов"
FROM SPQ