-- 14. Инструкция SELECT, консолидирующая данные с помощью предложения GROUP BY, но без предложения HAVING.
-- Для каждого заказанного продукта с оценкой выше 4х получить его
-- наименование, количество отзывов, среднюю цену, минимальную цену
SELECT P.product_id, P.name, P.review_number,
     AVG(O.order_price) AS AvgPrice,
     MIN(O.order_price) AS MinPrice
FROM products P LEFT OUTER JOIN orders O ON O.product_id = P.product_id
WHERE average_rating > 4.0
GROUP BY P.product_id, P.name, P.review_number;