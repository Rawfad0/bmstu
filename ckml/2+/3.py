d = dict()
input_str = input()
while input_str != "стоп":
    category, subcategory, product, price = input_str.split(" - ")
    price = int(price)
    if d.get(category) is None:
        d[category] = {subcategory: {product: price, }, }
    elif d[category].get(subcategory) is None:
        d[category][subcategory] = {product: price, }
    else:
        d[category][subcategory][product] = price
    input_str = input()
for category, subcategories in sorted(d.items()):
    print(f"{category}:")
    for subcategory, products in sorted(subcategories.items()):
        print(f"  {subcategory}:")
        for product, price in sorted(products.items(), key=lambda item: item[1]):
            print(f"    - {product} ({price} руб.)")
