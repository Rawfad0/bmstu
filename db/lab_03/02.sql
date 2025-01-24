-- 2. Подставляемая табличная функция
-- Функция возвращает продавцов (id, name и количество), которые продают не менее min_n товаров
CREATE OR REPLACE FUNCTION stores_ge_n (min_n integer)
RETURNS TABLE (store_id integer, name text, product_count bigint)
AS $$
BEGIN
    RETURN QUERY
    SELECT s.store_id, s.name, s.product_count
    FROM (
        SELECT s.store_id, s.name, COUNT(s.store_id) as product_count
        FROM stores as s LEFT JOIN stores_products as sp on s.store_id = sp.store_id
        GROUP BY s.store_id
    ) as s
    WHERE s.product_count >= min_n;
END
$$ LANGUAGE PLPGSQL;

-- Вывести продавцов, которые продают не менее 4 товаров
SELECT *
FROM stores_ge_n(4)
ORDER BY store_id;