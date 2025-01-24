-- 4. Хранимая процедура CLR
-- Применить скидку ко всем товарам конкретного продавца
CREATE OR REPLACE PROCEDURE store_discount_py(id integer, discount float)
AS $$
    plpy.execute(f"UPDATE stores_products SET price = price * (1 - {discount}) WHERE store_id = {id};")
$$ LANGUAGE plpython3u;

-- Увеличить цену всех товаров конкретного продавца
CREATE OR REPLACE PROCEDURE store_up_prices_py(id integer, up float)
AS $$
    plpy.execute(f"UPDATE stores_products SET price = price * {up} WHERE store_id = {id};")
$$ LANGUAGE plpython3u;


select *
from stores_products sp
where store_id = 35;

call store_discount_py(35, 0.5);

select *
from stores_products sp
where store_id = 35;

call store_up_prices_py(35, 2);

select *
from stores_products sp
where store_id = 35;