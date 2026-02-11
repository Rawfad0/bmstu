from lab2.main import generate_key
from scipy.stats import chi2


def poker_test(key, m=4, alpha=0.1, df=6):
    k = len(key) // m
    blocks = [key[i*m:(i+1)*m] for i in range(k)]

    freq = {}
    for block in blocks:
        freq[block] = freq.get(block, 0) + 1

    sum_sq = sum(v**2 for v in freq.values())
    X2 = (2**m / k) * sum_sq - k

    chi_crit = chi2.ppf(1 - alpha, df)
    return X2, chi_crit, X2 <= chi_crit


if __name__ == "__main__":
    decision = False
    iter = 0
    while not decision:
        key = generate_key(256)
        X2, chi_crit, decision = poker_test(key)
        iter += 1
    print(f"key={key}")
    print(f"Статистика X^2 = {X2:.3f}")
    print(f"Критическое значение = {chi_crit}")
    print(f"Решение: {"Ключ случайный" if decision else "Ключ неслучайный"}")
    print(f"Случайный ключ найден спустя итераций: {iter}")
