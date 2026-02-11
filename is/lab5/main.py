# def polynomial_multiplication(multiplicand, multiplier):
#     l_p = (len(multiplicand) + len(multiplier) - 1)
#     product = [0] * l_p
#     for i in range(len(multiplier)):
#         k = multiplier[i]
#         for j in range(len(multiplicand)):
#             product[i + j] += k*multiplicand[j]
#     return product
#
#
# def polynomial_division(dividend, divisor):
#     quotient = []
#     a, b = dividend.copy(), divisor.copy()
#     for i in range(len(a) - len(b) + 1):
#         k = a[0]/b[0]
#         quotient.append(k)
#         for j in range(len(b)):
#             a[j] -= k*b[j]
#         del a[0]
#     remainder = a
#     return quotient, remainder
#
#
# def gf_sum(a, b):
#     print()
#     r = a ^ b
#     return r
#
#
# def bin2pol(b):
#     return list(map(int, list(f"{b:b}")))
#
#
# def pol2bin(p):
#     return "".join(p)


def mulx(b):
    highbit = b & 0x80
    shl = (b << 1) & 0xff
    return shl if highbit == 0 else shl ^ 0x1b


def gf_mul(a, b):
    bp_b = str(bin(b))[2:]
    s = 0
    for i in range(len(bp_b)):
        if bp_b[i] == '1':
            n = a
            for j in range(len(bp_b) - (i + 1)):
                n = mulx(n)
            s ^= n
    return s

gf_inv = dict()

for i in range(256):
    for j in range(256):
        if gf_mul(i, j) == 1:
            gf_inv[i] = j


def left_shift(row, n):
    for i in range(n):
        tmp = row[0]
        row.remove(tmp)
        row.append(tmp)


def shift_rows(state):
    for i in range(4):
        left_shift(state[i], i)


def mix_column(state):
    pass


def add_round_key(state, key):
    for i in range(4):
        for j in range(4):
            state[i][j] = state[i][j] ^ key[i][j]


# p = 0b001110
# q = 0b100001
# m = 0b100011011
# print(p, q, m)
# r = p*q % m
# print(r)

print("======")
mtx = [
    [0, 1, 2, 3],
    [4, 5, 6, 7],
    [8, 9, 10, 11],
    [12, 13, 14, 15]
]
key = [[1 for i in range(4)] for j in range(4)]
add_round_key(mtx, key)
print(*mtx, sep='\n')



if __name__ == "__main__":
    text = "ABC"
