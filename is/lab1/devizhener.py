# import numpy as np
# from numba import jit, prange

ru_alphabet = "абвгдеёжзийклмнопрстуфхцчшщьъыэюя"

# with open('russian.txt', 'r', encoding="cp1251") as f:
#     lines = f.readlines()
# print(len(lines))
# with open('ru_words.txt', 'w') as f:
#     for line in lines:
#         skip = False
#         for ch in line[:-1]:
#             if ch not in ru_alphabet:
#                 skip = True
#                 break
#         if skip:
#             continue
#         else:
#             f.write(line)

with open('ru_words.txt', 'r') as f:
    words = f.read().split('\n')
print(len(words))

coded_msg = "ыодхчаюъбькящячгчгщщб"
coded_msg = "йсагофрем"

i = 0
for key in words:
    decoded_msg = ''
    for i in range(len(coded_msg)):
        ch = coded_msg[i]
        if ch.isalpha():
            key_ch = key[i % len(key)]
            key_chi = ru_alphabet.find(key_ch)
            chi = ru_alphabet.find(ch)
            decoded_msg += ru_alphabet[chi - key_chi]
        else:
            decoded_msg += ch
    for word in words:
        if len(word) > 5 and word in decoded_msg:
            print(decoded_msg, i, '/', len(words))
    i += 1



# coded_msg = 'гфтзюркёп пёщмчышфг'
# key = 'море'
# decoded_msg = ''
# for i in range(len(coded_msg)):
#     ch = coded_msg[i]
#     if ch.isalpha():
#         key_ch = key[i % len(key)]
#         key_chi = ru_alphabet.find(key_ch)
#         chi = ru_alphabet.find(ch)
#         decoded_msg += ru_alphabet[chi - key_chi]
#     else:
#         decoded_msg += ch
# print(decoded_msg)

"""

завтра две лекции
задание к лабе на лекции
индивидуальная беседа
работающая прога интуитивно понятный интерфейс
отчет по каждой лабе

долги до 1 октября
лабы с октября

титульник
задание
теор часть
текст программы (только часть с моделированием)
результат
вывод
3-4 листа не больше
после подписи не выбрасывать


пятница с 10 до 12
если лабы не сданы до 31 декабря то лабы вместо экзамена за экз неуд
всего 8 лаб
инструмент любой главное суть
но питон самое последнее

экз
два теор вопроса и одна задача
все лабы сданы освобождение от задачи
gpss

"""
