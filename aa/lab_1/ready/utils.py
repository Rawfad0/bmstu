from time import process_time
from random import choices
from string import ascii_lowercase, ascii_uppercase


# def print_matrix(matrix, n, m):
#     for i in range(n):
#         len(str())


def record_process_time(func, *args):
    tb = process_time()
    func(*args)
    te = process_time()
    return te - tb


def generate_str(length):
    return ''.join(choices(ascii_lowercase + ascii_uppercase, k=length))
