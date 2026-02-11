import struct

print(hex(20040122))
path = input('Введите путь: ')
with open(path, 'r') as f1, open(path+'.bin', 'wb') as f2:
    while (line := f1.readline().rstrip('\n')) != '':
        line = line.split(',')
        line[3] = int(line[3])
        line[:3] = [i.encode('windows-1251') for i in line[:3]]
        print(line)
        packed_line = struct.pack('16s16s8sL', *line)
        print(packed_line)
        f2.write(packed_line)
