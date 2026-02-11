import random


def find_min_period_strict(s):
    n = len(s)
    for p in range(1, n//2 + 1):
        ok = True
        for i in range(n - p):
            if s[i] != s[i + p]:
                ok = False
                break
        if ok:
            return p
    return None


def crit(arr):
    d1 = [(arr[i + 1] - arr[i]) / 2 for i in range(len(arr) - 1)]
    # d2 = [(d1[i + 1] - d1[i]) / 2 for i in range(len(d1) - 1)]
    # d3 = [(d2[i + 1] - d2[i]) / 2 for i in range(len(d2) - 1)]
    # d4 = [(d3[i + 1] - d3[i]) / 2 for i in range(len(d3) - 1)]
    # d5 = [(d4[i + 1] - d4[i]) / 2 for i in range(len(d4) - 1)]
    # d6 = [(d5[i + 1] - d5[i]) / 2 for i in range(len(d5) - 1)]
    avg_crit = 1 - abs(4.5 - sum(arr) / len(arr)) / 4.5
    avg_d1_crit = 1 - abs(sum(d1) / len(d1)) / 0.5
    # avg_d2_crit = 1 - abs(sum(d2) / len(d2)) / 0.5625
    # avg_d3_crit = 1 - abs(sum(d3) / len(d3)) / 0.642857142857
    period_crit = 1 if find_min_period_strict(arr) is None else 0
    # avg_d4_crit = 1 - abs(sum(d4) / len(d4)) / 0.739583333
    # criteria = 0.25 * avg_crit + 0.25 * avg_d1_crit + 0.25 * avg_d2_crit + 0.25 * avg_d3_crit
    criteria = 0.3 * avg_crit + 0.3 * avg_d1_crit + 0.4 * period_crit
    return criteria, avg_crit, avg_d1_crit, period_crit


arrs = [
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 9, 9, 9, 9, 9],
    [0, 9, 0, 9, 0, 9, 0, 9, 0, 9],
    [0, 1, 2, 3, 4, 5, 6, 7, 8, 9],
    [1, 2, 1, 2, 1, 2, 1, 2, 1, 2],
    [1, 2, 3, 1, 2, 3, 1, 2, 3, 1],
    [8, 5, 4, 1, 4, 5, 4, 5, 8, 3],
    random.choices([i for i in range(10)], k=10),
    random.choices([i for i in range(10)], k=10),
    random.choices([i for i in range(10)], k=10),
    random.choices([i for i in range(10)], k=10),
    random.choices([i for i in range(10)], k=10),
    random.choices([i for i in range(10)], k=10),
    random.choices([i for i in range(10)], k=10),
    random.choices([i for i in range(10)], k=10),
    random.choices([i for i in range(10)], k=10),
    random.choices([i for i in range(10)], k=10),
]
for arr in arrs:
    print(arr, crit(arr))

# max_crit = 0
# for i in range(1000000):
#     arr = random.choices([i for i in range(100)], k=10)
#     res = crit(arr)
#     if res > max_crit:
#         max_crit = res
# print(max_crit)

# d1 0.5
# d2 0.5625
# d3 0.642857142857
# d4 0.739583333



# 0.9927386541458353