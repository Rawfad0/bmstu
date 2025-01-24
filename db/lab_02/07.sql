-- 7. Инструкция SELECT, использующая агрегатные функции в выражениях столбцов.
-- Получить среднюю стоимость всех товаров c 'Samsung' в названии
SELECT AVG(price) as "Average product price"
FROM products JOIN stores_products ON products.product_id = stores_products.product_id
WHERE name LIKE '%Samsung%';

-- Ближе к примеру из задания:
-- Получить среднюю стоимость всех групп товаров по продавцам (двумя способами)
-- т.е. стоимость*"количество товара на складе" / "количество всех именований товаров у всех продавцов"
SELECT AVG(TotalPrice) AS "Actual AVG",
    SUM(TotalPrice) / COUNT(product_id) AS "Calc AVG"
FROM (SELECT products.product_id, SUM(price*product_quantity) AS TotalPrice
    FROM products JOIN stores_products ON products.product_id = stores_products.product_id
    GROUP BY products.product_id
) AS TotOrders;
