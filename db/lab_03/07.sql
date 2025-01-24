-- 7. Хранимая процедура с курсором
CREATE OR REPLACE PROCEDURE print_n_products(n integer)
AS $$
declare
    avg_rating NUMERIC(10, 3);
    product RECORD;
    curs CURSOR FOR
        SELECT *
        FROM products
        LIMIT n;
begin
    OPEN curs;
    LOOP
        FETCH curs INTO product;
        EXIT WHEN NOT FOUND;
        avg_rating = product.average_rating;
        RAISE NOTICE 'id=%, avg_rating=%, name=%', product.product_id, avg_rating, product.name;
    END LOOP;
    CLOSE curs;
end;
$$ LANGUAGE PLPGSQL;

CALL print_n_products(20);