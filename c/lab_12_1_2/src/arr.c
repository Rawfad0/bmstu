#include "arr.h"

#define EPS 0.000000001

void left_cycle_shift(int *arr, size_t n)
{
    if (n == 0 || n == 1)
        return;

    int tmp = arr[0];
    for (size_t i = 1; i < n; i++)
        arr[i - 1] = arr[i];
    arr[n - 1] = tmp;
}

void k_left_cycle_shift(int *arr, size_t n, size_t k)
{
    size_t kmod = k % n;
    for (size_t i = 0; i < kmod; i++)
        left_cycle_shift(arr, n);
}

int count_new_arr_len(int *arr, size_t n)
{
    size_t res = 0;
    float tmp;
    for (size_t i = 0; i < n; i++)
        if (arr[i] >= 0)
            if (tmp = sqrt(arr[i]), tmp - (int) tmp < EPS)
                res++;
    return res;
}

void filter_squares(int *arr_src, size_t n_src, int *arr_dst)
{
    int n_dst = 0;
    float tmp;
    for (size_t i = 0; i < n_src; i++)
        if (arr_src[i] >= 0)
            if (tmp = sqrt(arr_src[i]), tmp - (int) tmp < EPS)
                arr_dst[n_dst++] = arr_src[i];
}
