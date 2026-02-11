import math
import random


def get_sieve(n):
    isprime = [True for _ in range(n)]
    prime = []
    spf = [None for _ in range(n)]

    isprime[0] = isprime[1] = False
    for i in range(2, n):
        if isprime[i]:
            prime.append(i)
            spf[i] = i

        j = 0
        while (j < len(prime) and i * prime[j] < n and prime[j] <= spf[i]):
            isprime[i*prime[j]] = False
            spf[i*prime[j]] = prime[j]
            j += 1

    return prime


def is_probably_prime(n, sieve):
    for x in sieve:
        if n % x == 0:
            return False
    return True


def generate_prime(n: int, primes=None, s=None):
    up_limit = 10 ** n

    if not primes:
        primes = get_sieve(1000)

    if not s:
        s = primes[-1]
    while s < up_limit:
        lo, hi = (s + 1) >> 1, (s << 1) + 1

        while True:
            r = random.randint(lo, hi) << 1
            n = s * r + 1

            if not is_probably_prime(n, primes):
                continue

            while True:
                a = random.randint(2, n - 1)

                if pow(a, n - 1, n) != 1:
                    break

                d = math.gcd((pow(a, r, n) - 1) % n, n)
                if d != n:
                    if d == 1:
                        s = n
                    else:
                        pass
                    break
                else:
                    pass
            if s == n:
                break
    return s


if __name__ == "__main__":
    num = generate_prime(50)
    print(num)
