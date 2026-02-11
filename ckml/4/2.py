from statistics import multimode


def get_popular_name_from_file(filename):  # Должна вернуть: Владимир, Джо
    with open(filename, 'r') as f:
        names = [line.split()[0] for line in f.read().splitlines()]
    return ', '.join(sorted(multimode(names)))


print(get_popular_name_from_file("2.txt"))
