def extended_euqlidean_alg(a, b):
    x1, x2 = 0, 1
    y1, y2 = 1, 0
    while b > 0:
        q = a // b
        # print("q", q)
        r = a - q * b
        # print("r", r)
        x = x2 - q * x1
        y = y2 - q * y1
        # print("xy", x, y)
        a, b = b, r
        # print("ab", a, b)
        x1, x2 = x, x1
        y1, y2 = y, y1
        # print("x", x1, x2)
        # print("y", y1, y2)

    return x2, y2


def gen_e(fi_n):
    # i = fi_n
    # while i >= 3:
    #     a, b = extended_euqlidean_alg(fi_n, i)
    #     if a * fi_n + b * i:
    #         break
    #     i -= 1
    # return i
    # return 691
    return 13


def get_d(fi_n, e):
    x2, y2 = extended_euqlidean_alg(fi_n, e)
    print(x2, y2)
    return fi_n - abs(min(x2, y2))


def encrypt(msg, open_key):
    return msg**open_key[0] % open_key[1]


def decrypt(msg, closed_key):
    return msg**closed_key[0] % closed_key[1]


if __name__ == "__main__":
    p = 7
    q = 11
    e = 13
    n = p * q
    fi_n = (p - 1) * (q - 1)
    # e = gen_e(fi_n)
    d = get_d(fi_n, e)
    print(f"p = {p}, q = {q}")
    print(f"n = {n}")
    print(f"fi_n = {fi_n}")
    print(f"e = {e}, d = {d}")
    open_key = (e, n)
    closed_key = (d, n)
    print("Open key", open_key)
    print("Closed key", closed_key)

    message = 63
    print("MSG:", message)

    encrypted_msg = encrypt(message, open_key)
    print("ENCRYPT:", encrypted_msg)
    decrypted_msg = decrypt(encrypted_msg, closed_key)
    print("DECRYPT:", decrypted_msg)


# prime_nums = [2]
# last_num = 2
#
#
# def is_prime(num):
#     if num <= 1:
#         return False
#     if num <= prime_nums[-1]:
#         for i in prime_nums:
#             if num == i:
#                 return True
#             if num % i == 0:
#                 return False
#     else:
#         for i in prime_nums:
#             if num % i == 0:
#                 return False
#         for i in range(last_num, int(num**0.5) + 1):
#             # print(i)
#             if num % i == 0:
#                 return False
#         prime_nums.append(num)
#     return True
#
#
# def gen_primes():
#     for i in range(1 << 512):
#         if is_prime(i) is False:
#             last_not_prime = i
#         else:
#             print(len(prime_nums), i)
#
#
#
# def gen_prime(b=512):
#     n = 1 << b
#     while is_prime(n) is False:
#         print(n)
#         # last_not_prime = n
#         n += 1
#     return n

# gen_primes()
# print(gen_prime())
