with open("reports/report-functesting-latest.txt", "r") as f:
    lines = f.readlines()
coverage = int(lines[-1].split()[-1][:-1])
with open("results/functest_tmp.txt", "r") as f:
    lines = f.readlines()
lines.insert(0, f"{coverage:.2f} \n")
with open("reports/report-functesting-latest.txt", "w") as f:
    f.writelines(lines)
