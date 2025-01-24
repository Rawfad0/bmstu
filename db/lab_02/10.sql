-- 10. Инструкция SELECT, использующая поисковое выражение CASE
-- <10k     - Inexpensive
-- 10k-50k  - Fair
-- 50k-80k  - Expensive
-- 80k+     - Very Expensive
SELECT name,
    CASE
        WHEN price < 10000 THEN 'Inexpensive'
        WHEN price < 50000 THEN 'Fair'
        WHEN price < 80000 THEN 'Expensive'
        ELSE 'Very Expensive'
    END AS Price
FROM products JOIN stores_products ON products.product_id = stores_products.product_id;