from lab2.main import generate_key
import numpy as np


def correlation_test(key, k=9):
    N = len(key)
    x = np.array([int(ch) for ch in key], dtype=float)

    x1, x2 = x[:N-k], x[k:]
    m1, m2 = np.mean(x1), np.mean(x2)
    d1, d2 = np.var(x1, ddof=1), np.var(x2, ddof=1)

    r = np.sum((x1 - m1) * (x2 - m2)) / ((N - k) * np.sqrt(d1 * d2))
    r_crit = 1 / (N - 1) + 2 / (N - 2) * np.sqrt(N*(N - 3) / (N - 1))
    return r, np.abs(r) <= r_crit


if __name__ == "__main__":
    key = generate_key()
    print("Длина ключа:", len(key))
    for k in [1, 2, 8, 9]:
        r, result = correlation_test(key, k)
        print(f"R[{k}] = {r: .6f} => {result}")
