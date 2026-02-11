from lab2.main import generate_key
import itertools
import matplotlib.pyplot as plt
from scipy.stats import chi2


def serial_test(key, k=4, alpha=0.1):
    serial_comb = list(itertools.product([0, 1], repeat=k))
    serials_dict = {''.join(map(str, serial)): 0 for serial in serial_comb}

    for i in range(len(key) - k + 1):
        serials_dict[key[i:i+k]] += 1

    total_sequences = len(key) - k + 1
    expected_frequency = total_sequences / (2 ** k)
    serials = []
    counts = []
    for serial, count in serials_dict.items():
        serials.append(serial)
        counts.append(count)

    chi_square = sum((count - expected_frequency) ** 2 / expected_frequency for count in counts)
    df = (2 ** k) - 1
    critical_value = chi2.ppf(1 - alpha, df)
    return serials_dict, chi_square, critical_value, chi_square < critical_value


if __name__ == "__main__":
    key = generate_key()
    print(f"key: {key}\n")

    for k in range(2, 4+1):
        print(f"SERIAL TEST k={k}")
        serials_dict, chi_square, critical_value, result = serial_test(key, k)
        print(f"Статистика хи-квадрат: {chi_square:.3f}")
        print(f"Крит. значение (α=0.1): {critical_value:.3f}")
        if result:
            print("Последовательность выглядит случайной\n")
        else:
            print("Последовательность не случайна\n")
