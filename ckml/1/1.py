r = 0
while (s := input()) != 'end':
    x = int(s)
    if x % 2 == 0:
        r += x
print(r)
