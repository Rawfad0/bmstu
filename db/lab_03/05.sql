-- 5. Хранимая процедура без параметров или с параметрами
-- Применить скидку ко всем товарам конкретного продавца
CREATE OR REPLACE PROCEDURE store_discount(id integer, discount float)
AS $$
BEGIN
    UPDATE stores_products
    SET price = price * (1 - discount)
    WHERE store_id = id;
END
$$ LANGUAGE PLPGSQL;
-- Увеличить цену всех товаров конкретного продавца
CREATE OR REPLACE PROCEDURE store_up_prices(id integer, up float)
AS $$
BEGIN
    UPDATE stores_products
    SET price = price * up
    WHERE store_id = id;
END
$$ LANGUAGE PLPGSQL;


select *
from stores_products sp
where store_id = 35;

call store_discount(35, 0.5);

select *
from stores_products sp
where store_id = 35;

call store_up_prices(35, 2);

select *
from stores_products sp
where store_id = 35;
