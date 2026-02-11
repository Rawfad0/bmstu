def word_strip(word):  #
    word_l = list(word)
    remains = []
    for i in range(len(word_l)):
        if not word_l[i].isalpha() and not word_l[i] == '-':
            remains.append(word_l[i])
            word_l[i] = ''
    word = ''.join(word_l)
    remain = ''.join(remains)
    return word, remain


def word_strip_lr(word):  #
    word_l = list(word)
    l_remain = ''
    r_remain = ''
    new_word = ''
    flag = False
    for i in range(len(word_l)):
        if word_l[i].isalpha():
            flag = True
            new_word += word_l[i]
        elif flag and word_l[i] == '-':
            new_word += word_l[i]
        else:
            # word_l[i] = ''
            flag = False
        if not flag and len(new_word):
            r_remain += word_l[i]
        elif not len(new_word):
            l_remain += word_l[i]

    print(l_remain, r_remain, new_word)
    return new_word, l_remain, r_remain


def text_width(text):
    width = len(text[0])
    for line in text:
        if len(line) > width:
            width = len(line)
    return width


# 1. Выровнять текст по левому краю.
def text_align_left(text):
    mode = 'l'
    for i in range(len(text)):
        text[i] = ' '.join(text[i].split())

    width = text_width(text)
    for i in range(len(text)):
        text[i] = text[i].ljust(width)
    return text, mode


# 2. Выровнять текст по правому краю.
def text_align_right(text):
    mode = 'r'
    for i in range(len(text)):
        text[i] = ' '.join(text[i].split())

    width = text_width(text)
    for i in range(len(text)):
        lw = len(text[i])
        text[i] = ' '*(width - lw) + text[i]
    return text, mode


# 3. Выровнять текст по ширине.
def text_align_width(text):
    mode = 'w'
    for i in range(len(text)):
        line = ''
        for word in text[i].split():
            line += word + ' '
        text[i] = line.rstrip()

    width = text_width(text)
    for i in range(len(text) - 1):  # все кроме последней строки
        words = text[i].split()
        char_len = 0
        for word in words:
            char_len += len(word)
        spaces = width - char_len
        if len(words) <= 1:
            text[i] = ' '.join(words)
            text[i] = ' '.join(words) + ' '*(width - len(text[i]))
            continue
        else:
            space = spaces / (len(words) - 1)   # float
        line = f'{words[0]}'
        interval = 1e-8
        for j in range(1, len(words)):
            interval += space
            line += ' '*int(interval) + words[j]
            interval -= int(interval)
            # print(interval)
        text[i] = line
    text[-1] = ' '.join(text[-1].split())
    return text, mode


def align_update(text, mode):
    aligns = {'l': text_align_left,
              'r': text_align_right,
              'w': text_align_width}
    return aligns[mode](text)


# 4. Удаление всех вхождений заданного слова.
def text_del_all_word_intro(text, mode):
    del_w = input('Введите слово, которое будет удалено из текста: ')
    if len(del_w.split()) > 1:
        print('Слов больше одного.')
        return text
    for i in range(len(text)):
        words = text[i].split()
        for j in range(len(words)):
            word, l_remain, r_remain = word_strip_lr(words[j])
            if word == del_w:
                words[j] = l_remain + r_remain
        text[i] = ' '.join(words)

    text, mode = align_update(text, mode)
    return text


# 5. Замена одного слова другим во всём тексте.
def text_replace_all_words(text, mode):
    replaced_w = input('Введите слово, которое будет заменено: ')
    if len(replaced_w.split()) > 1:
        print('Слов больше одного.')
        return text
    replacement_w = input('Введите слово, которым будет заменено: ')

    for i in range(len(text)):
        words = text[i].split()
        for j in range(len(words)):
            word, l_remain, r_remain = word_strip_lr(words[j])
            if len(word) != 0 and word == replaced_w:
                words[j] = l_remain + replacement_w + r_remain
        text[i] = ' '.join(words)

    text, mode = align_update(text, mode)
    return text

# def calc(line):
#     print(line)
#     lst = []
#     start = 0
#     for i in range(len(line)):
#         if line[i] == ' ' or line[i] == '+' or line[i] == '-' or i == len(line) - 1:
#             lst.append(line[start:i + (i == len(line) - 1)])
#             if i != len(line) - 1:
#                 if line[i] == '+':
#                     lst.append('+')
#                 elif line[i] == '-':
#                     lst.append('-')
#             start = i + 1
#             # print(start, i, lst)
#     print(lst)
#     return '00000'


def line_calc(line):
    line += ' '     # добавил пробел, чтобы не проверять на последний индекс (прервется из-за пробела)
    n1 = ''         # первое число
    op = ''         # оператор (+ или -)
    n2 = ''         # второе число
    start = 0
    for i in range(len(line)):  # первое число
        suc = False
        # print(line[i])
        if (line[i] in '+-' and len(n1) == 0) or (line[i] in '0123456789'):
            n1 += line[i]
            # print(n1)
        else:
            if len(n1) > 0 and n1[-1] in '0123456789':  #
                for j in range(i, len(line)):   # знак
                    back = False
                    if line[j] in '+-':
                        op = line[j]
                        for k in range(j + 1, len(line)):   # второе число
                            # print(i, j, k, n1, op, n2, line)
                            if (line[k] in '+-' and len(n2) == 0) or (line[k] in '0123456789'):
                                n2 += line[k]
                            else:
                                if len(n2) > 0 and n2[-1] in '0123456789':
                                    if op == '+':
                                        n1 = str(int(n1) + int(n2))
                                    elif op == '-':
                                        n1 = str(int(n1) - int(n2))
                                    back = True
                                    suc = True
                                    n2 = ''
                                    break
                                elif len(n2) == 0:  # число пока не начиналось, этот символ - пробел, смотрим дальше
                                    continue
                                else:   # второе число закончилось не успев начаться
                                    back = True
                                    suc = False
                                    n2 = ''
                                    break

                    elif line[j] == ' ':
                        continue
                    else:
                        break
                    if back:    # закончили со вторым числом, возвращаемся
                        break
            if suc:
                line = line[:start] + n1.rjust(k - start) + line[k:]    # меняем два числа и знак на их результат
                n1 = ''
            else:
                start = i + 1
                n1 = ''
    return line


# 6. Вычисление арифметических выражений над целыми числами внутри текста (сложение и вычитание).
def text_calc(text, mode):
    for line_i in range(len(text)):
        words = text[line_i].split()
        start = 0
        for i in range(len(words)):
            is_calcable = True
            for char in words[i]:
                if not (char in '0123456789-+'):
                    is_calcable = False

            if (not is_calcable) or i == len(words) - 1:
                # length = i + ((i == len(words) - 1) and is_calcable) - start
                line = ' '.join(words[start:i + ((i == len(words) - 1) and is_calcable)])
                # result = calc(' '.join(words[start:i + ((i == len(words) - 1) and is_calcable)]))
                if len(line) > 0:
                    # print(line, ';;', start, i, i + ((i == len(words) - 1) and is_calcable))
                    result = line_calc(line)
                    # print(result)
                    for el in range(start, i + ((i == len(words) - 1) and is_calcable) - 1):
                        words[el] = ''
                    words[i + ((i == len(words) - 1) and is_calcable) - 1] = result
                start = i + 1
                # print(result)
                # print('0'*20)
        text[line_i] = ' '.join(words)

    text, mode = align_update(text, mode)
    return text


# # 6. Вычисление арифметических выражений над целыми числами внутри текста (сложение и вычитание).
# def text_sum_and_div(text, mode):
#     for i in range(len(text)):
#         words = text[i].split()
#         for j in range(len(words)):
#             if words[j] == '+':
#                 r = None
#                 try:
#                     a = int(words[j - 1])
#                     b = int(words[j + 1])
#                     r = a + b
#                 except Exception:
#                     pass
#                 if not (r is None):
#                     words[j - 1] = ''
#                     words[j] = str(r)
#                     words[j + 1] = ''
#
#             if words[j] == '-':
#                 r = None
#                 try:
#                     a = int(words[j - 1])
#                     b = int(words[j + 1])
#                     r = a - b
#                 except Exception:
#                     pass
#                 if not (r is None):
#                     words[j - 1] = ''
#                     words[j] = str(r)
#                     words[j + 1] = ''
#
#         text[i] = ' '.join(words)
#
#     text, mode = align_update(text, mode)
#     return text


# 7. Найти (вывести на экран) и затем удалить самое короткое слово в предложении, в котором слов больше всего.
def text_cut_word(text, mode):
    mx_sentence_i = 0
    mx_sentence_words = 0
    word_counter = 0
    sentence_counter = 0
    for i in range(len(text)):  # max words sentence
        words = text[i].split()
        for j in range(len(words)):
            word, l_remain, r_remain = word_strip_lr(words[j])
            if len(word) > 0:
                word_counter += 1
            if '.' in words[j]:
                if word_counter > mx_sentence_words:
                    mx_sentence_i = sentence_counter
                    mx_sentence_words = word_counter
                sentence_counter += 1
                word_counter = 0

    # print(mx_sentence_i)
    word_counter = 0
    sentence_counter = 0
    mn_word_len = None
    mn_word_i = None
    mn_word = ''
    for i in range(len(text)):  # min word in max sentence
        words = text[i].split()
        for j in range(len(words)):
            word, l_remain, r_remain = word_strip_lr(words[j])
            if sentence_counter == mx_sentence_i:
                # print(mn_word)
                # print(word, len(word))
                if (len(word) > 0 and mn_word_len is None) or (0 < len(word) < mn_word_len):
                    mn_word_i = word_counter
                    mn_word_len = len(word)
                    mn_word = word
            if len(word) > 0:
                word_counter += 1
            if '.' in words[j]:
                sentence_counter += 1
                word_counter = 0
            # print(sentence_counter, word_counter, mn_word_id)

    # print(mn_word_i, mn_word)
    if len(mn_word) > 0:
        print(mn_word)
        word_counter = 0
        sentence_counter = 0
        for i in range(len(text)):  # del word
            words = text[i].split()
            for j in range(len(words)):
                # print(j, words[j], sentence_counter, word_counter)
                word, l_remain, r_remain = word_strip_lr(words[j])
                if sentence_counter == mx_sentence_i and word_counter == mn_word_i:
                    # print(words[j], j)
                    words[j] = l_remain + r_remain
                if len(word) > 0:
                    word_counter += 1
                if '.' in words[j]:
                    sentence_counter += 1
                    word_counter = 0
            text[i] = ' '.join(words)
    else:
        print('Слова не нашлось.')

    text, mode = align_update(text, mode)
    return text

