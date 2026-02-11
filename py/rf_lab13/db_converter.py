path = input('Введите путь: ')
with open(path, 'r', encoding='UTF-8') as f:
    lines = [i.split('\t') for i in f.readlines()]
print(*lines, sep='\n')
with open(f'{path}', 'w') as f:
    for line in lines:
        f.write(','.join(line))
