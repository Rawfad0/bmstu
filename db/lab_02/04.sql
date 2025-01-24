-- 4. Инструкция SELECT, использующая предикат IN с вложенным подзапросом.
-- Получить список магазинов, продающих товары, в описании которых есть '%Android 9.0%память 512 Гб%'
SELECT store_id, name
FROM stores
WHERE store_id IN (SELECT store_id
    FROM stores_products
    WHERE product_id IN (SELECT product_id
        FROM products
        WHERE description LIKE '%Android 9.0%память 512 Гб%'
    )
);