-- 9. Инструкция SELECT, использующая простое выражение CASE.
-- Получить список пользователей и как давно зарегистрирован (этот год, прошлый год или сколько лет назад)
SELECT user_id, last_name, first_name,
    CASE date_part('year', reg_date)
        WHEN date_part('year', now()) THEN 'This year'
        WHEN date_part('year', now()) - 1 THEN 'Last year'
        ELSE date_part('year', age(reg_date)) || ' years ago'
    END AS "When reg"
FROM users;
