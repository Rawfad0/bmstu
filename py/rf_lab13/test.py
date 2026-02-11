import struct as struct

# line = 'Подкорытов,Александр,22У1502,2004-01-22'
# packed_line = s.pack('64s', line.encode('UTF-8'))
# print(len(line), line)
# print(len(packed_line), packed_line)
# print(s.calcsize('48s'))
#
# with open('test.txt', 'wb') as f:
#     f.write(packed_line)
line0 = ['Аверьянов'.encode('windows-1251'), 'Дмитрий'.encode('windows-1251'), '22У115'.encode('windows-1251'), 20040122]
# i = s.pack('10s10si', *line, 64)

# i = s.pack('iiii', 1, 12, 256, 4096)
# print(s.calcsize('i'))
# print(i)

# print(256*16)
# print(bytearray([i for i in range(100)]))
# for i in range(100):
#     print(bytearray([i]))

# j = s.pack('i', )
# print(j)

with open('test2', 'wb') as f:
    f.write(struct.pack('16s16s8sL', *line0))


