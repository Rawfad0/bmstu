from csv import writer, reader
from random import randint


with (open("/Users/Shared/users.csv", 'r', newline='') as src,
      open(f"/Users/Shared/users2.csv", "w", newline="") as dst):
    users = []
    csv_reader = reader(src, delimiter=',')
    for i, row in enumerate(csv_reader):
        ref = randint(0, i)
        if ref == 0:
            ref = ''
        row.append(str(ref))
        users.append(row)

    print(ref)


    csv_writer = writer(dst)
    csv_writer.writerows(users)
