import os
import pandas as pd
import matplotlib.pyplot as plt


def plot_data(file_path, y_label):
    data = pd.read_csv(file_path, encoding='UTF-8')     # загрузка данных из csv файла
    columns = data.columns  # названия столбцов

    # Извлечение данных для оси Y и остальных столбцов для оси X
    Y_column = columns[0]
    X_columns = columns[1:]

    # s = data[Y_column]
    # t1 = data[X_columns[0]]
    # t2 = data[X_columns[0]]
    # for i in range(9):
    #     print(f"{s[i]} & {t1[i]:.5f} & {t2[i]:.5f} \\\\ \\hline")

    plt.figure(figsize=(10, 6))  # Создание графика
    plt.plot(data[Y_column], data[X_columns[0]], marker='^', label="Полный перебор")
    plt.plot(data[Y_column], data[X_columns[1]], marker='v', label="Муравьиный алгоритм")
    plt.xlabel("Размер матрицы")
    plt.ylabel(y_label)
    # plt.yscale('log')  # установка экспоненциальной шкалы для Y
    plt.legend()  # добавление легенды
    plt.grid(True)

    # Сохранение файла с расширением .pdf
    # plt.savefig(os.path.splitext(file_path)[0] + '_logscale.pdf', bbox_inches='tight')
    plt.savefig(os.path.splitext(file_path)[0] + '.pdf', bbox_inches='tight')

    plt.show()

# Вызов функции plot_data с указанным файлом и меткой для Y-оси
plot_data("../data/results.csv", "Время, с")