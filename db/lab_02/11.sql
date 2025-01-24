-- 11. Создание новой временной локальной таблицы из результирующего набора данных инструкции SELECT.
SELECT products.product_id, SUM(product_quantity) AS SQ,
    SUM(price*product_quantity) AS SP
INTO TEMP TABLE TMP_TABLE
FROM products JOIN stores_products ON products.product_id = stores_products.product_id
GROUP BY products.product_id;


SELECT * FROM TMP_TABLE;

--SELECT ProductID, SUM(Quantity) AS SQ,
--    CAST(SUM(UnitPrice*Quantity*(1.0-Discount)) AS money) AS SR
--INTO TEMP TABLE #BestSelling
--FROM [Order Details]
--WHERE ProductID IS NOT NULL
--GROUP BY productID;
