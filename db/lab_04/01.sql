-- 1. Определяемая пользователем скалярная функция CLR
-- Средняя стоимость товара в заказе
CREATE OR REPLACE FUNCTION avg_order_product_price(quantity integer, total integer)
RETURNS float
AS $$
    return total / quantity
$$ LANGUAGE plpython3u;

SELECT order_id, product_quantity, order_price, avg_order_product_price(product_quantity, order_price) AS avg_price
FROM orders
LIMIT 30;