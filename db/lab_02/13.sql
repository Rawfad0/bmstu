-- 13. Инструкция SELECT, использующая вложенные подзапросы с уровнем вложенности 3.
-- Наименование самого продающегося товара
SELECT name as "Best Selling"
FROM products
WHERE product_id = (
    SELECT product_id
    FROM orders
    GROUP BY product_id
    HAVING SUM(product_quantity) = (SELECT MAX(SQ)
        FROM ( SELECT SUM(product_quantity) as SQ
            FROM orders
            GROUP BY product_id
            ) AS OD
        )
    ORDER BY product_id
    LIMIT 1
    )
