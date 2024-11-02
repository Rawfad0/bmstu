with open("reports/report-unittesting-latest.txt", "r") as f:
    lines = f.readlines()
coverage = int(lines[-1].split()[-1][:-1])
lines.insert(0, f"{coverage:.2f} \n")
with open("reports/report-unittesting-latest.txt", "w") as f:
    f.writelines(lines)
