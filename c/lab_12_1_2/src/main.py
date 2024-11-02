from funcs import k_left_cycle_shift, filter_squares
import tkinter as tk
import re


def error_message(line):
    error_window = tk.Toplevel(window)
    error_window.title("Ошибка")
    error_window.geometry("500x100")
    tk.Label(error_window, text=line, font=("Arial", 20)).pack()


def entry_print(entry, str_value):
    entry.delete(0, tk.END)
    entry.insert(0, str_value)


def clean_entry_arr():
    entry_arr.delete(0, tk.END)


def clean_entry_k():
    entry_k.delete(0, tk.END)


def func_left_cycle_shift():
    arr = entry_arr.get()
    k = entry_k.get()

    arr_split = arr.split()
    if len(arr_split) == 0:
        error_message("Некорректный массив")
    else:
        i = 0
        while (i < len(arr_split) and re.match("^-?\d*$", arr_split[i]) is not None):
            i += 1
        if i != len(arr_split):
            error_message("Некорректный массив")
        elif re.match("^\d*$", k) is None:
            error_message("Некорректный сдвиг")
        else:
            res = k_left_cycle_shift([int(i) for i in arr.split()], int(k))
            entry_print(entry_arr, " ".join([str(i) for i in res]))
            # entry_print(entry_k, "")  # очистка поля если нужно


def func_filter_squares():
    arr = entry_arr.get()
    arr_split = arr.split()
    if len(arr_split) == 0:
        error_message("Некорректный массив")
    else:
        i = 0
        while (i < len(arr_split) and re.match("^-?\d*$", arr_split[i]) is not None):
            i += 1
        if i != len(arr_split):
            error_message("Некорректный массив")
        else:
            res = filter_squares([int(i) for i in arr.split()])
            entry_print(entry_arr, " ".join([str(i) for i in res]))


window = tk.Tk()
window.title('LAB12_2')
window.geometry("950x100")

font = 20
width = 20

# labels
label_arr = tk.Label(text="Массив", font=("Arial", font))
label_shift = tk.Label(text="Сдвиг", font=("Arial", font))
# entries
entry_arr = tk.Entry(window, width=width, font=("Arial", font))
entry_k = tk.Entry(window, width=width, font=("Arial", font))
# buttons
button_clean_entry_arr = tk.Button(text="Очистить", font=("Arial", font), command=clean_entry_arr)
button_clean_entry_k = tk.Button(text="Очистить", font=("Arial", font), command=clean_entry_k)
button_left_cycle_shift = tk.Button(text="Циклический сдвиг влево", font=("Arial", font), command=func_left_cycle_shift)
button_filter_squares = tk.Button(text="Только полные квадраты", font=("Arial", font), command=func_filter_squares)
# grid
grid = [[label_arr, entry_arr, button_clean_entry_arr, button_left_cycle_shift],
        [label_shift, entry_k, button_clean_entry_k, button_filter_squares]]
# grid compositor
for grid_i in range(len(grid)):
    for grid_j in range(len(grid[grid_i])):
        grid[grid_i][grid_j].grid(column=grid_j, row=grid_i, sticky="w")

window.mainloop()
