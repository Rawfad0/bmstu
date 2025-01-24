-- 3. Инструкция SELECT, использующая предикат LIKE.
-- Получить список товаров в описании которых присутствует слово 'Android 9.0'
SELECT DISTINCT product_id, name
FROM products
WHERE description LIKE '%Android 6.0%память 8 Гб%'
ORDER BY product_id;