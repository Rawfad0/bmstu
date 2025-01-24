import matplotlib.pyplot as plt


def get_data(path):
    ds = []
    ts = []
    print(path)
    with open(path, 'r') as f:
        lines = f.read().splitlines()
        pairs = []
        for line in lines:
            t, d = line.split(', ')
            print(f"{int(float(d))} & {float(t)*1000:.3f} \\\\ \\hline")
            pairs.append((float(d), float(t)*1000))
        pairs.sort(key=lambda x: x[0])
        for pair in pairs:
            ds.append(pair[0])
            ts.append(pair[1])
    return ds, ts


ds_cube, ts_1 = get_data('../data/data_dist_cube_02.txt')
# ds_cube2, ts_12 = get_data('../data/data_dist_cube_03.txt')
ds_sqpyr, ts_2 = get_data('../data/data_dist_sqpyr_02.txt')
ds_tetr, ts_3 = get_data('../data/data_dist_tetr_02.txt')
ds_hprism, ts_4 = get_data('../data/data_dist_hexprism_02.txt')
# ds_hprism2, ts_42 = get_data('../data/data_dist_hexprism_01.txt')

plt.figure()
plt.plot(ds_cube, ts_1, label='Куб', color='b', marker='s')
# plt.plot(ds_cube2, ts_12, label='Куб2', color='y', marker='.')
plt.plot(ds_sqpyr, ts_2, label='Четырехугольная пирамида', color='r', marker='D')
plt.plot(ds_tetr, ts_3, label='Тетраэдр', color='g', marker='^')
plt.plot(ds_hprism, ts_4, label='Шестиугольная призма', color='m', marker='h')
# plt.plot(ds_hprism2, ts_42, label='Шестиугольная призма', color='y', marker='.')
plt.legend(loc='best', fontsize=12)
plt.xlabel('Расстояние центра масс объекта до наблюдателя')
plt.ylabel('Время, мс')
plt.grid(True)
plt.show()
