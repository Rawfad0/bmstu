-- 5. Инструкция SELECT, использующая предикат EXISTS с вложенным подзапросом.
-- Получить список товаров стоимостью ниже 1000 хотя бы в одном магазине
SELECT product_id, name
FROM products
WHERE EXISTS (SELECT *
    FROM stores_products
    WHERE products.product_id = stores_products.product_id AND price < 1000);

--SELECT products.id, products.name
--FROM products JOIN stores_products ON products.id = stores_products.product_id
--WHERE price < 1000;
