with open('../log.txt', 'r') as f:
    for line in f.readlines():
        splt = line.split()
        if len(splt) == 4:
            if int(splt[1]) <= 4:
                if splt[2] == "reading":
                    op = "чтение"
                elif splt[2] == "processing":
                    op = "парсинг"
                else:
                    op = "запись"
                if splt[3] == "begin":
                    s = "начало"
                else:
                    s = "окончание"

                print(f"{splt[0]} & {splt[1]}: {op} --- {s}\\\\ \\hline")
