d = dict()
input_str = input()
while input_str != "стоп":
    product, category, price = input_str.split(" - ")
    price = int(price)
    if d.get(category) is None:
        d[category] = {product: price, }
    else:
        d[category][product] = price
    input_str = input()
for category, products in sorted(d.items()):
    print(f"{category}:")
    for product, price in sorted(products.items(), key=lambda item: item[1]):
        print(f"  - {product} ({price} руб.)")
