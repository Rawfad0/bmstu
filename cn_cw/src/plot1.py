#!/usr/bin/env python3
import pandas as pd
import matplotlib.pyplot as plt

files = [
    ("res/1_2.csv", "2 процессов"),
    ("res/1_4.csv", "4 процесса"),
    ("res/1_8.csv", "8 процессов")
]

plt.figure(figsize=(10,6))

colors = ["blue", "green", "red"]

for i, (csv_file, label) in enumerate(files):
    df = pd.read_csv(csv_file, header=None,
                     names=["connections", "success", "failed", "success_rate", "mb", "seconds", "throughput"])
    plt.plot(df["connections"], df["success_rate"], marker='o', linestyle='-', color=colors[i], label=label)

plt.xlabel("Количество одновременных подключений")
plt.ylabel("Процент успешных соединений (%)")
# plt.title("Процент успешных соединений отколичества одновременных ")
plt.grid(True)
plt.legend()

output_file = "res/1_all.svg"
plt.savefig(output_file, format="svg")
plt.close()

print(f"График сохранён в {output_file}")
