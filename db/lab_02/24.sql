-- 24. Оконные функции. Использование конструкций MIN/MAX/AVG OVER()
-- Для каждого продаваемого продукта вывести его цену
-- и среднее, минимальное и максимальное среди всех продавцов
SELECT P.product_id, P.name, SP.price,
    AVG(SP.price) OVER(PARTITION BY P.product_id, P.name) AS AvgPrice,
    MIN(SP.price) OVER(PARTITION BY P.product_id, P.name) AS MinPrice,
    MAX(SP.price) OVER(PARTITION BY P.product_id, P.name) AS MaxPrice
FROM products P LEFT OUTER JOIN stores_products SP ON SP.product_id = P.product_id