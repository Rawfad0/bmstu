from random import sample
from algs import linear_search, binary_search
import matplotlib.pyplot as plt
# from collections import Counter


def search_all(arr, func):
    comp_list, i_list = [], []
    i, c = func(arr, 1000000)
    comp_list.append(c)
    i_list.append(i)
    for x in arr:
        i, c = func(arr, x)
        comp_list.append(c)
        i_list.append(i)
    return comp_list, i_list


def histogram_plot(comp_list, i_list, title):
    plt.bar(i_list, comp_list, width=1)
    plt.title(title)
    plt.xlabel("Индекс элемента массива")
    plt.ylabel("Количество сравнений")
    plt.grid(visible=True)
    plt.show()


def main():
    X = 8172
    arr_len = X // 8 + (X % 1000 if (X >> 2) % 10 == 0 else (X >> 2) % 10 * (X % 10) + (X >> 1) % 10)
    print("ARR_LEN =", arr_len)
    arr = sample([i for i in range(100000)], k=arr_len)

    histogram_plot(*search_all(arr, linear_search), "Нахождение элемента алгоритмом полного перебором")
    arr.sort()
    c_list, i_list = search_all(arr, binary_search)
    histogram_plot(c_list, i_list, "Нахождение элемента алгоритмом двоичного поиска")
    c_list.sort()
    # print(Counter(c_list))
    histogram_plot(c_list, i_list, "Нахождение элемента алгоритмом двоичного поиска (отсортировано)")


if __name__ == "__main__":
    main()
