-- 1. Из таблиц базы данных, созданной в первой лабораторной работе, извлечь данные в JSON (Postgres).
copy (select row_to_json(users) from users) to '/Users/Shared/users.json';
copy (select row_to_json(products) from products) to '/Users/Shared/products.json';
copy (select row_to_json(stores) from stores) to '/Users/Shared/stores.json';
copy (select row_to_json(orders) from orders) to '/Users/Shared/orders.json';
copy (select row_to_json(stores_products) from stores_products) to '/Users/Shared/stores_products.json';