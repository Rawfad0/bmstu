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


def lev_dist_rec(s1, s2, l1, l2):
    # print(f"id(s1)={id(s1)}, {l1}; id(s1)={id(s2)}, {l2};")
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


def dam_lev_dist_rec(s1, s2, l1, l2):
    if l1 == 0:
        return l2
    if l2 == 0:
        return l1

    change = 1 if s1[l1 - 1] != s2[l2 - 1] else 0
    res = min(dam_lev_dist_rec(s1, s2, l1, l2 - 1) + 1,
              dam_lev_dist_rec(s1, s2, l1 - 1, l2) + 1,
              dam_lev_dist_rec(s1, s2, l1 - 1, l2 - 1) + change)
    if l1 > 1 and l2 > 1 and s1[l1 - 1] == s2[l2 - 2] and s1[l1 - 2] == s2[l2 - 1]:
        res = min(res, dam_lev_dist_rec(s1, s2, l1 - 2, l2 - 2) + 1)
    return res


def dam_lev_rec_cache_entry(s1, s2):
    l1, l2 = len(s1), len(s2)

    matrix = [[-1 for _ in range(l2 + 1)] for _ in range(l1 + 1)]
    dam_lev_rec_cache(s1, s2, l1, l2, matrix)
    # print(*matrix, sep='\n')
    return matrix[l1][l2]


def dam_lev_rec_cache(s1, s2, l1, l2, matrix):
    if l1 == 0:
        matrix[l1][l2] = l2
    elif l2 == 0:
        matrix[l1][l2] = l1
    else:
        if matrix[l1 - 1][l2] == -1:
            dam_lev_rec_cache(s1, s2, l1 - 1, l2, matrix)
        if matrix[l1][l2 - 1] == -1:
            dam_lev_rec_cache(s1, s2, l1, l2 - 1, matrix)
        if matrix[l1 - 1][l2 - 1] == -1:
            dam_lev_rec_cache(s1, s2, l1 - 1, l2 - 1, matrix)

        change = 1 if s1[l1 - 1] != s2[l2 - 1] else 0
        matrix[l1][l2] = min(matrix[l1][l2 - 1] + 1,
                             matrix[l1 - 1][l2] + 1,
                             matrix[l1 - 1][l2 - 1] + change)
        if l1 > 1 and l2 > 1 and s1[l1 - 1] == s2[l2 - 2] and s1[l1 - 2] == s2[l2 - 1]:
            matrix[l1][l2] = min(matrix[l1][l2], matrix[l1 - 2][l2 - 2] + 1)
