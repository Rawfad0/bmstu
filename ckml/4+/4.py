# def count_word_occurrences(filename, word):
#     c = 0
#     buf = ""
#     buf_len = 0
#     with open(filename, 'r') as f:
#         ch = f.read(1)
#         while ch:
#             if buf + ch == word[:buf_len + 1]:
#                 if buf_len + 1 == len(word):
#                     buf = ""
#                     buf_len = 0
#                     c += 1
#                 else:
#                     buf += ch
#                     buf_len += 1
#             ch = f.read(1)
#     return f"Слово '{word}' встречается в файле '{filename}' {c} раз."


# def count_word_occurrences(filename, word):
#     c = 0
#     with open(filename, 'r') as f:
#         line = f.readline()
#         while line:
#             l = line.split()
#             for w in l:
#                 if w == word:
#                     c += 1
#             line = f.readline()
#     return f"Слово '{word}' встречается в файле '{filename}' {c} раз."

import re


def count_word_occurrences(filename, word):
    c = 0
    with open(filename, 'r') as f:
        for line in f:
            words = re.split(r'\W', line.lower())
            for w in words:
                if w == word:
                    c += 1
    return f"Слово '{word}' встречается в файле '{filename}' {c} раз."


with open('4.txt', 'w') as f:
    for i in range(100000):
        f.write('python ')
    # f.write('\n')
    # for i in range(100000):
    #     f.write('python ')
print(count_word_occurrences('4.txt', 'python'))
