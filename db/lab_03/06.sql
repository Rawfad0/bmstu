-- 6. Рекурсивная хранимая процедура или хранимая процедура с рекурсивным ОТВ
-- Вывести всех, кто является рефералом уровня LVL пользователя ID
CREATE OR REPLACE PROCEDURE print_users_ref_lvl (
    id integer,
    lvl integer,
    cur_lvl integer DEFAULT 0
)
AS $$
DECLARE
    elem INT;
BEGIN
    IF cur_lvl = lvl THEN
        RAISE NOTICE 'FOUND: USER_ID=%, LVL=%', id, cur_lvl;
    END IF;

    IF cur_lvl < lvl THEN
    FOR elem IN
        SELECT *
        FROM users2 as u
        WHERE ref = id
        LOOP
            CALL print_users_ref_lvl(elem, lvl, cur_lvl + 1);
        END LOOP;
    END IF;

END
$$ LANGUAGE PLPGSQL;

CALL print_users_ref_lvl(272, 2);
CALL print_users_ref_lvl(1, 3);
