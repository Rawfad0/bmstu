import matplotlib.pyplot as plt

max_length = 5
# t = [
#     [0.09, 0.01, 0.12, 0.11,],
#     [0.15, 0.06, 0.14, 0.14,],
#     [0.2, 0.23, 0.28, 0.24, ],
#     [0.35, 1.15, 0.5699999999999999, 0.4, ],
#     [0.58, 5.95, 0.9399999999999999, 0.7, ],
#     [0.8199999999999999, 30.97, 1.39, 1.03, ]
# ]
# for i, line in enumerate(t):
#     print(i, *line, sep=' & ', end=' \\\\\n\\hline\n')
t = [
    [0.09, 0.15, 0.2, 0.35, 0.58, 0.82],
    [0.01, 0.06, 0.23, 1.15, 5.95, 30.97],
    [0.12, 0.14, 0.28, 0.57, 0.94, 1.39],
    [0.11, 0.14, 0.24, 0.4, 0.7, 1.03]
]

limit = 5
length_arr = [i for i in range(0, limit)]
plt.figure(1)
plt.plot(length_arr, t[0][:limit], label='Левенштейн', color='b', marker='.')
plt.plot(length_arr, t[1][:limit], label='Левенштейн рек', color='orange', marker='.')
plt.plot(length_arr, t[2][:limit], label='Левенштейн рек кэш', color='g', marker='.')
plt.plot(length_arr, t[3][:limit], label='Дамерау-Левенштейн', color='r', marker='.')
plt.legend(loc='best', fontsize=12)
plt.xlabel('Длина строки')
plt.ylabel('Время, мс')
plt.grid(True)
plt.show()

limit = 6
length_arr = [i for i in range(0, limit)]
plt.figure(2)
plt.plot(length_arr, t[0][:limit], label='Левенштейн', color='b', marker='.')
plt.plot(length_arr, t[2][:limit], label='Левенштейн рек кэш', color='g', marker='.')
plt.plot(length_arr, t[3][:limit], label='Дамерау-Левенштейн', color='r', marker='.')
plt.legend(loc='best', fontsize=12)
plt.xlabel('Длина строки')
plt.ylabel('Время, мс')
plt.grid(True)
plt.show()

limit = 6
length_arr = [i for i in range(0, limit)]
plt.figure(3)
plt.plot(length_arr, t[0][:limit], label='Левенштейн', color='b', marker='.')
plt.plot(length_arr, t[3][:limit], label='Дамерау-Левенштейн', color='r', marker='.')
plt.legend(loc='best', fontsize=12)
plt.xlabel('Длина строки')
plt.ylabel('Время, мс')
plt.grid(True)
plt.show()
