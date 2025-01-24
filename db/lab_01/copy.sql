copy users(
    user_id,
    last_name,
    first_name,
    phone_number,
    email,
    birth_date,
    reg_date
) from '/Users/Shared/users.csv' delimiter ',' csv;

copy products(
    product_id,
    category,
    name,
    description,
    average_rating,
    review_number
) from '/Users/Shared/products.csv' delimiter ',' csv;

copy stores
(
    store_id,
    name,
    ogrnip,
    ip,
    average_rating,
    review_number
) from '/Users/Shared/stores.csv' delimiter ',' csv;

copy stores_products(
    sp_id,
    store_id,
    product_id,
    price,
    delivery_days,
    product_quantity
) from '/Users/Shared/stores_products.csv' delimiter ',' csv;

copy orders(
    order_id,
    user_id,
    product_id,
    store_id,
    delivery_days,
    product_quantity,
    order_price
) from '/Users/Shared/orders2.csv' delimiter ',' csv;
