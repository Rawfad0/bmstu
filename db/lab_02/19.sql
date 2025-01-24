-- 19. Инструкция UPDATE со скалярным подзапросом в предложении SET.
-- Выставить цену у на товар 40 у продавца 35 на среднюю из заказов
-- Было 62909 стало 48504
UPDATE stores_products
SET price = ( SELECT AVG(order_price / product_quantity)
    FROM orders
    WHERE product_id = 40)
WHERE store_id = 35 AND product_id = 40