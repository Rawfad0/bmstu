-- 23. Инструкция SELECT, использующая рекурсивное обобщенное табличное выражение.
-- Level = log2(delivery_days)
--WITH recursive OrderDeliveryDays (order_id, user_id, product_id, product_quantity, delivery_days, order_price, Level) AS
--(
--    SELECT o.order_id, o.user_id, o.product_id, o.product_quantity, o.delivery_days, o.order_price, 0 AS Level
--    FROM orders AS o
--    WHERE delivery_days = 1
--
--    UNION
--
--    SELECT o.order_id, o.user_id, o.product_id, o.product_quantity, o.delivery_days, o.order_price, Level + 1
--    FROM orders AS o INNER JOIN OrderDeliveryDays AS d ON o.delivery_days = 2*d.delivery_days
--)
--SELECT * FROM OrderDeliveryDays;


WITH recursive UserRefs (user_id, last_name, first_name, ref, Level) AS
(
    SELECT user_id, last_name, first_name, ref, 0 AS Level
    FROM users2
    WHERE ref is NULL

    UNION

    SELECT U.user_id, U.last_name, U.first_name, U.ref, Level + 1
    FROM users2 AS U INNER JOIN UserRefs AS R ON U.ref = R.user_id
)
SELECT * FROM UserRefs;
