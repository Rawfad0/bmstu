from prime_gen import generate_prime
import math


def extended_euclidean_alg(a, b):
    x1, x2 = 0, 1
    y1, y2 = 1, 0
    while b > 0:
        q = a // b
        r = a - q * b
        x = x2 - q * x1
        y = y2 - q * y1
        a, b = b, r
        x1, x2 = x, x1
        y1, y2 = y, y1
    return x2, y2


def gen_e(fi_n):
    for e in range(3, fi_n):
        x, y = extended_euclidean_alg(fi_n, e)
        if fi_n * x + e * y == 1:  # gcd == 1
            return e
    # return 691
    # return 13


def get_d(fi_n, e):
    x2, y2 = extended_euclidean_alg(fi_n, e)
    print(x2, y2)
    return fi_n - abs(min(x2, y2))


def pow_mod(n, pow, mod):
    res = 1
    while pow > 0:
        if pow % 2 == 1:
            res = (res * n) % mod
            pow -= 1
        else:
            n = (n * n) % mod
            pow = pow // 2
    return res


def encrypt(msg, open_key):
    return pow_mod(msg, open_key[0], open_key[1])


def decrypt(msg, closed_key):
    return pow_mod(msg, closed_key[0], closed_key[1])


if __name__ == "__main__":
    p = generate_prime(30)
    q = generate_prime(30)
    # p = 55240416320382117946022627613687638985307167828352073 #generate_prime(30)
    # q = 27548767790482337289507858175559288639809160667685883 #generate_prime(30)
    # p = 698516047048107676516949799683604343610531331202910977244920145367906212943851858873181245842440341286402193876679578773794976277643432994771357996055539617861603790655925613977534877101463575024808765998378277341134135085194505141447
    # q = 702858387032036565789411333711911922650144236688180376276665351779426916320110042564384958634025908645228528266745657778159771969247876354975910715241106137445894250102381216289941198539768517625748344099635330154676624812922436004247
    n = p * q
    fi_n = (p - 1) * (q - 1)
    # e = gen_e(fi_n)
    e = 13
    d = get_d(fi_n, e)
    print(f"p =    {p}")
    print(f"q =    {q}")
    print(f"n =    {n}")
    print(f"fi_n = {fi_n}")
    print(f"e =    {e}")
    print(f"d =    {d}")
    open_key = (e, n)
    closed_key = (d, n)
    print("Open key", open_key)
    print("Closed key", closed_key)

    message = 321
    print("MSG:", message)

    encrypted_msg = encrypt(message, open_key)
    print("ENCRYPT:", encrypted_msg)
    decrypted_msg = decrypt(encrypted_msg, closed_key)
    print("DECRYPT:", decrypted_msg)

