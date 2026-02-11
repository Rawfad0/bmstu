import gc

from algs import lev_dist, lev_dist_rec, lev_rec_cache_entry, dam_lev_dist, dam_lev_dist_rec, dam_lev_rec_cache_entry
from utils import record_process_time, generate_str
import matplotlib.pyplot as plt


print("1. Единичный расчет")
print("2. Массированный замер процессорного времени")
print("3. График")
command = int(input(": ") or 3)
if command == 1:
    s1 = input("Введите первую строку: ") or "exponential"
    s2 = input("Введите вторую строку: ") or "polynomial"

    res = lev_dist(s1, s2)
    print(f"{'Расстояние Левенштейна (нерекурсивный алгоритм):':65}{res}")

    res = lev_dist_rec(s1, s2, len(s1), len(s2))
    print(f"{'Расстояние Левенштейна (рекурсивный алгоритм):':65}{res}")

    res = lev_rec_cache_entry(s1, s2)
    print(f"{'Расстояние Левенштейна (рекурсивный алгоритм c кэшем):':65}{res}")

    res = dam_lev_dist(s1, s2)
    print(f"{'Расстояние Дамерау-Левенштейна (нерекурсивный алгоритм):':65}{res}")

    res = dam_lev_dist_rec(s1, s2, len(s1), len(s2))
    print(f"{'Расстояние Дамерау-Левенштейна (рекурсивный алгоритм):':65}{res}")

    res = dam_lev_rec_cache_entry(s1, s2)
    print(f"{'Расстояние Дамерау-Левенштейна (рекурсивный алгоритм c кэшем):':65}{res}")
elif command == 2:
    length = int(input("Введите длину строк: ") or 7)
    n = int(input("Введите количество замеров: ") or 100)

    t_lev = 0
    t_lev_rec = 0
    t_lev_rec_cache = 0
    t_dam_lev = 0
    t_dam_lev_rec = 0
    t_dam_lev_rec_cache = 0
    for _ in range(n):
        s1, s2 = generate_str(length), generate_str(length)

        t_lev += record_process_time(lev_dist, s1, s2)
        t_lev_rec += record_process_time(lev_dist_rec, s1, s2, length, length)
        t_lev_rec_cache += record_process_time(lev_rec_cache_entry, s1, s2)
        t_dam_lev += record_process_time(dam_lev_dist, s1, s2)
        t_dam_lev_rec += record_process_time(dam_lev_dist_rec, s1, s2, length, length)
        t_dam_lev_rec_cache += record_process_time(dam_lev_rec_cache_entry, s1, s2)

    print(f"{'Расстояние Левенштейна (нерекурсивный алгоритм):':65} {t_lev:.6f}")
    print(f"{'Расстояние Левенштейна (рекурсивный алгоритм):':65} {t_lev_rec:.6f}")
    print(f"{'Расстояние Левенштейна (рекурсивный алгоритм c кэшем):':65} {t_lev_rec_cache:.6f}")
    print(f"{'Расстояние Дамерау-Левенштейна (нерекурсивный алгоритм):':65} {t_dam_lev:.6f}")
    print(f"{'Расстояние Дамерау-Левенштейна (рекурсивный алгоритм):':65} {t_dam_lev_rec:.6f}")
    print(f"{'Расстояние Дамерау-Левенштейна (рекурсивный алгоритм c кэшем):':65} {t_dam_lev_rec_cache:.6f}")
elif command == 3:
    max_length = int(input("Введите максимальную длину строк: ") or 9)
    n = int(input("Введите количество замеров: ") or 100)

    if n == 0:
        print("себя на ноль подели")
    else:
        t = [[0 for _ in range(max_length)] for _ in range(4)]
        gc.freeze()
        for length in range(max_length):
            for _ in range(n):
                s1, s2 = generate_str(length), generate_str(length)
                t[0][length] += record_process_time(lev_dist, s1, s2)
                # t[1][length] += record_process_time(lev_dist_rec, s1, s2, length, length)
                t[2][length] += record_process_time(lev_rec_cache_entry, s1, s2)
                t[3][length] += record_process_time(dam_lev_dist, s1, s2)
                # t[4][length] += record_process_time(dam_lev_dist_rec, s1, s2, length, length)
                # t[5][length] += record_process_time(dam_lev_rec_cache_entry, s1, s2)

            for j in range(4):
                t[j][length] /= n
        gc.unfreeze()
        # print(*t, sep="\n")

        length_arr = [i for i in range(1, max_length + 1)]
        plt.figure(1)
        plt.plot(length_arr, t[0], label='Левенштейн')
        # plt.plot(length_arr, t[1], label='Левенштейн рек')
        plt.plot(length_arr, t[2], label='Левенштейн рек кэш')
        plt.plot(length_arr, t[3], label='Дамерау-Левенштейн')
        # plt.plot(length_arr, t[4], label='Дамерау-Левенштейн рек')
        # plt.plot(length_arr, t[5], label='Дамерау-Левенштейн рек кэш')
        plt.legend(loc='best', fontsize=12)
        plt.xlabel('Длина строки')
        plt.ylabel('Время, мс')
        plt.grid(True)
        plt.show()

        plt.figure(2)
        plt.plot(length_arr, t[0], label='Левенштейн')
        # plt.plot(length_arr, t[2], label='Левенштейн рек кэш')
        plt.plot(length_arr, t[3], label='Дамерау-Левенштейн')
        # plt.plot(length_arr, t[5], label='Дамерау-Левенштейн рек кэш')
        plt.legend(loc='best', fontsize=12)
        plt.xlabel('Длина строки')
        plt.ylabel('Время, мс')
        plt.grid(True)
        plt.show()

        # plt.figure(3)
        # plt.plot(length_arr, t[3], label='Д-Л')
        # plt.plot(length_arr, t[5], label='Д-Л (рек с кешем)')
        # plt.legend(loc='best', fontsize=12)
        # plt.xlabel('Длина строки')
        # plt.ylabel('Время, мс')
        # plt.grid(True)
        # plt.show()
