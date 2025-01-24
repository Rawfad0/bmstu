-- 9. Триггер AFTER
-- Таблица аудита
CREATE TABLE IF NOT EXISTS products_audit
(
    product_id int,
    product_name text,
    operation text,
    modified_date timestamp
);

-- Функция для триггера
CREATE OR REPLACE FUNCTION insert_product_trig_func ()
RETURNS TRIGGER
AS $$
BEGIN
    RAISE NOTICE 'NEW % INSERTED IN TABLE PRODUCT', new;
    INSERT INTO products_audit(
        product_id,
        product_name,
        operation,
        modified_date
    )
    VALUES (new.product_id, new.name, 'INSERT', now());
    RETURN new;
END
$$ LANGUAGE PLPGSQL;

-- Сам триггер
CREATE OR REPLACE TRIGGER insert_product_trigger
AFTER INSERT ON products
FOR EACH ROW
EXECUTE FUNCTION insert_product_trig_func();

INSERT INTO products
VALUES (1001, 1, 'ProductName', 'Descr', 4.34, 100);

SELECT *
FROM products
WHERE product_id = 1001;

SELECT *
FROM products_audit;

DELETE FROM products
WHERE product_id = 1001;

DELETE FROM products_audit
WHERE product_id = 1001;
