-- 8. Инструкция SELECT, использующая скалярные подзапросы в выражениях столбцов.
-- Получить список продуктов содержащих в названии "Apple iPhone X", их среднюю и минимальную цену
SELECT product_id, name,
    (SELECT AVG(price)
    FROM stores_products
    WHERE products.product_id = stores_products.product_id) AS AvgPrice,
    (SELECT MIN(price)
    FROM stores_products
    WHERE products.product_id = stores_products.product_id) AS MinPrice
FROM products
WHERE name LIKE '%Apple iPhone X%';
