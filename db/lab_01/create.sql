create table if not exists users
(
    user_id serial,
    last_name varchar(100),
    first_name varchar(100),
    phone_number varchar(15),
    email varchar(50),
    birth_date date,
    reg_date date
);

create table if not exists products
(
    product_id serial,
    category varchar(100),
    name text,
    description text,
    average_rating float,
    review_number float
);

create table if not exists stores
(
    store_id serial,
    name text,
    ogrnip varchar(15),
    ip text,
    average_rating float,
    review_number float
);

create table if not exists stores_products
(
    sp_id serial,
    store_id int,
    product_id int,
    price int,
    delivery_days int,
    product_quantity int
);

create table if not exists orders
(
    order_id serial,
    user_id int,
    product_id int,
    store_id int,
    delivery_days int,
    product_quantity int,
    order_price int
);
