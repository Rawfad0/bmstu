from csv import writer, reader
from random import randint


with (open("/Users/Shared/orders.csv", 'r', newline='') as src,
      open(f"/Users/Shared/orders2.csv", "w", newline="") as dst):
    orders = []
    csv_reader = reader(src, delimiter=',')
    for i, row in enumerate(csv_reader):
        store_id = randint(1, 1000)
        row.insert(3, str(store_id))
        orders.append(row)

    csv_writer = writer(dst)
    csv_writer.writerows(orders)
