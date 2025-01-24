-- 1. Найти все страны с самыми новыми спутниками
select country
from satellite 
where prod_date = (
	select max(prod_date)
	from satellite
);

-- 2. Найти спутник, который отправлен в этом году позже всех
-- select date_part('year', (select current_timestamp));
-- select name
-- from sattelite s join flight f on s.s_id = f.s_id
-- where 
-- select *
-- from flight
-- where 

select f.s_id, name
from flight f join satellite s on f.s_id = s.s_id
where launch_date = (
	select max(launch_date)
	from flight
	where type=1 and date_part('year', launch_date) = date_part('year', (select current_timestamp))
)
order by launch_time
limit 1;

-- 3. Найти все аппараты, вернувшиеся на землю не позднее 10 дней с 2024-01-01
select name
from satellite s join flight f on s.s_id = f.s_id
where type = 0 and launch_date <= '2024-01-11';