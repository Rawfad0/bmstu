-- select function_info();

-- select COUNT(PS) from (select * from products where average_rating > 4.0) as PS;
-- select * from orders where product_id = 753;
--
-- select * from stores_products sp where sp.store_id = 35;
-- select * from orders where product_id = 40;
-- 9

--select sp_id, store_id, product_id
--from stores_products
--where store_id = 261;
--
--select user_id, last_name, first_name
--from users u join orders o on u.user_id = o.user_id
--	join stores_products sp on o.product_id = sp.product_id


--select u.user_id, u.last_name, u.first_name
--from users u join (
--    select *
--    from orders
--    where store_id = (
--        select store_id
--        from stores
--        where average_rating = (
--            select MIN(average_rating)
--            from stores
--        )
--        limit 1
--    )
--) o on u.user_id = o.user_id;


--select u.user_id, u.last_name, u.first_name
--from users u join (
--    select *
--    from orders
--    where store_id = 777
--) o on u.user_id = o.user_id;


--
--select u.user_id, u.last_name, u.first_name,
--from users u
--where 2 > ALL (
--    select s.average_rating
--    from users u2 join orders o on u2.user_id = o.user_id join stores s on o.store_id = s.store_id
--    where o.user_id = u.user_id
--);


--AND COUNT(
--    select *
--    from users u join orders o on u.user_id = o.user_id
--) != 0;

--select u.user_id, u.last_name, u.first_name
--from users u
--where 1.1 > ALL (
--    select s.average_rating
--    from orders o join stores s on o.store_id = s.store_id
--    where o.user_id = u.user_id
--);

--select s.store_id, s.name, count(s.store_id) as product_count
--from stores as s left join stores_products as sp on s.store_id = sp.store_id
--group by s.store_id

--select store_id
--from stores
--where average_rating < 1.1;



-- Пользователи, которые закупаются в магазинах, в которых средняя оценка меньше двух

select u.user_id, u.last_name, u.first_name
from users u join (
    select *
    from orders o join (
        select *
        from stores
        where average_rating < 2
    ) s on s.store_id = o.store_id
) o on u.user_id = o.user_id;

--select order_id, u.user_id, s.store_id, s.average_rating
--from orders u join stores s on u.store_id = s.store_id
--where user_id = 8;
