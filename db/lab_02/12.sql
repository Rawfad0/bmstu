-- 12. Инструкция SELECT, использующая вложенные коррелированные подзапросы в качестве производных таблиц в предложении FROM.
-- Самый продаваемый товар: 1) по количеству; 2) по цене
SELECT name as "Best Selling"
FROM products P JOIN ( SELECT product_id, SUM(product_quantity) AS SQ
     FROM orders
     GROUP BY product_id
     ORDER BY SQ DESC
     LIMIT 1) AS OD ON OD.product_id = P.product_id
UNION
SELECT name as "Best Selling"
FROM products P JOIN ( SELECT product_id,
     SUM(order_price) AS SR
     FROM orders
     GROUP BY product_id
     ORDER BY SR DESC
     LIMIT 1) AS OD ON OD.product_id = P.product_id;