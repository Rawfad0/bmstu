-- 25. Оконные функции для устранения дублей
-- Придумать запрос, в результате которого в данных появляются полные дубли.
-- Устранить дублирующиеся строки с использованием функции ROW_NUMBER().
SELECT * FROM (
    SELECT P.product_id, P.name,
        AVG(SP.price) OVER(PARTITION BY P.product_id, P.name) AS AvgPrice,
        MIN(SP.price) OVER(PARTITION BY P.product_id, P.name) AS MinPrice,
        MAX(SP.price) OVER(PARTITION BY P.product_id, P.name) AS MaxPrice,
        row_number() OVER(PARTITION BY P.product_id order by P.name) AS N
    FROM products P LEFT OUTER JOIN stores_products SP ON SP.product_id = P.product_id) AS Prices
WHERE N = 1;
