-- Задание №1

-- create database RK2;

CREATE TABLE IF NOT EXISTS club
(
	id int primary key, 
	name varchar(20),
	est_year int,
	descr varchar(200)
);

CREATE TABLE IF NOT EXISTS visitor
(
	id int primary key,
	name varchar(50),
	birth_year int,
	address varchar(100),
	email varchar(30)
);

CREATE TABLE IF NOT EXISTS head
(
	id int primary key,
	name varchar(50),
	birth_year int,
	expirience int,
	phone_number varchar(15)
);

CREATE TABLE IF NOT EXISTS club_visitor
(
	club_id int,
	visitor_id int
);

INSERT INTO club
(
	id, 
	name,
	est_year,
	descr
) VALUES
(1, 'Club Name 1', 1, 'description abc awdwadw 1.'),
(2, 'Club Name 2', 2, 'description cbd kad 2.'),
(3, 'Club Name 3', 3, 'description eaawdda 3.'),
(4, 'Club Name 4', 4, 'description adwda 4.'),
(5, 'Club Name 5', 5, 'description kad awdkad 5.'),
(6, 'Club Name 6', 6, 'description awdadkw abc 6.'),
(7, 'Club Name 7', 7, 'description awdkaw zbc 7.'),
(8, 'Club Name 8', 8, 'description adwakw 8.'),
(9, 'Club Name 9', 9, 'description adwkkd abc 9.'),
(10, 'Club Name 10', 10, 'description awm wdam kad 10.');

INSERT INTO visitor
(
	id,
	name,
	birth_year,
	address,
	email
) VALUES
(1, 'Visitor Name 1', 1901, 'Address 1', 'email1@email.com'),
(2, 'Visitor Name 2', 1902, 'Address 2', 'email2@email.com'),
(3, 'Visitor Name 3', 1903, 'Address 3', 'email3@email.com'),
(4, 'Visitor Name 4', 1904, 'Address 4', 'email4@email.com'),
(5, 'Visitor Name 5', 1905, 'Address 5', 'email5@email.com'),
(6, 'Visitor Name 6', 1906, 'Address 6', 'email6@email.com'),
(7, 'Visitor Name 7', 1907, 'Address 7', 'email7@email.com'),
(8, 'Visitor Name 8', 1908, 'Address 8', 'email8@email.com'),
(9, 'Visitor Name 9', 1909, 'Address 9', 'email9@email.com'),
(10, 'Visitor Name 10', 1910, 'Address 10', 'email10@email.com');

INSERT INTO head
(
	id,
	name,
	birth_year,
	expirience,
	phone_number
) VALUES 
(1, 'Head Name 1', 1901, 1, '8900000001'),
(2, 'Head Name 2', 1902, 2, '8900000002'),
(3, 'Head Name 3', 1903, 3, '8900000003'),
(4, 'Head Name 4', 1904, 4, '8900000004'),
(5, 'Head Name 5', 1905, 5, '8900000005'),
(6, 'Head Name 6', 1906, 6, '8900000006'),
(7, 'Head Name 7', 1907, 7, '8900000007'),
(8, 'Head Name 8', 1908, 8, '8900000008'),
(9, 'Head Name 9', 1909, 9, '8900000009'),
(10, 'Head Name 10', 1910, 10, '89000000010');

INSERT INTO club_visitor
(
	club_id,
	visitor_id
) VALUES
(10, 8),
(10, 7),
(2, 1),
(6, 8),
(2, 6),
(4, 1),
(4, 4),
(10, 8),
(9, 5),
(8, 5),
(6, 3),
(7, 2),
(10, 9),
(3, 10),
(9, 8),
(8, 3),
(5, 4),
(2, 10),
(9, 6),
(5, 10);

-- Задание №2
-- 1. Получить список кружков, в описании которых есть последовательность символов 'abc'
SELECT id, name
FROM club 
WHERE descr LIKE '%abc%'
ORDER BY id;

-- 2. Получить список кружков, чей год основания больше чем у всех кружков, в описании которых есть последовательность символов 'abc'
SELECT id, name
FROM club
WHERE club.est_year > ALL (SELECT est_year
	FROM club
	WHERE descr LIKE '%abc%'
);

-- 3. ...



-- Задание №3
CREATE OR REPLACE FUNCTION 
function_info()
RETURNS integer AS $$
	DECLARE 
	count_ integer;
	row_ RECORD;
	cur_table CURSOR 
		FOR SELECT p.oid AS id, proargnames, proname AS namef, nspname, prokind 
		FROM pg_proc p INNER JOIN pg_catalog.pg_namespace s ON s."oid" = p.pronamespace 
		WHERE s.nspname NOT IN ('pg_catalog', 'pg_toast', 'information_schema')
			AND prokind = 'f'
			AND oidvectortypes(proargtypes) != ''
		ORDER BY s.nspname;
	BEGIN 
		OPEN cur_table;
		LOOP
			FETCH cur_table INTO row_;
			EXIT WHEN NOT FOUND;
			RAISE NOTICE 'FNAME: %, ARGS: %', row_.namef, row_.proargnames;
			count_ = count_ + 1;
		END LOOP;
		RETURN count_;
	END;
$$ LANGUAGE PLPGSQL;
