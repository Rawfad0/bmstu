-- 10. Триггер INSTEAD OF


-- Создание представлений
CREATE VIEW products_v AS
SELECT *
FROM products;

CREATE VIEW stores_products_v AS
SELECT *
FROM stores_products;

-- Функция для триггера
-- ОбНУЛЛить соответствующие значения id в дочерней таблице без удаления товара из родительской
CREATE OR REPLACE FUNCTION remove_product_trig_func ()
RETURNS TRIGGER
AS $$
BEGIN
--    RAISE NOTICE '%', old;
    UPDATE stores_products_v
    SET product_id = NULL
    WHERE stores_products_v.product_id = old.product_id;
    RETURN new;
END
$$ LANGUAGE PLPGSQL;

-- Сам триггер
CREATE OR REPLACE TRIGGER delete_product_trigger
INSTEAD OF DELETE ON products_v
FOR EACH ROW EXECUTE FUNCTION remove_product_trig_func();

SELECT *
FROM stores_products_v
WHERE product_id = 135;

DELETE FROM products_v
WHERE product_id = 135;

SELECT *
FROM stores_products_v
WHERE product_id = 135;

SELECT *
FROM stores_products_v
WHERE sp_id = 254 OR sp_id=609;

DROP VIEW products_v;

DROP VIEW stores_products_v;

TRUNCATE stores_products;

COPY stores_products(
    sp_id,
    store_id,
    product_id,
    price,
    delivery_days,
    product_quantity
) FROM '/Users/Shared/stores_products.csv' delimiter ',' csv;

TRUNCATE products;


COPY products(
    product_id,
    category,
    name,
    description,
    average_rating,
    review_number
) FROM '/Users/Shared/products.csv' delimiter ',' csv;

