-- 3. Многооператорная табличная функция
-- Функция возвращает по 10 товаров из каждого условия (количество отзывов и средняя оценка)
CREATE OR REPLACE FUNCTION prods ()
RETURNS TABLE (
    product_id integer,
    name text,
    average_rating float,
    review_number float
)
AS $$
BEGIN
    RETURN QUERY
    SELECT p.product_id, p.name, p.average_rating, p.review_number
    FROM products p
    WHERE p.review_number > 280 AND p.average_rating > 4.0
    LIMIT 10;

    RETURN QUERY
    SELECT p.product_id, p.name, p.average_rating, p.review_number
    FROM products p
    WHERE p.average_rating > 4.8 AND p.review_number > 200
    LIMIT 10;
END
$$ LANGUAGE PLPGSQL;

SELECT *
FROM prods();