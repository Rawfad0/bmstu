-- 6. Инструкция SELECT, использующая предикат сравнения с квантором.
-- Получить список продуктов, рейтинг которых выше, чем у любого продукта
-- с "Samsung" в названии и "память 512 Гб" в описании
SELECT product_id, name, average_rating
FROM products
WHERE average_rating > ALL (SELECT average_rating
    FROM products
    WHERE name LIKE '%Samsung%' AND description LIKE '%память 512 Гб%');