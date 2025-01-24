-- 4. Рекурсивная функция или функция с рекурсивным ОТВ

CREATE OR REPLACE FUNCTION get_users_ref_lvl ()
RETURNS TABLE (user_id int, last_name varchar(100), first_name varchar(100), ref int, lvl int)
AS $$
BEGIN
    RETURN QUERY
    WITH recursive UserRefs (user_id, last_name, first_name, ref, lvl) AS
    (
        SELECT u.user_id, u.last_name, u.first_name, u.ref, 0 AS lvl
        FROM users2 u
        WHERE u.ref is NULL

        UNION

        SELECT u.user_id, u.last_name, u.first_name, u.ref, r.lvl + 1
        FROM users2 AS u INNER JOIN UserRefs AS r ON u.ref = r.user_id
    )
    SELECT * FROM UserRefs;
END
$$ LANGUAGE PLPGSQL;

SELECT *
FROM get_users_ref_lvl (388, 0);
