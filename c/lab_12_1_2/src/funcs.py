import ctypes

lib = ctypes.CDLL('./out/libarr.so')

# void k_left_cycle_shift(int *arr, size_t n, size_t k);
_k_left_cycle_shift = lib.k_left_cycle_shift
_k_left_cycle_shift.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.c_int)


def k_left_cycle_shift(nums, k):
    src_len = len(nums)
    src = (ctypes.c_int * src_len)(*nums)
    _k_left_cycle_shift(src, src_len, k)
    return list(src)


# int count_new_arr_len(int *arr, int n);
_count_new_arr_len = lib.count_new_arr_len
_count_new_arr_len.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int)
_count_new_arr_len.restype = ctypes.c_int


def count_new_arr_len(nums):
    src_len = len(nums)
    src = (ctypes.c_int * src_len)(*nums)
    return _count_new_arr_len(src, src_len)


# void filter_squares(int *arr_src, int n_src, int *arr_dst, int n_dst);
_filter_squares = lib.filter_squares
_filter_squares.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.POINTER(ctypes.c_int))


def filter_squares(nums):
    src_len = len(nums)
    src = (ctypes.c_int * src_len)(*nums)
    dst_len = count_new_arr_len(nums)
    dst = (ctypes.c_int * int(dst_len))()
    _filter_squares(src, src_len, dst, dst_len)
    return list(dst)
