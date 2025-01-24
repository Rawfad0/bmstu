--1. Инструкция SELECT, использующая предикат сравнения.
--Вывести товары, где количество отзывов больше 250 и средний рейтинг больше 4.5
SELECT DISTINCT name, average_rating, review_number
FROM products
WHERE review_number > 250
    AND average_rating > 4.5
ORDER BY name, average_rating, review_number;
