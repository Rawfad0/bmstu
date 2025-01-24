--1. Инструкция SELECT, использующая предикат сравнения.
--Вывести товары, где количество отзывов больше 250 и средний рейтинг больше 4.5
SELECT DISTINCT name, average_rating, review_number
FROM products
WHERE review_number > 250
    AND average_rating > 4.5
ORDER BY name, average_rating, review_number;

--2. Инструкция SELECT, использующая предикат BETWEEN.
--Получить список пользователей, зарегистрировавшихся между '2020-01-01' и '2020-03-31'
SELECT DISTINCT id, reg_date
FROM users
WHERE reg_date BETWEEN '2020-01-01' AND '2020-03-31';

-- 3. Инструкция SELECT, использующая предикат LIKE.
-- Получить список товаров в описании которых присутствует слово 'Android 9.0'
SELECT DISTINCT id, name
FROM products
WHERE description LIKE '%Android 6.0%память 8 Гб%'
ORDER BY id;

-- 4. Инструкция SELECT, использующая предикат IN с вложенным подзапросом.
-- Получить список магазинов, продающих товары, в описании которых есть '%Android 9.0%память 512 Гб%'
SELECT id, name
FROM stores
WHERE id IN (SELECT store_id
    FROM stores_products
    WHERE product_id IN (SELECT id
        FROM products
        WHERE description LIKE '%Android 9.0%память 512 Гб%'
    )
);

---- 5. Инструкция SELECT, использующая предикат EXISTS с вложенным подзапросом.
SELECT id, name
FROM stores
WHERE EXISTS (SELECT store_id
    FROM stores_products
    WHERE product_id IN (SELECT id
        FROM products
        WHERE description LIKE '%Android 9.0%память 512 Гб%'
    )
);
--SELECT ProductID, ProductName
--FROM Products
--WHERE EXISTS (SELECT Products.ProductID
-- FROM Products LEFT OUTER JOIN [Order Details]
-- ON Products.ProductID = [Order Details].ProductID
-- WHERE [Order Details].ProductID IS NULL
--)


