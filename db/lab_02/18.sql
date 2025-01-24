-- 18. Простая инструкция UPDATE.
-- Повысить цены у продавца 35 в два раза
UPDATE stores_products
SET price = price * 2
WHERE store_id = 35