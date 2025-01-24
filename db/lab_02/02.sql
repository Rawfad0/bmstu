--2. Инструкция SELECT, использующая предикат BETWEEN.
--Получить список пользователей, зарегистрировавшихся между '2020-01-01' и '2020-03-31'
SELECT DISTINCT user_id, reg_date
FROM users
WHERE reg_date '2020-01-01' AND '2020-03-31';
