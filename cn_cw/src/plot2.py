#!/usr/bin/env python3
import pandas as pd
import matplotlib.pyplot as plt

files = [
    ("res/2_2.csv", "2 процесса"),
    ("res/2_4.csv", "4 процесса"),
    ("res/2_8.csv", "8 процесса")
]

plt.figure(figsize=(10,6))
colors = ["blue", "green", "red"]

for i, (csv_file, label) in enumerate(files):
    df = pd.read_csv(csv_file, header=None,
                     names=["connections", "mb", "seconds", "throughput", "per_connection"])
    
    plt.plot(df["connections"], df["per_connection"], marker='o', linestyle='-', color=colors[i], label=label)

plt.xlabel("Количество одновременных подключений")
plt.ylabel("Пропускная способность (MB/s)")
plt.grid(True)
plt.legend()
plt.tight_layout()

plt.savefig("res/2_per_connection.svg", format="svg")
plt.close()

print("График сохранён в res/2_per_connection.svg")
