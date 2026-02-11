import matplotlib.pyplot as plt

sizes = [1, 2, 4, 8, 16, 32, 64]
times = [100/127.353, 100/87.003, 100/59.0796, 100/41.2432, 100/24.837, 100/15.4944, 100/8.3868]
# times = [127353, 87003, 59079.6, 41243.2, 24837, 15494.4, 8386.8]

plt.figure()
plt.plot(sizes, times, marker='.')
plt.xlabel('Количество потоков')
# plt.ylabel('Время, мс')
plt.ylabel('Производительность (страниц в секунду)')
plt.grid(True)
plt.show()
