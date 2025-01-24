alter table if exists users
    add constraint pk_users primary key (user_id);

alter table if exists users
    add constraint reg_date_after_birth_day check (reg_date > birth_date);

alter table if exists products
    add constraint pk_products primary key (product_id);

alter table if exists products
    alter column category set not null,
    alter column name set not null,
    alter column average_rating set not null,
    alter column review_number set not null;

alter table if exists products
    add constraint uniq_orgnip unique (name);

alter table if exists products
    add constraint rating_higher_equal_than_1 check(average_rating >= 1),
    add constraint rating_lower_equal_than_5 check(average_rating <= 5),
    add constraint positive_review_number check(review_number >= 0);

alter table if exists stores
    add constraint pk_stores primary key (store_id);

alter table if exists stores
    alter column name set not null,
    alter column ogrnip set not null,
    alter column ip set not null,
    alter column average_rating set not null,
    alter column review_number set not null;

alter table if exists stores
    add constraint uniq_ogrnip unique (ogrnip);

alter table if exists stores
    add constraint rating_higher_equal_than_1 check(average_rating >= 1),
    add constraint rating_lower_equal_than_5 check(average_rating <= 5),
    add constraint not_negative_review_number check(review_number >= 0);

alter table if exists stores_products
    add constraint pk_stores_products primary key (sp_id);

alter table if exists stores_products
    add constraint positive_price check(price >= 0),
    add constraint positive_delivery_days check(delivery_days >= 0),
    add constraint not_negative_product_quantity check(product_quantity >= 0);

alter table if exists orders
    add constraint pk_orders primary key (order_id);

alter table if exists orders
    add constraint positive_price check(order_price >= 0),
    add constraint positive_delivery_days check(delivery_days >= 0),
    add constraint not_negative_product_quantity check(product_quantity >= 0);
