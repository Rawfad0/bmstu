s1 = input().lower()
s2 = list(input().lower())
for ch in s1:
    if not s2:
        s2.append('')
        break
    if ch in s2:
        s2.remove(ch)
print(f'Слова{["", " не"][bool(s2)]} являются анаграммами.')
