-- Query plans to SQL
-- 1:
-- В моей таблице satellite_id это s_id
select s_id, count(*) as flight_count
from flights
group by s_id
having count(*) > 5;


-- 2: Найти все пары спутников из одной страны  
-- В моей таблице id это s_id
select *
from satellite s1 join satellite s2 on s1.country = s2.country
where s1.s_id<s2.s_id;
