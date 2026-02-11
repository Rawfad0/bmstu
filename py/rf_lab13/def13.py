# 13 вводится входной файл с текстом разбитым по предложениям точками
# необходимо записать в выходной файл предложения в обратном порядке при этом
# на каждой строке должно находится одно предложение



with open('input1.txt', 'r', encoding='UTF-8') as f, open('output1.txt', 'w') as ff:
    n_words_in_sentence = list()
    n_words_in_sentence.append(0)
    sentence_counter = 0
    while (line := f.readline()) != '':
        line = line.split()
        for i in range(len(line)):
            word = line[i]
            n_words_in_sentence[sentence_counter] += 1
            if '.' in word:
                n_words_in_sentence.append(0)
                sentence_counter += 1

    del n_words_in_sentence[-1]
    # print(n_words_in_sentence)

    for sentence_i in range(len(n_words_in_sentence), 0, -1):
        # print(sentence_i)
        sentence_counter = 1
        f.seek(0)
        sentence = ''
        while (line := f.readline()) != '':
            line = line.split()
            for i in range(len(line)):
                word = line[i]
                # print(word, sentence_counter)
                if sentence_i == sentence_counter:
                    sentence += word + ' '
                if '.' in word:
                    sentence_counter += 1

        ff.write(sentence+'\n')

