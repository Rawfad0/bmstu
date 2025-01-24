-- 6. Определяемый пользователем тип данных CLR.
CREATE TYPE name AS (
    first_name text,
    last_name text
);

CREATE OR REPLACE FUNCTION get_user_name(id integer)
RETURNS name
AS $$
    user = plpy.execute(f"SELECT first_name, last_name FROM users WHERE user_id = {id};")
    return f"{user[0]['first_name']} {user[0]['last_name']}"
$$ LANGUAGE plpython3u;

SELECT * FROM get_user_name(3);

SELECT user_id, get_user_name(user_id) as name
FROM users;