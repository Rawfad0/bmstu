r = sorted(set(input().split()).intersection(set(input().split())))
if r:
    print("Общие элементы:", *r)
else:
    print("Общих элементов нет")
