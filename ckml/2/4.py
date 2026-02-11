d = dict()
for word in input().split(', '):
    d[word] = 1 if d.get(word) is None else d[word]+1
for k, v in sorted(d.items(), key=lambda item: item[1], reverse=True)[:3]:
    print(k+':', v)
