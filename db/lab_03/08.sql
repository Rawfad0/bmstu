-- 8. Хранимая процедура доступа к метаданным
CREATE OR REPLACE PROCEDURE print_tables ()
AS $$
DECLARE
    r record;
BEGIN
    FOR r IN
        SELECT *
        FROM information_schema.tables
        WHERE table_catalog = 'postgres' AND table_schema = 'postgres'
        LOOP
            RAISE NOTICE '%', r;
        END LOOP;
END
$$ LANGUAGE PLPGSQL;

CREATE OR REPLACE PROCEDURE print_columns (name VARCHAR)
AS $$
DECLARE
    r record;
BEGIN
    FOR r IN
        SELECT column_name, data_type
        FROM information_schema.columns
        WHERE table_catalog = 'postgres' AND table_name = name
        LOOP
            RAISE NOTICE '%', r;
        END LOOP;
END
$$ LANGUAGE PLPGSQL;

CALL print_tables();
CALL print_columns('users');