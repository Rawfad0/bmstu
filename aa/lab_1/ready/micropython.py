import gc

from utime import ticks_ms as ticks
import urandom


def record_process_time(func, *args):
    gc.disable()
    tb = ticks()
    func(*args)
    te = ticks()
    gc.collect()
    gc.enable()
    return te - tb


def generate_str(length):
    return ''.join([urandom.choice('abcdefghijklmnopqrstuvwxyz') for _ in range(length)])


def lev_dist(s1, s2):
    l1, l2 = len(s1), len(s2)
    matrix = [[0 for _ in range(l2 + 1)] for _ in range(l1 + 1)]

    for i in range(l1 + 1):
        matrix[i][0] = i
    for j in range(l2 + 1):
        matrix[0][j] = j

    # print(*matrix, sep='\n')
    for i in range(1, l1 + 1):
        for j in range(1, l2 + 1):
            change = 1 if s1[i - 1] != s2[j - 1] else 0
            matrix[i][j] = min(matrix[i][j - 1] + 1,
                               matrix[i - 1][j] + 1,
                               matrix[i - 1][j - 1] + change)
    # print(*matrix, sep='\n')
    return matrix[l1][l2]


def lev_dist_rec_entry(s1, s2):
    return lev_dist_rec(s1, s2, len(s1), len(s2))


def lev_dist_rec(s1, s2, l1, l2):
    if l1 == 0:
        return l2
    if l2 == 0:
        return l1

    change = 1 if s1[l1 - 1] != s2[l2 - 1] else 0
    res = min(lev_dist_rec(s1, s2, l1, l2 - 1) + 1,
              lev_dist_rec(s1, s2, l1 - 1, l2) + 1,
              lev_dist_rec(s1, s2, l1 - 1, l2 - 1) + change)
    return res


def lev_rec_cache_entry(s1, s2):
    l1, l2 = len(s1), len(s2)

    matrix = [[-1 for _ in range(l2 + 1)] for _ in range(l1 + 1)]
    lev_rec_cache(s1, s2, l1, l2, matrix)
    # print(*matrix, sep='\n')
    return matrix[l1][l2]


def lev_rec_cache(s1, s2, l1, l2, matrix):
    if l1 == 0:
        matrix[l1][l2] = l2
    elif l2 == 0:
        matrix[l1][l2] = l1
    else:
        if matrix[l1 - 1][l2] == -1:
            lev_rec_cache(s1, s2, l1 - 1, l2, matrix)
        if matrix[l1][l2 - 1] == -1:
            lev_rec_cache(s1, s2, l1, l2 - 1, matrix)
        if matrix[l1 - 1][l2 - 1] == -1:
            lev_rec_cache(s1, s2, l1 - 1, l2 - 1, matrix)

        change = 1 if s1[l1 - 1] != s2[l2 - 1] else 0
        matrix[l1][l2] = min(matrix[l1][l2 - 1] + 1,
                             matrix[l1 - 1][l2] + 1,
                             matrix[l1 - 1][l2 - 1] + change)


def dam_lev_dist(s1, s2):
    l1, l2 = len(s1), len(s2)
    matrix = [[0 for _ in range(l2 + 1)] for _ in range(l1 + 1)]

    for i in range(l1 + 1):
        matrix[i][0] = i
    for j in range(l2 + 1):
        matrix[0][j] = j

    # print(*matrix, sep='\n')
    for i in range(1, l1 + 1):
        for j in range(1, l2 + 1):
            change = 1 if s1[i - 1] != s2[j - 1] else 0
            matrix[i][j] = min(matrix[i][j - 1] + 1,
                               matrix[i - 1][j] + 1,
                               matrix[i - 1][j - 1] + change)
            if i > 1 and j > 1 and s1[i - 1] == s2[j - 2] and s1[i - 2] == s2[j - 1]:
                matrix[i][j] = min(matrix[i][j], matrix[i - 2][j - 2] + 1)
    # print(*matrix, sep='\n')
    return matrix[l1][l2]


length = 5
n = 100

print("MAX_LEN=", length)
print("REPEAT=", n)

algs = [lev_dist,
        lev_dist_rec_entry,
        lev_rec_cache_entry,
        dam_lev_dist,
        ]
algs_name = [
    "Расстояние Левенштейна (нерекурсивный алгоритм):",
    "Расстояние Левенштейна (рекурсивный алгоритм):",
    "Расстояние Левенштейна (рекурсивный алгоритм с кэшем):",
    "Расстояние Дамерау-Левенштейна (не рекурсивный алгоритм):",
]

for l in range(length+1):
    print("\nLENGTH=", l)
    for i in range(len(algs)):
        t = 0.0
        for _ in range(n):
            s1, s2 = generate_str(l), generate_str(l)
            t += record_process_time(algs[i], s1, s2)
        print(algs_name[i], t/n)
