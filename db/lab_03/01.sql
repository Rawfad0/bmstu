-- 1. Разработать и тестировать скалярную функцию
-- Вычисление цены всей партии(?) определенного продукта
CREATE OR REPLACE FUNCTION calc_total_price (price integer, quantity integer)
RETURNS integer
AS $$
    RETURN quantity * price;
$$ LANGUAGE plpython3u;

-- Применение функции к каждой строке
SELECT sp_id, calc_total_price(price, product_quantity) as total_price
FROM stores_products
ORDER BY sp_id;

---- Суммарная стоимость каждого типа товара у продавцов
--SELECT product_id, SUM(total_price)
--FROM (
--    SELECT sp_id, product_id, calc_total_price(price, product_quantity) as total_price
--    FROM stores_products
--)
--GROUP BY product_id;