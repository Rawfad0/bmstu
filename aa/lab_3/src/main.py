import matplotlib.pyplot as plt

sizes = []
t_stds = []
t_wins = []
t_opts = []

with open('../res_safe.txt', 'r') as f:
    lines = f.read().splitlines()

for line in lines:
    size, t_std, t_win, t_opt = line.split()
    sizes.append(int(size))
    t_stds.append(float(t_std))
    t_wins.append(float(t_win))
    t_opts.append(float(t_opt))

for i in range(5):
    filename = f'../res{i+1}.txt'
    with open(filename, 'r') as f:
        lines = f.read().splitlines()
    for j, line in enumerate(lines):
        size, t_std, t_win, t_opt = line.split()
        t_wins[j] = max(t_wins[j], float(t_win))
        t_opts[j] = min(t_opts[j], float(t_opt))

with open('../res_best.txt', 'w') as f:
    for i in range(len(sizes)):
        f.write(f'{sizes[i]} {t_stds[i]} {t_wins[i]} {t_opts[i]}\n')

print(sizes)
print(t_stds)
print(t_wins)
print(t_opts)

for i in range(len(sizes)):
    print(f'{sizes[i]} & {t_stds[i]} & {t_wins[i]} & {t_opts[i]} \\\\\n\\hline')

plt.figure()
plt.plot(sizes, t_stds, label='Стандартный алг.', color='b', marker='.')
plt.plot(sizes, t_wins, label='Алг. Винограда', color='g', marker='^')
plt.plot(sizes, t_opts, label='Алг. Винограда оптимизированный', color='r', marker='v')
plt.legend(loc='best', fontsize=12)
plt.xlabel('Размерность матрицы')
plt.ylabel('Время, мс')
plt.grid(True)
plt.show()
