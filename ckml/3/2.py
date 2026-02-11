def lists_sum(*lists, unique=False):
    al = []
    for l in lists:
        al.extend(l)

    if unique:
        unique_list = set(al)
        s = sum(unique_list)
    else:
        s = sum(al)
    return s


line = input()
while line:
    exec(line)
    line = input()
