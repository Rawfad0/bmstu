create database rk3;

-- s_id - ID
-- name - Название
-- prod_date - Дата производства
-- country - Страна
create table if not exists satellite
(
	s_id int,
	name text,
	prod_date date,
	country text
);

-- s_id - ID
-- launch_date - дата запуска
-- laucnh_time - время запуска
-- day - день недели
-- type - тип (0 - прилет, 1 - вылет)
create table if not exists flight
(
	s_id int,
	launch_date date,
	launch_time time,
	day text,
	type int
);

insert into satellite(s_id, name, prod_date, country) values
(1, 'SIT-2086', '2050-01-01', 'Россия'),
(2, 'SIT-2087', '2050-01-01', 'Россия'),
(3, 'SIT-2088', '2050-01-01', 'Россия'),
(4, 'SIT-2089', '2050-01-01', 'Россия'),
(5, 'Шицзян 16-02', '2049-12-01', 'Китай');

insert into flight(s_id, launch_date, launch_time, day, type) values
(1, '2050-05-11', '9:00', 'Среда', 1),
(1, '2051-06-14', '23:05', 'Среда', 0),
(1, '2051-10-10', '23:50', 'Вторник', 1),
(2, '2050-05-11', '15:15', 'Среда', 1),
(1, '2052-01-01', '12:15', 'Понедельник', 0),
(3, '2053-05-11', '9:00', 'Среда', 1),
(3, '2054-06-14', '23:05', 'Среда', 0),
(4, '2055-10-10', '23:50', 'Вторник', 1),
(4, '2056-05-11', '15:15', 'Среда', 0),
(2, '2057-01-01', '12:15', 'Понедельник', 0);
